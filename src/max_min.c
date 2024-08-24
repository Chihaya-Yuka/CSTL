#include "max_min.h"
#include <stddef.h>
#include <string.h>

void *find_max(const void *array, size_t size, size_t element_size, CompareFunc cmp) {
    if (size == 0) return NULL;
    
    void *max = (void *)array;
    for (size_t i = 1; i < size; i++) {
        void *current = (char *)array + i * element_size;
        if (cmp(current, max) > 0) {
            max = current;
        }
    }
    return max;
}

void *find_min(const void *array, size_t size, size_t element_size, CompareFunc cmp) {
    if (size == 0) return NULL;
    
    void *min = (void *)array;
    for (size_t i = 1; i < size; i++) {
        void *current = (char *)array + i * element_size;
        if (cmp(current, min) < 0) {
            min = current;
        }
    }
    return min;
}
