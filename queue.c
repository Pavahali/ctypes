// It's licensed under MIT, btw
#include "queue.h"

#include <stddef.h> // size_t
#include <string.h> // memcpy()
#include <stdlib.h> // malloc() and free()



queue_t queue_new() {
    return (queue_t){0, 0, 0};
}

int queue_empty(queue_t Q) {
    return !(Q.head);
}

size_t queue_size(queue_t Q) {
    return Q.size;
}


void *queue_front(queue_t Q) {
    if (queue_empty(Q)) return 0;
    return Q.tail->item;
}

void *queue_back(queue_t Q) {
    if (queue_empty(Q)) return 0;
    return Q.head->item;
}


void queue_push(queue_t *Q, void *item, size_t size) {
    struct queue_item *newi = (struct queue_item*)malloc(sizeof(struct queue_item));

    newi->item = malloc(size);
    memcpy(newi->item, item, size);

    if (queue_empty(*Q)) {
        Q->head = newi;
        Q->tail = Q->head;
        Q->head->next = 0;
    } else {
        Q->head->next = newi;
        Q->head = newi;
    }
    
    Q->size++;
}

void queue_pop(queue_t *Q) {
    struct queue_item *p;
    
    if (queue_empty(*Q)) return;

    free(Q->tail->item);
    if (Q->tail == Q->head) {
        free(Q->tail);
        Q->tail = 0;
        Q->head = 0;
    } else {
        p = Q->tail->next;
        free(Q->tail);
        Q->tail = p;
    }

    Q->size--;
}