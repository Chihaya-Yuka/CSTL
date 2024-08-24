#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Vector;

void vector_init(Vector *v);
void vector_push_back(Vector *v, int value);
void vector_free(Vector *v);
size_t vector_size(const Vector *v);
int vector_get(const Vector *v, size_t index);
void vector_set(Vector *v, size_t index, int value);

#endif // VECTOR_H
