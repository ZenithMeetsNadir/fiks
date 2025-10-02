#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <inttypes.h>
#include <math.h>

#define ITER_DEPTH 0xff

char radixSort(uint64_t *data, size_t size);
uint64_t* excludeZeroes(const uint64_t *data, size_t size, size_t *out_size);

#endif
