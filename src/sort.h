#ifndef SORT_H
#define SORT_H

#include <stddef.h>

void sort(void *base, size_t nitems, size_t size,
          int (*compar)(const void *, const void *));

#endif // SORT_H