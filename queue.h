// It's licensed under MIT, btw
#ifndef _CTYPES_QUEUE_H
#define _CTYPES_QUEUE_H

#include <stdlib.h> // size_t

// The item stored in the queue
struct queue_item
{
    void *item;
    struct queue_item *next;
};

// The queue type. should be assigned the value of queue_new() or zeroed manually
struct queue
{
    size_t size;
    struct queue_item *tail;
    struct queue_item *head;
};

typedef struct queue queue_t;


// Returns `queue_t` filled with zeroes
// Can be replaced with {0, 0, 0}
queue_t queue_new();

// Returns a boolean value indicating whether or not `Q` is empty
extern int queue_empty(queue_t q);

// Returns the number of elements
extern size_t queue_size(queue_t q);


// Accesses the first element
extern void* queue_front(queue_t q);

// Accesses the last element
extern void* qeque_back(queue_t q);


// Inserts an element at the end
extern void queue_push(queue_t* q, void* item, size_t size);

// Removes the last element
extern void queue_pop(queue_t* q);

#endif