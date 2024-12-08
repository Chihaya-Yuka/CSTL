#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <stddef.h>

#define TYPE_INT     1
#define TYPE_FLOAT   2
#define TYPE_DOUBLE  3
#define TYPE_CHAR    4
#define TYPE_STRING  5

#define TEMPLATE_ASSERT_TYPE(actual, expected) \
    _Static_assert((actual) == (expected), "Type mismatch in template")

#define TEMPLATE_FUNC(func, type) _Generic((type), \
    int: func##_int, \
    float: func##_float, \
    double: func##_double, \
    char: func##_char, \
    char*: func##_string \
)

#define DEFINE_ARRAY_TEMPLATE(T, suffix) \
    typedef struct { \
        T* data; \
        size_t size; \
        size_t capacity; \
    } Array_##suffix; \
    \
    static inline Array_##suffix* Array_##suffix##_create(size_t initial_capacity) { \
        Array_##suffix* arr = (Array_##suffix*)malloc(sizeof(Array_##suffix)); \
        if (arr) { \
            arr->data = (T*)malloc(initial_capacity * sizeof(T)); \
            arr->size = 0; \
            arr->capacity = initial_capacity; \
        } \
        return arr; \
    } \
    \
    static inline void Array_##suffix##_destroy(Array_##suffix* arr) { \
        if (arr) { \
            free(arr->data); \
            free(arr); \
        } \
    } \
    \
    static inline int Array_##suffix##_push(Array_##suffix* arr, T value) { \
        if (arr->size >= arr->capacity) { \
            size_t new_capacity = arr->capacity * 2; \
            T* new_data = (T*)realloc(arr->data, new_capacity * sizeof(T)); \
            if (!new_data) return 0; \
            arr->data = new_data; \
            arr->capacity = new_capacity; \
        } \
        arr->data[arr->size++] = value; \
        return 1; \
    } \
    \
    static inline T Array_##suffix##_get(Array_##suffix* arr, size_t index) { \
        if (index >= arr->size) { \
            /* Handle error case */ \
            T zero = {0}; \
            return zero; \
        } \
        return arr->data[index]; \
    } \
    \
    static inline void Array_##suffix##_set(Array_##suffix* arr, size_t index, T value) { \
        if (index < arr->size) { \
            arr->data[index] = value; \
        } \
    }

#define DEFINE_LIST_NODE_TEMPLATE(T, suffix) \
    typedef struct ListNode_##suffix { \
        T data; \
        struct ListNode_##suffix* next; \
    } ListNode_##suffix; \
    \
    typedef struct { \
        ListNode_##suffix* head; \
        size_t size; \
    } List_##suffix; \
    \
    static inline List_##suffix* List_##suffix##_create(void) { \
        List_##suffix* list = (List_##suffix*)malloc(sizeof(List_##suffix)); \
        if (list) { \
            list->head = NULL; \
            list->size = 0; \
        } \
        return list; \
    } \
    \
    static inline void List_##suffix##_destroy(List_##suffix* list) { \
        if (!list) return; \
        ListNode_##suffix* current = list->head; \
        while (current) { \
            ListNode_##suffix* next = current->next; \
            free(current); \
            current = next; \
        } \
        free(list); \
    } \
    \
    static inline int List_##suffix##_push_front(List_##suffix* list, T value) { \
        ListNode_##suffix* node = (ListNode_##suffix*)malloc(sizeof(ListNode_##suffix)); \
        if (!node) return 0; \
        node->data = value; \
        node->next = list->head; \
        list->head = node; \
        list->size++; \
        return 1; \
    }

DEFINE_ARRAY_TEMPLATE(int, int)
DEFINE_ARRAY_TEMPLATE(float, float)
DEFINE_ARRAY_TEMPLATE(double, double)
DEFINE_ARRAY_TEMPLATE(char, char)
DEFINE_ARRAY_TEMPLATE(char*, string)

DEFINE_LIST_NODE_TEMPLATE(int, int)
DEFINE_LIST_NODE_TEMPLATE(float, float)
DEFINE_LIST_NODE_TEMPLATE(double, double)
DEFINE_LIST_NODE_TEMPLATE(char, char)
DEFINE_LIST_NODE_TEMPLATE(char*, string)

#define DEFINE_COMPARE_TEMPLATE(T, suffix) \
    static inline int compare_##suffix(T a, T b) { \
        return (a < b) ? -1 : (a > b) ? 1 : 0; \
    }

DEFINE_COMPARE_TEMPLATE(int, int)
DEFINE_COMPARE_TEMPLATE(float, float)
DEFINE_COMPARE_TEMPLATE(double, double)
DEFINE_COMPARE_TEMPLATE(char, char)

static inline int compare_string(const char* a, const char* b) {
    return strcmp(a, b);
}

#endif // TEMPLATE_H