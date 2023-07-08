// It's licensed under MIT, btw
#ifndef _CTYPES_STACK_H
#define _CTYPES_STACK_H

#include <stddef.h> // size_t


// The item stored in the stack
struct stack_item {
    void *item;
    struct stack_item *prev;
};

// The stack itself. Should be assingned the value of `stack_new()` or zeroed manually
struct stack {
    size_t size;
    struct stack_item *head;
};

typedef struct stack stack_t;


// Returns `stack_t` filled with zeroes
// Can be replaced with {0, 0}
extern stack_t stack_new();

// Returns a boolean value indicating whether or not `S` is empty 
extern int stack_empty(stack_t S);

// Accesses the top element
extern void *stack_top(stack_t S);

// Returns the number of elements
extern size_t stack_size(stack_t q);


// Inserts an element at the top
extern void stack_push(stack_t *S, void *item, size_t size);

// Removes the top element
extern void stack_pop(stack_t *S);

#endif