#include "find.h"
#include <string.h>

void* find(const void *base, size_t nitems, size_t size,
           const void *key, int (*compar)(const void *, const void *)) {
    for (size_t i = 0; i < nitems; i++) {
        void *item = (char*)base + i * size;
        if (compar(item, key) == 0) {
            return item;
        }
    }
    return NULL;
}
