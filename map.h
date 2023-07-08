// It's licensed under MIT, btw
#ifndef _MAP_PAVA_H
#define _MAP_PAVA_H
#include "comparator.h"

#include <stdlib.h> // size_t

struct map_node {
    struct map_node *left;
    struct map_node *right;
    struct map_node *parent;
    int color;

    cmp_item_t key;
    cmp_item_t value;
};

struct map {
    struct map_node *root;
    int (*sgn_cmp)(cmp_item_t a, cmp_item_t b);
    size_t size;
};

typedef struct map map_t;

// Returns a properly initialised `map_t`. Takes signum comparator as an argument
extern map_t map_new(int (*sgn_cmp)(cmp_item_t a, cmp_item_t b));

// Returns the number of elements
extern size_t map_size(map_t M);

// Inserts an element with a specified key in the map
extern void map_insert(map_t *M, cmp_item_t key, cmp_item_t value);

// Deletes an element with a specified key from the map
extern void map_delete(map_t *M, cmp_item_t key);

// Accesses an an element with a specified key in the tree
extern cmp_item_t *map_find(map_t M, cmp_item_t key);


#endif