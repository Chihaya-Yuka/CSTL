#ifndef CSTL_GENERIC_H
#define CSTL_GENERIC_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// 定义通用的类型标识符
#define CSTL_TYPE_INT      1
#define CSTL_TYPE_FLOAT    2
#define CSTL_TYPE_DOUBLE   3
#define CSTL_TYPE_CHAR     4
#define CSTL_TYPE_STRING   5
#define CSTL_TYPE_CUSTOM   6

// 泛型容器元素定义
#define CSTL_GENERIC_TYPE(T) \
    struct { \
        T value; \
        int type_id; \
    }

// 泛型比较函数定义
#define CSTL_DEFINE_COMPARE(T, suffix) \
    static inline int compare_##suffix(T a, T b) { \
        return (a < b) ? -1 : (a > b) ? 1 : 0; \
    }

// 泛型哈希函数定义
#define CSTL_DEFINE_HASH(T, suffix) \
    static inline size_t hash_##suffix(T key) { \
        return (size_t)key; \
    }

// 泛型内存操作
#define CSTL_GENERIC_COPY(dest, src, type) \
    memcpy((dest), (src), sizeof(type))

#define CSTL_GENERIC_MOVE(dest, src, type) \
    do { \
        CSTL_GENERIC_COPY(dest, src, type); \
        memset((src), 0, sizeof(type)); \
    } while(0)

// 泛型容器节点定义
#define CSTL_DEFINE_NODE(T, suffix) \
    typedef struct Node_##suffix { \
        T data; \
        struct Node_##suffix* next; \
        struct Node_##suffix* prev; \
    } Node_##suffix

// 泛型迭代器定义
#define CSTL_DEFINE_ITERATOR(T, suffix) \
    typedef struct Iterator_##suffix { \
        T* current; \
        void* container; \
        int (*next)(struct Iterator_##suffix*); \
        int (*prev)(struct Iterator_##suffix*); \
        T* (*get)(struct Iterator_##suffix*); \
    } Iterator_##suffix

// 泛型容器基础定义
#define CSTL_DEFINE_CONTAINER(T, suffix) \
    typedef struct Container_##suffix { \
        T* data; \
        size_t size; \
        size_t capacity; \
        int type_id; \
        int (*compare)(T, T); \
        size_t (*hash)(T); \
    } Container_##suffix

// 泛型错误处理
typedef enum {
    CSTL_SUCCESS = 0,
    CSTL_ERROR_MEMORY,
    CSTL_ERROR_INVALID_ARGUMENT,
    CSTL_ERROR_OUT_OF_RANGE,
    CSTL_ERROR_EMPTY_CONTAINER
} CSTL_Error;

// 预定义基本类型的比较函数
CSTL_DEFINE_COMPARE(int, int)
CSTL_DEFINE_COMPARE(float, float)
CSTL_DEFINE_COMPARE(double, double)
CSTL_DEFINE_COMPARE(char, char)

// 字符串比较函数特化
static inline int compare_string(const char* a, const char* b) {
    return strcmp(a, b);
}

// 预定义基本类型的哈希函数
CSTL_DEFINE_HASH(int, int)
CSTL_DEFINE_HASH(float, float)
CSTL_DEFINE_HASH(double, double)
CSTL_DEFINE_HASH(char, char)

// 字符串哈希函数特化
static inline size_t hash_string(const char* key) {
    size_t hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

#endif // CSTL_GENERIC_H 