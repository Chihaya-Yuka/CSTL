#ifndef FLAT_SET_H
#define FLAT_SET_H

typedef struct {
    int *elements;
    int size;
    int capacity;
} FlatSet;

void flat_set_init(FlatSet *set, int capacity);
void flat_set_insert(FlatSet *set, int value);
int flat_set_contains(FlatSet *set, int value);
void flat_set_free(FlatSet *set);

#endif // FLAT_SET_H
