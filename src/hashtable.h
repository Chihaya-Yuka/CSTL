#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// 哈希表节点模板
#define DEFINE_HASHTABLE_NODE_TEMPLATE(K, V, suffix) \
    typedef struct HashNode_##suffix { \
        K key; \
        V value; \
        struct HashNode_##suffix* next; \
    } HashNode_##suffix;

// 哈希表模板
#define DEFINE_HASHTABLE_TEMPLATE(K, V, suffix) \
    typedef struct { \
        HashNode_##suffix** buckets; \
        size_t size; \
        size_t capacity; \
        size_t (*hash_func)(K); \
        int (*compare_func)(K, K); \
    } HashTable_##suffix; \
    \
    static inline HashTable_##suffix* HashTable_##suffix##_create(size_t initial_capacity, \
            size_t (*hash_func)(K), int (*compare_func)(K, K)) { \
        HashTable_##suffix* table = (HashTable_##suffix*)malloc(sizeof(HashTable_##suffix)); \
        if (!table) return NULL; \
        \
        table->buckets = (HashNode_##suffix**)calloc(initial_capacity, sizeof(HashNode_##suffix*)); \
        if (!table->buckets) { \
            free(table); \
            return NULL; \
        } \
        \
        table->size = 0; \
        table->capacity = initial_capacity; \
        table->hash_func = hash_func; \
        table->compare_func = compare_func; \
        return table; \
    } \
    \
    static inline void HashTable_##suffix##_destroy(HashTable_##suffix* table) { \
        if (!table) return; \
        for (size_t i = 0; i < table->capacity; i++) { \
            HashNode_##suffix* current = table->buckets[i]; \
            while (current) { \
                HashNode_##suffix* next = current->next; \
                free(current); \
                current = next; \
            } \
        } \
        free(table->buckets); \
        free(table); \
    } \
    \
    static inline int HashTable_##suffix##_insert(HashTable_##suffix* table, K key, V value) { \
        if (!table) return 0; \
        \
        size_t index = table->hash_func(key) % table->capacity; \
        HashNode_##suffix* node = table->buckets[index]; \
        \
        while (node) { \
            if (table->compare_func(node->key, key) == 0) { \
                node->value = value; \
                return 1; \
            } \
            node = node->next; \
        } \
        \
        HashNode_##suffix* new_node = (HashNode_##suffix*)malloc(sizeof(HashNode_##suffix)); \
        if (!new_node) return 0; \
        \
        new_node->key = key; \
        new_node->value = value; \
        new_node->next = table->buckets[index]; \
        table->buckets[index] = new_node; \
        table->size++; \
        return 1; \
    } \
    \
    static inline int HashTable_##suffix##_get(HashTable_##suffix* table, K key, V* value) { \
        if (!table || !value) return 0; \
        \
        size_t index = table->hash_func(key) % table->capacity; \
        HashNode_##suffix* node = table->buckets[index]; \
        \
        while (node) { \
            if (table->compare_func(node->key, key) == 0) { \
                *value = node->value; \
                return 1; \
            } \
            node = node->next; \
        } \
        return 0; \
    } \
    \
    static inline int HashTable_##suffix##_remove(HashTable_##suffix* table, K key) { \
        if (!table) return 0; \
        \
        size_t index = table->hash_func(key) % table->capacity; \
        HashNode_##suffix* current = table->buckets[index]; \
        HashNode_##suffix* prev = NULL; \
        \
        while (current) { \
            if (table->compare_func(current->key, key) == 0) { \
                if (prev) \
                    prev->next = current->next; \
                else \
                    table->buckets[index] = current->next; \
                \
                free(current); \
                table->size--; \
                return 1; \
            } \
            prev = current; \
            current = current->next; \
        } \
        return 0; \
    }

// 为基本类型定义哈希函数
static inline size_t hash_int(int key) {
    return (size_t)key;
}

static inline size_t hash_string(const char* key) {
    size_t hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// 定义常用类型的哈希表
DEFINE_HASHTABLE_NODE_TEMPLATE(int, int, int_int)
DEFINE_HASHTABLE_NODE_TEMPLATE(char*, char*, string_string)
DEFINE_HASHTABLE_TEMPLATE(int, int, int_int)
DEFINE_HASHTABLE_TEMPLATE(char*, char*, string_string)

#endif // HASHTABLE_H 