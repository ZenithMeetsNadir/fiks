#ifndef IOF_PARSER_H
#define IOF_PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

const char *readInput(const char *filename, size_t *size_p);
void writeOutput(const char *filename, const char *data, size_t size);
void appendOutput(const char *filename, const char *data, size_t size);

size_t indexOf(const char *data, size_t size, char c, size_t start);

struct StringIterator {
    const char *data;
    size_t size;
    size_t pos;
    char delim;
};

void stringIterInit(struct StringIterator *iter, char delim);
const char *stringIterNext(struct StringIterator *iter, size_t *len);
const char *stringIterNextValid(struct StringIterator *iter, size_t *len);
char stringIterNextParseUint64(struct StringIterator *iter, uint64_t *out_value);
const char *dupeNTerm(const char *data, size_t len);

#endif