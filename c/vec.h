//
// Pure C VEC implementation.
//
// VEC is also known as:
// - Vector (that's where name comes from)
// - Dynamic Array
// - ArrayList
//
// VEC is typesafe, so by default you can't
// create VEC of different type than you declare.
//
// This will not work during compilation:
// VEC(float) vec = VEC_NEW(int, 5);
//
// Maybe I want to add grow stategy somewhere as well.
// Currently it just allocate 4 more items.
//
// UPPER_CASE is used just to remind that it's macro.
// Even though it mostly have another highlighting color.
// Change it to your code style if you want.

#ifndef VEC_H
#define VEC_H

#include "assert.h"
#include "stdlib.h"

#define CONCAT(a, b) a##b

#define VEC_GROW_SIZE 4;

#define VEC(type) CONCAT(type, Vec)

#define DEFINE_VEC(type) \
    typedef struct type##Vec { \
        type* data; \
        size_t size; \
        size_t capacity; \
    } type##Vec; \

#define VEC_NEW(type, capacity) (struct type##Vec) { (type*) malloc(capacity * sizeof(type)), 0, capacity };

#define VEC_PUSH(vec, item) \
    do { \
        if ((vec).size == (vec).capacity) { \
            (vec).capacity += VEC_GROW_SIZE; \
            void* ptr = realloc((vec).data, (vec).capacity * sizeof(*(vec).data)); \
            assert(ptr != NULL); \
            (vec).data = ptr; \
        } \
        (vec).data[(vec).size] = item; \
        (vec).size += 1; \
    } while (0)

#define VEC_REMOVE(vec, index) \
    do { \
        if ((index) < (vec).size) { \
            for (size_t i = (index); i < (vec).size - 1; i += 1) { \
                (vec).data[i] = (vec).data[i + 1]; \
            } \
            (vec).size -= 1; \
        } \
    } while (0)

#define VEC_FREE(vec) \
    do { \
        free((vec).data); \
        (vec).data = NULL; \
        (vec).capacity = 0; \
        (vec).size = 0; \
    } while (0)

#endif