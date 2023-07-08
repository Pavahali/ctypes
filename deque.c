// It's licensed under MIT, btw
#include "comparator.h"
#include "deque.h"

#include <stdlib.h> // malloc() and free()
#include <string.h> // memcpy()

deque_t deque_new() {
    return (deque_t){0, 0, 0};
}

int deque_empty(deque_t L) {
    return !(L.tail);
}

size_t deque_size(deque_t L) {
    return L.size;
}

void* deque_front(deque_t L) {
    if (deque_empty(L)) return 0;
    else return cmp_item(L.tail->item);
}

void* deque_back(deque_t L) {
    if (deque_empty(L)) return 0;
    else return cmp_item(L.head->item);
}

void deque_push_front(deque_t* L, void* item, size_t size) {
    struct deque_item* newi = (struct deque_item*)malloc(sizeof(struct deque_item));
    
    newi->prev = 0;
    newi->item = cmp_item_new(item, size);
    
    if (deque_empty(*L)) {
        L->tail = newi;
        L->head = L->tail;
    } else {
        newi->next = L->tail;
        L->tail->prev  = newi;
        L->tail = newi;
    }
    L->size++;
}

void deque_push_back(deque_t* L, void* item, size_t size) {
    struct deque_item* newi = (struct deque_item*)malloc(sizeof(struct deque_item));
    
    newi->next = 0;
    newi->item = cmp_item_new(item, size);

    if (deque_empty(*L)) {
        L->head = newi;
        L->tail = L->head;
    } else {
        newi->prev = L->head;
        L->head->next = newi;
        L->head = newi;
    }
    L->size++;
}

void deque_pop_front(deque_t *L) {
    if (deque_empty(*L)) return;
    struct deque_item* oldi = L->tail;

    if (L->head == L->tail) {
        L->head = 0;
        L->tail = 0;
    } else {
        L->tail = L->tail->next;
    }

    free(cmp_item(oldi->item));
    free(oldi);
    L->size--;
}

void deque_pop_back(deque_t *L) {
    if (deque_empty(*L)) return;
    struct deque_item* oldi = L->head;

    if (L->head == L->tail) {
        L->head = 0;
        L->tail = 0;
    } else {
        L->head = L->head->prev;
    }

    free(cmp_item(oldi->item));
    free(oldi);
    L->size--;
}

static struct deque_item* __deque_at(deque_t L, int at) {
    if (deque_empty(L)) return 0;
    struct deque_item* p = L.tail;
    while (at--) {
        p = p->next;
        if (!p) return 0;
    }
    return p;
}

void* deque_at(deque_t L, int at) {
    if (deque_empty(L)) return 0;
    struct deque_item* p = L.tail;
    while (at--) {
        p = p->next;
        if (!p) return 0;
    }
    return cmp_item(p->item);
}


void deque_insert(deque_t* L, int at, void* item, size_t size) {
    struct deque_item* p;
    struct deque_item* newi;

    if (deque_empty(*L)) deque_push_back(L, item, size);
    else if (at == 0) deque_push_front(L, item, size);
    else if (at >= L->size) deque_push_back(L, item, size);
    else {
        newi = (struct deque_item*)malloc(sizeof(struct deque_item));
        newi->item = cmp_item_new(item, size);

        p = __deque_at(*L, at-1);
        
        newi->prev = p;
        newi->next = p->next;
        newi->next->prev = newi;
        newi->prev->next = newi;

        L->size++;
    }
}

void deque_remove(deque_t* L, int at) {
    struct deque_item* oldi;

    if (deque_empty(*L)) return;
    else if (at == 0) deque_pop_front(L);
    else if (at == L->size-1) deque_pop_back(L);
    else if (at >= L->size) return;
    else {
        struct deque_item* p = __deque_at(*L, at-1);
        oldi = p->next;

        p->next = p->next->next;
        p->next->prev = p;
        
        free(cmp_item(oldi->item));
        free(oldi);
        L->size--;
    }
}

int deque_count(deque_t L, void* item, size_t size) {
    struct deque_item *p = L.tail;
    cmp_item_t x = {item, size};

    int out = 0;
    while (p != 0) {
        if (cmp_equal(x, p->item)) out++;
        p = p->next;
    }
    return out;
}