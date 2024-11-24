#include "flat_set.h"
#include <stdlib.h>

void flat_set_init(FlatSet *set, int capacity) {
    set->elements = (int *)malloc(capacity * sizeof(int));
    set->size = 0;
    set->capacity = capacity;
}

void flat_set_insert(FlatSet *set, int value) {
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i] == value) {
            return;
        }
    }
    if (set->size < set->capacity) {
        set->elements[set->size++] = value;
    }
}

int flat_set_contains(FlatSet *set, int value) {
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i] == value) {
            return 1;
        }
    }
    return 0;
}

void flat_set_free(FlatSet *set) {
    free(set->elements);
}
