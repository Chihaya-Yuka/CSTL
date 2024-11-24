#ifndef FLAT_MAP_H
#define FLAT_MAP_H

typedef struct {
    int key;
    int value;
} FlatMapEntry;

typedef struct {
    FlatMapEntry *entries;
    int size;
    int capacity;
} FlatMap;

void flat_map_init(FlatMap *map, int capacity);
void flat_map_insert(FlatMap *map, int key, int value);
int flat_map_get(FlatMap *map, int key);
void flat_map_free(FlatMap *map);

#endif // FLAT_MAP_H
