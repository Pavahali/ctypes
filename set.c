// It's licensed under MIT, btw
#include "comparator.h"
#include "set.h"

set_t set_new(int (*sgn_cmp)(cmp_item_t a, cmp_item_t b)) {
    return (set_t){0, sgn_cmp, 0};
}

size_t set_size(set_t S) {
    return S.size;
}

static struct set_node *set_node_new(cmp_item_t key) {
    struct set_node *node = (struct set_node*)malloc(sizeof(struct set_node)); 
    node->key = cmp_item_copy(key.data, key.size);
    node->parent = 0;
    node->left = 0;
    node->right = 0;
    node->color = 1;
    
    return node;
}


// ---
// set_find

static struct set_node *__set_find(struct set_node *root, cmp_item_t key, int (*sgn_cmp)(cmp_item_t a, cmp_item_t b)) {
    if (!root) return 0;
    switch (sgn_cmp(root->key, key)) {
        case -1:
            return __set_find(root->right, key, sgn_cmp);
        case 0: 
            return root;
        case 1:
            return __set_find(root->left, key, sgn_cmp);
        default:
            return 0;
    }
}

static struct set_node *_set_find(set_t S, cmp_item_t key) {
    return __set_find(S.root, key, S.sgn_cmp);
}

int set_count(set_t S, cmp_item_t key) {
    return _set_find(S, key) ? 1 : 0;
}

//
// ---

// ---
// rotation functions

static void __rotate_left(set_t *S, struct set_node *node) {
    struct set_node *child = node->right;
    node->right = child->left;

    if (node->right) node->right->parent = node;

    child->parent = node->parent;

    if (!node->parent) S->root = child;
    else if (node == node->parent->left) node->parent->left = child;
    else node->parent->right = child;

    child->left = node;
    node->parent = child;
}

static void __rotate_right(set_t *S, struct set_node *node) {
    struct set_node *child = node->left;
    node->left = child->right;

    if (node->left) node->left->parent = node;

    child->parent = node->parent;

    if (!node->parent) S->root = child;
    else if (node == node->parent->left) node->parent->left = child;
    else node->parent->right = child;

    child->right = node;
    node->parent = child;
}

//
// ---

// ---
// set_insert

static struct set_node *__find_parent(set_t *S, struct set_node *node) {
    struct set_node *x = S->root;
    struct set_node *par = 0;
    
    while (x != 0) {
        par = x;
        switch (S->sgn_cmp(node->key, x->key)) {
        case -1:
            x = x->left;
            break;
        default: // + case 0:
            return x;
        case 1:
            x = x->right;
            break;
        }
    }
    
    return par;
}

static void __insert_fix(set_t *S, struct set_node *node) {
    struct set_node *u; // uncle

    while (node->parent && node->parent->color) {
        if (node->parent == node->parent->parent->left) {
            u = node->parent->parent->right;
            if (u && u->color) {
                node->parent->color = 0;
                u->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    __rotate_left(S, node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                __rotate_right(S, node->parent->parent);
            }
        } else {
            u = node->parent->parent->left;
            if (u && u->color) {
                node->parent->color = 0;
                u->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    __rotate_right(S, node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                __rotate_left(S, node->parent->parent);
            }
        }
    }
    S->root->color = 0;
}

static void set_insert_node(set_t *S, struct set_node *node) {
    // Insert `item` into tree
    struct set_node *par = __find_parent(S, node);

    node->parent = par;

    if (!par) S->root = node;
    else {
        switch (S->sgn_cmp(par->key, node->key)) {
        case -1:
            par->right = node;
            break;
        default: // + case 0:
            free(cmp_item(node->key));
            free(node);
            return;
        case 1:
            par->left = node;
            break;
        }
    }

    __insert_fix(S, node);
    S->size++;
}

void set_insert(set_t *S, cmp_item_t item) {
    set_insert_node(S, set_node_new(item));
}

//
// ---

// ---
// set_remove
static struct set_node *__minimum(struct set_node *node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

static void __transplant(set_t *S, struct set_node *u, struct set_node *v) {
    if (!u->parent) S->root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;

    if (v) v->parent = u->parent;
}

static void __delete_fix(set_t *S, struct set_node *node) {
    struct set_node *u;

    if (!node) return;

    while (node != S->root && !node->color) {
        if (node == node->parent->left) {
            u = node->parent->right;
            if (u->color) {
                u->color = 0;
                node->parent->color = 1;
                __rotate_left(S, node->parent);
                u = node->parent->right;
            }
            if (!u->left->color && !u->right->color) {
                u->color = 1;
                node = node->parent;
            } else {
                if (!u->right->color) {
                    u->left->color = 0;
                    u->color = 1;
                    __rotate_right(S, u);
                    u = node->parent->right;
                }
                u->color = node->parent->color;
                node->parent->color = 0;
                u->right->color = 0;
                __rotate_left(S, node->parent);
                node = S->root;
            }
        } else {
            u = node->parent->left;
            if (u->color) {
                u->color = 0;
                node->parent->color = 1;
                __rotate_right(S, node->parent);
                u = node->parent->left;
            }
            if (!u->left->color && !u->right->color) {
                u->color = 1;
                node = node->parent;
            } else {
                if (!u->left->color) {
                    u->right->color = 0;
                    u->color = 1;
                    __rotate_left(S, u);
                    u = node->parent->left;
                }
                u->color = node->parent->color;
                node->parent->color = 0;
                u->left->color = 0;
                __rotate_right(S, node->parent);
                node = S->root;
            }
        }
    }
    node->color = 0;
}


void set_delete(set_t *S, cmp_item_t key) {
    struct set_node *node = _set_find(*S, key);
    struct set_node *u, *v;
    int color;

    if (!node) return;

    u = node;
    color = u->color;
    if (!node->left) {
        v = node->right;
        __transplant(S, node, node->right);
    } else if (!node->right) {
        v = node->left;
        __transplant(S, node, node->left);
    } else {
        u = __minimum(node->right);
        color = u->color;
        v = u->right;
        if (u->parent == node) v->parent = u;
        else {
            __transplant(S, u, u->right);
            u->right = node->right;
            u->right->parent = u;
        }
        __transplant(S, node, u);
        u->left = node->left;
        u->left->parent = u;
        u->color = node->color;
    }

    if (!color) __delete_fix(S, v);

    free(cmp_item(node->key));
    free(node);
    S->size--;
}

//
// ---