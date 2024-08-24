#include "map.h"
#include <stdlib.h>

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
    entry->next = m->buckets[index];
    m->buckets[index] = entry;
}

int map_get(const Map *m, int key, int *value) {
    size_t index = HASH(key);
    MapEntry *entry = m->buckets[index];
    while (entry != NULL) {
        if (entry->key == key) {
            *value = entry->value;
            return 1; // Key found
        }
        entry = entry->next;
    }
    return 0; // Key not found
}

void map_remove(Map *m, int key) {
    size_t index = HASH(key);
    MapEntry *entry = m->buckets[index];
    MapEntry *prev = NULL;
    while (entry != NULL) {
        if (entry->key == key) {
            if (prev == NULL) {
                m->buckets[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

void map_free(Map *m) {
    for (size_t i = 0; i < MAP_SIZE; i++) {
        MapEntry *entry = m->buckets[i];
        while (entry != NULL) {
            MapEntry *temp = entry;
            entry = entry->next;
            free(temp);
        }
    }
}
