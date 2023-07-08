// It's licensed under MIT, btw
#include "comparator.h"
#include <string.h> // memcpy()
#include <stdio.h>

#define sgn(a) ( (0 < (a)) - ((a) < 0) )

void* cmp_item(cmp_item_t x) {
    return x.data;
}

cmp_item_t cmp_item_new(void* data, size_t size) {
    return (cmp_item_t){data, size};
}

cmp_item_t cmp_item_copy(void* data, size_t size) {
    void* out;

    out = malloc(size);
    memcpy(out, data, size);
    return (cmp_item_t){out, size};
}

// ---
// Boolean compare (byte-by-byte)

// Platform-independent

// Is `a` equal to `b`?
int cmp_equal(cmp_item_t a, cmp_item_t b) {
    if (a.size != b.size) return 0;

    uint8_t* aptr = (uint8_t*)a.data + a.size - 1;
    uint8_t* bptr = (uint8_t*)b.data + b.size - 1;

    while (aptr >= (uint8_t*)a.data && bptr >= (uint8_t*)b.data) {
        if (*aptr != *bptr) return 0;
        aptr--;
        bptr--;
    }
    return 1;
}


// Little-endian


// Is `a` less or equal to `b`? (In little-endian)
int cmp_smaller_le(cmp_item_t a, cmp_item_t b) {
    if (a.size != b.size) return (a.size <= b.size);


    uint8_t* aptr = (uint8_t*)a.data + a.size - 1;
    uint8_t* bptr = (uint8_t*)b.data + b.size - 1;

    while (aptr >= (uint8_t*)a.data && bptr >= (uint8_t*)b.data) {
        if (*aptr != *bptr) return *aptr <= *bptr;
        aptr--;
        bptr--;
    }
    return 1; // if a == b;
}

// Is `a` greater than `b`? (In little-endlian)
int cmp_greater_le(cmp_item_t a, cmp_item_t b) {
    if (a.size != b.size) return (a.size > b.size);


    uint8_t* aptr = (uint8_t*)a.data + a.size - 1;
    uint8_t* bptr = (uint8_t*)b.data + b.size - 1;

    while (aptr >= (uint8_t*)a.data && bptr >= (uint8_t*)b.data) {
        if (*aptr != *bptr) return *aptr > *bptr;
        aptr--;
        bptr--;
    }
    return 1; // if a == b;
}


// Big-Endian


// Is `a` less or equal to `b`? (In big-endian)
int cmp_smaller_be(cmp_item_t a, cmp_item_t b) {
    if (a.size != b.size) return (a.size <= b.size);

    
    uint8_t* aptr = (uint8_t*)a.data;
    uint8_t* bptr = (uint8_t*)b.data;

    while (aptr != (uint8_t*)a.data + a.size && bptr != (uint8_t*)b.data + b.size) {
        if (*aptr != *bptr) return *aptr <= *bptr;
        aptr++;
        bptr++;
    }
    return 1; // if a == b;
}

// Is `a` greater than `b`? (In big-endian)
int cmp_greater_be(cmp_item_t a, cmp_item_t b) {
    if (a.size != b.size) return (a.size > b.size);

    
    uint8_t* aptr = (uint8_t*)a.data;
    uint8_t* bptr = (uint8_t*)b.data;

    while (aptr != (uint8_t*)a.data + a.size && bptr != (uint8_t*)b.data + b.size) {
        if (*aptr != *bptr) return *aptr > *bptr;
        aptr++;
        bptr++;
    }
    return 1; // if a == b;
}

// Platform-dependent

// Is `a` less or equal to `b`?
// If it does not work, consider manually specifying endianness
int cmp_smaller(cmp_item_t a, cmp_item_t b) {
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        return cmp_smaller_le(a, b);
    #else
        return cmp_smaller_be(a, b);
    #endif
}

// Is `a` greater than `b`?
// If it does not work, consider manually specifying endianness
int cmp_bigger(cmp_item_t a, cmp_item_t b) {
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        return cmp_greater_le(a, b);
    #else
        return cmp_greater_be(a, b);
    #endif
}

//
// ---

// ---
// Signum-compare (byte-by-byte)


// What is the result of sgn(`a.size` - `b.size`) ?
// -1 if a.size < b.size
// 0 if a.size == b.size
// 1 if a.size > b.size
int cmp_sgn_size(cmp_item_t a, cmp_item_t b) {
    return sgn(a.size - b.size);
}

// What is the result of sgn(`a` - `b`) ?
// -1 if a < b
// 0 if a == b
// 1 if a > b
// Compare in little-endian
int cmp_sgn_le(cmp_item_t a, cmp_item_t b) {
    if (a.size != b.size) return sgn(a.size - b.size);


    uint8_t* aptr = (uint8_t*)a.data + a.size - 1;
    uint8_t* bptr = (uint8_t*)b.data + b.size - 1;

    while (aptr >= (uint8_t*)a.data && bptr >= (uint8_t*)b.data) {
        if (*aptr != *bptr) return sgn(*aptr - *bptr);
        aptr--;
        bptr--;
    }
    return 0; // if a == b;
}

// What is the result of sgn(`a` - `b`) ?
// -1 if a < b
// 0 if a == b
// 1 if a > b
// Compare in big-endian
int cmp_sgn_be(cmp_item_t a, cmp_item_t b) {
    if (a.size != b.size) return sgn(a.size - b.size);

    
    uint8_t* aptr = (uint8_t*)a.data;
    uint8_t* bptr = (uint8_t*)b.data;

    while (aptr != (uint8_t*)a.data + a.size && bptr != (uint8_t*)b.data + b.size) {
        if (*aptr != *bptr) return sgn(*aptr - *bptr);
        aptr++;
        bptr++;
    }
    return 0; // if a == b;
}

// What is the result of sgn(`a` - `b`) ?
// -1 if a < b
// 0 if a == b
// 1 if a > b
// If it does not work, consider manually specifying endianness
int cmp_sgn(cmp_item_t a, cmp_item_t b) {
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        return cmp_sgn_le(a, b);
    #else
        return cmp_sgn_be(a, b);
    #endif
}

#undef sgn