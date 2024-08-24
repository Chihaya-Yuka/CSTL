#include "set.h"
#include <stdlib.h>

#define HASH(value) ((value) % SET_SIZE)

void set_init(Set *s) {
    for (size_t i = 0; i < SET_SIZE; i++) {
        s->buckets[i] = NULL;
    }
}

void set_insert(Set *s, int value) {
    size_t index = HASH(value);
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = s->buckets[index];
    s->buckets[index] = new_node;
}

int set_contains(const Set *s, int value) {
    size_t index = HASH(value);
    Node *current = s->buckets[index];
    while (current != NULL) {
        if (current->data == value) {
            return 1; // Value found
        }
        current = current->next;
    }
    return 0; // Value not found
}

void set_remove(Set *s, int value) {
    size_t index = HASH(value);
    Node *current = s->buckets[index];
    Node *previous = NULL;
    while (current != NULL) {
        if (current->data == value) {
            if (previous == NULL) {
                s->buckets[index] = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void set_free(Set *s) {
    for (size_t i = 0; i < SET_SIZE; i++) {
        Node *current = s->buckets[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
}
