#include "reduce.h"
#include <stddef.h>
#include <string.h>

void *reduce(const void *array, size_t size, size_t element_size, ReduceFunc func, void *initial_value, void *context) {
    void *accumulator = initial_value;
    for (size_t i = 0; i < size; i++) {
        void *current = (char *)array + i * element_size;
        accumulator = func(accumulator, current, context);
    }
    return accumulator;
}
