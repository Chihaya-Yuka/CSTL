#include "sort.h"
#include <stdlib.h>

void sort(void *base, size_t nitems, size_t size,
          int (*compar)(const void *, const void *)) {
    qsort(base, nitems, size, compar);
}