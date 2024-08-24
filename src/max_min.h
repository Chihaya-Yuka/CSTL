#ifndef MAX_MIN_H
#define MAX_MIN_H

#include <stddef.h>

typedef int (*CompareFunc)(const void *a, const void *b);

void *find_max(const void *array, size_t size, size_t element_size, CompareFunc cmp);

void *find_min(const void *array, size_t size, size_t element_size, CompareFunc cmp);

#endif // MAX_MIN_H
