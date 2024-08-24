#include "map.h"
#include <stdlib.h>
#include <stdio.h>

#define HASH(key) ((key) % MAP_SIZE)

void map_init(Map *m) {
    for (size_t i = 0; i < MAP_SIZE; i++) {
        m->buckets[i] = NULL;
    }
}

void map_insert(Map *m, int key, int value) {
    size_t index = HASH(key);
    MapEntry *entry = (MapEntry *)malloc(sizeof(MapEntry));
    entry->key = key;
    entry->value = value;
    m->buckets[index] = entry;
}

int map_get(const Map *m, int key, int *value) {
    size_t index = HASH(key);
    if (m->buckets[index] != NULL && m->buckets[index]->key == key) {
        *value = m->buckets[index]->value;
        return 1;
    }
    return 0;
}

void map_remove(Map *m, int key) {
    size_t index = HASH(key);
    if (m->buckets[index] != NULL && m->buckets[index]->key == key) {
        free(m->buckets[index]);
        m->buckets[index] = NULL;
    }
}

void map_free(Map *m) {
    for (size_t i = 0; i < MAP_SIZE; i++) {
        free(m->buckets[i]);
    }
}
