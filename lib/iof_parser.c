#include "iof_parser.h"

const char *readInput(const char *filename, size_t *size_p) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("error opening file");
        return NULL;
    };

    fseek(file, 0, SEEK_END);
    *size_p = ftell(file);

    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(*size_p * sizeof(char));
    if (buffer == NULL) {
        fclose(file);
        return NULL;
    }

    fread(buffer, sizeof(char), *size_p, file);
    fclose(file);

    return buffer;
}

void writeFile(const char *filename, const char *data, size_t size, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        perror("error opening file for writing");
        return;
    }

    fwrite(data, sizeof(char), size, file);
    fclose(file);
}

void writeOutput(const char *filename, const char *data, size_t size) {
    writeFile(filename, data, size, "w+");
}

void appendOutput(const char *filename, const char *data, size_t size) {
    writeFile(filename, data, size, "a+");
}

size_t indexOf(const char *data, size_t size, char c, size_t start){
    for (size_t i = start; i < size; i++) {
        if (data[i] == c)
            return i;
    }

    // if not found
    return size;
}

void stringIterInit(struct StringIterator *iter, char delim) {
    iter->pos = 0;
    iter->delim = delim;
}

void stringIterReset(struct StringIterator *iter) {
    iter->pos = 0;
}

const char *stringIterNext(struct StringIterator *iter, size_t *len) {
    if (iter->pos >= iter->size) {
        *len = 0;
        return NULL;
    }

    size_t start = iter->pos;
    size_t end = indexOf(iter->data, iter->size, iter->delim, start);

    iter->pos = (end < iter->size) ? end + 1 : end;

    *len = end - start;
    return iter->data + start;
}

const char *stringIterNextValid(struct StringIterator *iter, size_t *len) {
    const char *str = NULL;
    do {
        str = stringIterNext(iter, len);
    } while ((str == NULL || *len == 0) && iter->pos < iter->size);

    if (*len == 0)
        return NULL;
    
    return str;
}

char stringIterNextParseUint64(struct StringIterator *iter, uint64_t *out_value) {
    size_t len;
    const char *str = stringIterNextValid(iter, &len);
    if (str == NULL || len == 0)
        return 0;

    const char *nterm = dupeNTerm(str, len);
    if (nterm == NULL)
        return 0;

    char *endptr = NULL;
    *out_value = strtoull(nterm, &endptr, 10);
    free((void *)nterm);

    return 1;
}

const char *dupeNTerm(const char *data, size_t len) {
    char *nterm = (char *)malloc((len + 1) * sizeof(char));
    if (nterm == NULL)
        return NULL;

    for (size_t i = 0; i < len; i++)
        nterm[i] = data[i];

    nterm[len] = '\0';
    return nterm;
}