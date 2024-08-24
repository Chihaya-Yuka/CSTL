#include "vector.h"

void vector_init(Vector *v) {
    v->size = 0;
    v->capacity = 10;
    v->data = (int *)malloc(v->capacity * sizeof(int));
}

void vector_push_back(Vector *v, int value) {
    if (v->size >= v->capacity) {
        v->capacity *= 2;
        v->data = (int *)realloc(v->data, v->capacity * sizeof(int));
    }
    v->data[v->size++] = value;
}

void vector_free(Vector *v) {
    free(v->data);
}

size_t vector_size(const Vector *v) {
    return v->size;
}

int vector_get(const Vector *v, size_t index) {
    if (index >= v->size) {
        // Handle out-of-bounds access (returning -1 or similar might be an option)
        return -1;
    }
    return v->data[index];
}

void vector_set(Vector *v, size_t index, int value) {
    if (index < v->size) {
        v->data[index] = value;
    }
}
