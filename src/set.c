#include "set.h"
#include <stdlib.h>
#include <stdio.h>

#define HASH(value) ((value) % SET_SIZE)

void set_init(Set *s) {
    for (size_t i = 0; i < SET_SIZE; i++) {
        s->buckets[i] = NULL;
    }
    s->size = 0;
}

void set_insert(Set *s, int value) {
    size_t index = HASH(value);
    if (s->buckets[index] == NULL) {
        s->buckets[index] = (int *)malloc(sizeof(int));
        *s->buckets[index] = value;
        s->size++;
    }
}

int set_contains(const Set *s, int value) {
    size_t index = HASH(value);
    return s->buckets[index] != NULL && *s->buckets[index] == value;
}

void set_remove(Set *s, int value) {
    size_t index = HASH(value);
    if (s->buckets[index] != NULL && *s->buckets[index] == value) {
        free(s->buckets[index]);
        s->buckets[index] = NULL;
        s->size--;
    }
}

void set_free(Set *s) {
    for (size_t i = 0; i < SET_SIZE; i++) {
        free(s->buckets[i]);
    }
}
