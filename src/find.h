#ifndef FIND_H
#define FIND_H

#include <stddef.h>

void* find(const void *base, size_t nitems, size_t size,
           const void *key, int (*compar)(const void *, const void *));

#endif // FIND_H
