#ifndef REDUCE_H
#define REDUCE_H

#include <stddef.h>

typedef void *(*ReduceFunc)(void *accumulator, const void *item, void *context);

void *reduce(const void *array, size_t size, size_t element_size, ReduceFunc func, void *initial_value, void *context);

#endif // REDUCE_H
