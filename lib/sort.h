#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>

#define ITER_BITS 8
#define ITER_SIZE (1 << ITER_BITS)
#define ITER_DEPTH (ITER_SIZE - 1)
#undef LITTLE_ENDIAN
#define LITTLE_ENDIAN (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define INT_BITS (sizeof(uint64_t) * 8)

char radixSort(uint64_t *data, size_t size);

/// offset the start of an ascending sorted array to the first non-zero element
uint64_t* excludeZeroesLeft(const uint64_t *data, size_t size, size_t *out_size);

/// return size if not found
size_t indexOfAscending(const uint64_t *data, size_t size, uint64_t value);

#endif
