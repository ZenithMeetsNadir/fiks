#include "sort.h"

char radixSort(uint64_t *data, size_t size) {
    uint64_t count_buf[ITER_DEPTH];
    for (size_t i = 0; i < ITER_DEPTH; i++)
        count_buf[i] = 0;

    uint64_t *buck_buf = (uint64_t *)malloc(size * sizeof(uint64_t));
    if (buck_buf == NULL)
        return 0;

    char in_buf_out = 1;
    int shift = 0;
    size_t num_zeroes = 0;
    while (shift < 64 && count_buf[0] != size) {
        in_buf_out = !in_buf_out;

        uint64_t *in_buf = in_buf_out ? buck_buf : data;
        uint64_t *out_buf = in_buf_out ? data : buck_buf;

        for (size_t i = 0; i < size; i++)
            count_buf[in_buf[i] & (ITER_DEPTH << shift)]++;

        for (size_t i = 1; i < ITER_DEPTH; i++)
            count_buf[i] += count_buf[i - 1];

        for (size_t i = 0; i < size; i++)
            out_buf[-1 + count_buf[in_buf[i] & (ITER_DEPTH << shift)]--] = in_buf[i];

        shift += ITER_DEPTH / 8;
    }

    if (!in_buf_out) {
        for (size_t i = 0; i < size; i++)
            data[i] = buck_buf[i];
    }

    free(buck_buf);
    return 1;
}

uint64_t* excludeZeroes(const uint64_t *data, size_t size, size_t *out_size) {
    size_t left = 0, right = size;
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (data[mid] == 0) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    if (left < size && data[left] != 0) {
        *out_size = size - left;
        return (uint64_t*)&data[left];
    }

    *out_size = 0;
    return NULL;
}