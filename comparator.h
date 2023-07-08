// It's licensed under MIT, btw
#ifndef __CTYPES_COMPARATOR_H
#define __CTYPES_COMPARATOR_H

#include <stdlib.h> // size_t
#include <stdint.h> // uint8_t

// An element which can be compared independently of its type
struct cmp_item {
    void *data;
    size_t size;
};

typedef struct cmp_item cmp_item_t;

void* cmp_item(cmp_item_t x);

// Initialises new comparable item
extern cmp_item_t cmp_item_new(void* data, size_t size);

// Initialises new comparable item and copies the data
extern cmp_item_t cmp_item_copy(void* data, size_t size);

// ---
// Boolean compare
//

// Is `a` equal to `b`?
extern int cmp_equal(cmp_item_t a, cmp_item_t b);

// Is the size of `a` less or equal than the size of `b`?
extern int cmp_shorter(cmp_item_t a, cmp_item_t b);

// Is the size of `a` longer than the size of `b`?
extern int cmp_longer(cmp_item_t a, cmp_item_t b);


// Is `a` less or equal to `b`? (In little-endian)
extern int cmp_smaller_le(cmp_item_t a, cmp_item_t b);

// Is `a` greater than `b`? (In little-endlian)
extern int cmp_greater_le(cmp_item_t a, cmp_item_t b);

// Is `a` less or equal to `b`? (In big-endian)
extern int cmp_smaller_be(cmp_item_t a, cmp_item_t b);

// Is `a` greater than `b`? (In big-endian)
extern int cmp_greater_be(cmp_item_t a, cmp_item_t b);


// Is `a` less or equal to `b`?
// If it does not work, consider manually specifying endianness
extern int cmp_smaller(cmp_item_t a, cmp_item_t b);

// Is `a` greater than `b`?
// If it does not work, consider manually specifying endianness
extern int cmp_bigger(cmp_item_t a, cmp_item_t b);

//
// ---

// ---
// Signum compare
//

// What is the result of sgn(`a.size` - `b.size`) ?
// -1 if a.size < b.size
// 0 if a.size == b.size
// 1 if a.size > b.size
extern int cmp_sgn_size(cmp_item_t a, cmp_item_t b);

// What is the result of sgn(`a` - `b`) ?
// -1 if a < b
// 0 if a == b
// 1 if a > b
// Compare in little-endian
extern int cmp_sgn_le(cmp_item_t a, cmp_item_t b);

// What is the result of sgn(`a` - `b`) ?
// -1 if a < b
// 0 if a == b
// 1 if a > b
// Compare in big-endian
extern int cmp_sgn_be(cmp_item_t a, cmp_item_t b);

// What is the result of sgn(`a` - `b`) ?
// -1 if a < b
// 0 if a == b
// 1 if a > b
// If it does not work, consider manually specifying endianness
extern int cmp_sgn(cmp_item_t a, cmp_item_t b);

//
// ---

#endif