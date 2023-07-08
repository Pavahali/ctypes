// It's licensed under MIT, btw
#include "map.h"

map_t map_new(int (*sgn_cmp)(cmp_item_t a, cmp_item_t b)) {
    return (map_t){0, sgn_cmp};
}

size_t map_size(map_t M) {
    return M.size;
}

static struct map_node *map_node_new(cmp_item_t key, cmp_item_t value) {
    struct map_node *node = (struct map_node*)malloc(sizeof(struct map_node));

    node->key = cmp_item_copy(key.data, key.size);
    node->value = cmp_item_copy(value.data, value.size);
    node->parent = 0;
    node->left = 0;
    node->right = 0;
    node->color = 1;
    
    return node;
}


// ---
// map_find

static struct map_node *__map_find(struct map_node *root, cmp_item_t key, int (*sgn_cmp)(cmp_item_t a, cmp_item_t b)) {
    if (!root) return 0;
    switch (sgn_cmp(root->key, key)) {
        case -1:
            return __map_find(root->right, key, sgn_cmp);
        case 0: 
            return root;
        case 1:
            return __map_find(root->left, key, sgn_cmp);
        default:
            return 0;
    }
}

struct map_node *_map_find(map_t M, cmp_item_t key) {
    return __map_find(M.root, key, M.sgn_cmp);
}


cmp_item_t *map_find(map_t M, cmp_item_t key) {
    struct map_node *node = _map_find(M, key);
    if (node) return &node->value;
    else return 0;
}

//
// ---

// ---
// rotation functions

static void __rotate_left(map_t *M, struct map_node *node) {
    struct map_node *child = node->right;
    node->right = child->left;

    if (node->right) node->right->parent = node;

    child->parent = node->parent;

    if (!node->parent) M->root = child;
    else if (node == node->parent->left) node->parent->left = child;
    else node->parent->right = child;

    child->left = node;
    node->parent = child;
}

static void __rotate_right(map_t *M, struct map_node *node) {
    struct map_node *child = node->left;
    node->left = child->right;

    if (node->left) node->left->parent = node;

    child->parent = node->parent;

    if (!node->parent) M->root = child;
    else if (node == node->parent->left) node->parent->left = child;
    else node->parent->right = child;

    child->right = node;
    node->parent = child;
}

//
// ---

// ---
// map_insert

static struct map_node *__find_parent(map_t *M, struct map_node *node) {
    struct map_node *x = M->root;
    struct map_node *par = 0;
    
    while (x != 0) {
        par = x;
        switch (M->sgn_cmp(node->key, x->key)) {
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

static void __insert_fix(map_t *M, struct map_node *node) {
    struct map_node *u; // uncle

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
                    __rotate_left(M, node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                __rotate_right(M, node->parent->parent);
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
                    __rotate_right(M, node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                __rotate_left(M, node->parent->parent);
            }
        }
    }
    M->root->color = 0;
}

static void map_insert_node(map_t *M, struct map_node *node) {
    // Insert `item` into tree
    struct map_node *par = __find_parent(M, node);

    node->parent = par;

    if (!par) M->root = node;
    else {
        switch (M->sgn_cmp(par->key, node->key)) {
        case -1:
            par->right = node;
            break;
        default: // + case 0:
            free(cmp_item(node->value));
            free(cmp_item(node->key));
            free(node);
            return;
        case 1:
            par->left = node;
            break;
        }
    }

    __insert_fix(M, node);
    M->size++;
}

void map_insert(map_t *M, cmp_item_t key, cmp_item_t value) {
    map_insert_node(M, map_node_new(key, value));
}

//
// ---

// ---
// map_remove
static struct map_node *__minimum(struct map_node *node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

static void __transplant(map_t *M, struct map_node *u, struct map_node *v) {
    if (!u->parent) M->root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;

    if (v) v->parent = u->parent;
}

static void __delete_fix(map_t *M, struct map_node *node) {
    struct map_node *u;

    if (!node) return;

    while (node != M->root && !node->color) {
        if (node == node->parent->left) {
            u = node->parent->right;
            if (u->color) {
                u->color = 0;
                node->parent->color = 1;
                __rotate_left(M, node->parent);
                u = node->parent->right;
            }
            if (!u->left->color && !u->right->color) {
                u->color = 1;
                node = node->parent;
            } else {
                if (!u->right->color) {
                    u->left->color = 0;
                    u->color = 1;
                    __rotate_right(M, u);
                    u = node->parent->right;
                }
                u->color = node->parent->color;
                node->parent->color = 0;
                u->right->color = 0;
                __rotate_left(M, node->parent);
                node = M->root;
            }
        } else {
            u = node->parent->left;
            if (u->color) {
                u->color = 0;
                node->parent->color = 1;
                __rotate_right(M, node->parent);
                u = node->parent->left;
            }
            if (!u->left->color && !u->right->color) {
                u->color = 1;
                node = node->parent;
            } else {
                if (!u->left->color) {
                    u->right->color = 0;
                    u->color = 1;
                    __rotate_left(M, u);
                    u = node->parent->left;
                }
                u->color = node->parent->color;
                node->parent->color = 0;
                u->left->color = 0;
                __rotate_right(M, node->parent);
                node = M->root;
            }
        }
    }
    node->color = 0;
}


void map_delete(map_t *M, cmp_item_t key) {
    struct map_node *node = (struct map_node*)_map_find(*M, key);
    struct map_node *u, *v;
    int color;

    if (!node) return;

    u = node;
    color = u->color;
    if (!node->left) {
        v = node->right;
        __transplant(M, node, node->right);
    } else if (!node->right) {
        v = node->left;
        __transplant(M, node, node->left);
    } else {
        u = __minimum(node->right);
        color = u->color;
        v = u->right;
        if (u->parent == node) v->parent = u;
        else {
            __transplant(M, u, u->right);
            u->right = node->right;
            u->right->parent = u;
        }
        __transplant(M, node, u);
        u->left = node->left;
        u->left->parent = u;
        u->color = node->color;
    }

    if (!color) __delete_fix(M, v);

    free(cmp_item(node->value));
    free(cmp_item(node->key));
    free(node);

    M->size--;
}

//
// ---