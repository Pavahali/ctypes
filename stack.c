// It's licensed under MIT, btw
#include "stack.h"

#include <stddef.h> // size_t
#include <string.h> // memcpy()
#include <stdlib.h> // malloc() and free()

stack_t stack_new() {
    return (stack_t){0, 0};
}

int stack_empty(stack_t S) {
    return !(S.head);
}

void *stack_top(stack_t S) {
    if (stack_empty(S)) return 0;
    return S.head->item;
}

size_t stack_size(stack_t S) {
    return S.size;
}

void stack_push(stack_t *S, void *item, size_t size) {
    struct stack_item *newi = (struct stack_item*)malloc(sizeof(struct stack_item));

    newi->item = malloc(size);
    memcpy((void*)newi->item, item, size);

    if (stack_empty(*S)) {
        S->head = newi;
        S->head->prev = 0;
    } else {
        newi->prev = S->head;
        S->head = newi;
    }

    S->size++;
}

void stack_pop(stack_t *S) {
    if (stack_empty(*S)) return;

    struct stack_item *oldi = S->head;
    free(oldi->item);

    if (S->head->prev == 0) {
        S->head = 0;
    } else {
        S->head = S->head->prev;
    }

    S->size--;
    free(oldi);
}