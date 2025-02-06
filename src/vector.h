#ifndef CSTL_VECTOR_H
#define CSTL_VECTOR_H

#include "generic.h"

// 定义向量容器的泛型模板
#define CSTL_DEFINE_VECTOR(T, suffix) \
    typedef struct Vector_##suffix { \
        T* data; \
        size_t size; \
        size_t capacity; \
        int (*compare)(T, T); \
    } Vector_##suffix; \
    \
    static inline Vector_##suffix* Vector_##suffix##_create(size_t initial_capacity) { \
        Vector_##suffix* vec = (Vector_##suffix*)malloc(sizeof(Vector_##suffix)); \
        if (!vec) return NULL; \
        \
        vec->data = (T*)malloc(initial_capacity * sizeof(T)); \
        if (!vec->data) { \
            free(vec); \
            return NULL; \
        } \
        \
        vec->size = 0; \
        vec->capacity = initial_capacity; \
        vec->compare = compare_##suffix; \
        return vec; \
    } \
    \
    static inline void Vector_##suffix##_destroy(Vector_##suffix* vec) { \
        if (vec) { \
            free(vec->data); \
            free(vec); \
        } \
    } \
    \
    static inline CSTL_Error Vector_##suffix##_push_back(Vector_##suffix* vec, T value) { \
        if (!vec) return CSTL_ERROR_INVALID_ARGUMENT; \
        \
        if (vec->size >= vec->capacity) { \
            size_t new_capacity = vec->capacity * 2; \
            T* new_data = (T*)realloc(vec->data, new_capacity * sizeof(T)); \
            if (!new_data) return CSTL_ERROR_MEMORY; \
            \
            vec->data = new_data; \
            vec->capacity = new_capacity; \
        } \
        \
        vec->data[vec->size++] = value; \
        return CSTL_SUCCESS; \
    } \
    \
    static inline CSTL_Error Vector_##suffix##_pop_back(Vector_##suffix* vec) { \
        if (!vec || vec->size == 0) return CSTL_ERROR_EMPTY_CONTAINER; \
        \
        vec->size--; \
        return CSTL_SUCCESS; \
    } \
    \
    static inline T* Vector_##suffix##_at(Vector_##suffix* vec, size_t index) { \
        if (!vec || index >= vec->size) return NULL; \
        return &vec->data[index]; \
    } \
    \
    static inline size_t Vector_##suffix##_size(Vector_##suffix* vec) { \
        return vec ? vec->size : 0; \
    } \
    \
    static inline CSTL_Error Vector_##suffix##_clear(Vector_##suffix* vec) { \
        if (!vec) return CSTL_ERROR_INVALID_ARGUMENT; \
        vec->size = 0; \
        return CSTL_SUCCESS; \
    } \
    \
    static inline CSTL_Error Vector_##suffix##_resize(Vector_##suffix* vec, size_t new_size) { \
        if (!vec) return CSTL_ERROR_INVALID_ARGUMENT; \
        \
        if (new_size > vec->capacity) { \
            T* new_data = (T*)realloc(vec->data, new_size * sizeof(T)); \
            if (!new_data) return CSTL_ERROR_MEMORY; \
            \
            vec->data = new_data; \
            vec->capacity = new_size; \
        } \
        \
        vec->size = new_size; \
        return CSTL_SUCCESS; \
    }

// 预定义常用类型的向量
CSTL_DEFINE_VECTOR(int, int)
CSTL_DEFINE_VECTOR(float, float)
CSTL_DEFINE_VECTOR(double, double)
CSTL_DEFINE_VECTOR(char, char)
CSTL_DEFINE_VECTOR(char*, string)

#endif // CSTL_VECTOR_H
