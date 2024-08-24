#include "copy.h"
#include <string.h>

void copy(const void *src, void *dst, size_t nitems, size_t size) {
    memcpy(dst, src, nitems * size);
}
