#ifndef FILTER_H
#define FILTER_H

#include <stddef.h>

typedef int (*PredicateFunc)(const void *item, void *context);

void *filter(const void *array, size_t size, size_t element_size, PredicateFunc pred, void *context, size_t *result_size);

#endif // FILTER_H
