// It's licensed under MIT, btw
#ifndef _PAVA_SET_H
#define _PAVA_SET_H
#include "comparator.h"

#include <stdlib.h> // size_t

struct set_node {
    struct set_node *left;
    struct set_node *right;
    struct set_node *parent;
    int color;

    cmp_item_t key;
};

struct set {
    struct set_node *root;
    int (*sgn_cmp)(cmp_item_t a, cmp_item_t b);

    size_t size;
};

typedef struct set set_t;

// Returns a properly initialised `set_t`. Takes signum comparator as an argument
extern set_t set_new(int (*sgn_cmp)(cmp_item_t a, cmp_item_t b));

// Returns the number of elements
extern size_t set_size(set_t S);

// Inserts an element in the set
extern void set_insert(set_t *S, cmp_item_t key);

// Deletes an element from the set
extern void set_delete(set_t *S, cmp_item_t key);

// Returns the number of elements in the set
extern int set_count(set_t S, cmp_item_t key);


#endif