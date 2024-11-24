#include "flat_map.h"
#include <stdlib.h>

void flat_map_init(FlatMap *map, int capacity) {
    map->entries = (FlatMapEntry *)malloc(capacity * sizeof(FlatMapEntry));
    map->size = 0;
    map->capacity = capacity;
}

void flat_map_insert(FlatMap *map, int key, int value) {
    for (int i = 0; i < map->size; i++) {
        if (map->entries[i].key == key) {
            map->entries[i].value = value;
            return;
        }
    }
    if (map->size < map->capacity) {
        map->entries[map->size++] = (FlatMapEntry){key, value};
    }
}

int flat_map_get(FlatMap *map, int key) {
    for (int i = 0; i < map->size; i++) {
        if (map->entries[i].key == key) {
            return map->entries[i].value;
        }
    }
    return -1; // Not found
}

void flat_map_free(FlatMap *map) {
    free(map->entries);
}
