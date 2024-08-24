#include "remove.h"
#include <string.h>

size_t remove_if(void *base, size_t nitems, size_t size,
                 int (*predicate)(const void *)) {
    char *ptr = base;
    size_t new_size = 0;

    for (size_t i = 0; i < nitems; i++) {
        void *item = ptr + i * size;
        if (!predicate(item)) {
            if (i != new_size) {
                memmove(ptr + new_size * size, item, size);
            }
            new_size++;
        }
    }
    return new_size;
}