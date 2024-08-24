#ifndef REMOVE_H
#define REMOVE_H

#include <stddef.h>

size_t remove_if(void *base, size_t nitems, size_t size,
                 int (*predicate)(const void *));

#endif // REMOVE_H