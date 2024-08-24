#include "filter.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void *filter(const void *array, size_t size, size_t element_size, PredicateFunc pred, void *context, size_t *result_size) {
    if (size == 0) {
        *result_size = 0;
        return NULL;
    }
    
    size_t capacity = size;
    void *result = malloc(capacity * element_size);
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        void *current = (char *)array + i * element_size;
        if (pred(current, context)) {
            if (count >= capacity) {
                capacity *= 2;
                void *temp = realloc(result, capacity * element_size);
                if (temp == NULL) {
                    free(result);
                    *result_size = 0;
                    return NULL;
                }
                result = temp;
            }
            memcpy((char *)result + count * element_size, current, element_size);
            count++;
        }
    }

    *result_size = count;
    return result;
}
