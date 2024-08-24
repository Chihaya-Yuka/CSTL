#ifndef MAP_H
#define MAP_H

#include <stddef.h>

#define MAP_SIZE 101

typedef struct {
    int key;
    int value;
} MapEntry;

typedef struct {
    MapEntry *buckets[MAP_SIZE];
} Map;

void map_init(Map *m);
void map_insert(Map *m, int key, int value);
int map_get(const Map *m, int key, int *value);
void map_remove(Map *m, int key);
void map_free(Map *m);

#endif // MAP_H
