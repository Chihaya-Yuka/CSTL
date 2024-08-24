#ifndef SET_H
#define SET_H

#include <stddef.h>

#define SET_SIZE 101

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *buckets[SET_SIZE];
} Set;

void set_init(Set *s);
void set_insert(Set *s, int value);
int set_contains(const Set *s, int value);
void set_remove(Set *s, int value);
void set_free(Set *s);

#endif // SET_H
