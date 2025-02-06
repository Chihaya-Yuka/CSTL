#ifndef CSTL_LIST_H
#define CSTL_LIST_H

#include "generic.h"

// 定义链表的泛型模板
#define CSTL_DEFINE_LIST(T, suffix) \
    CSTL_DEFINE_NODE(T, suffix); \
    \
    typedef struct List_##suffix { \
        Node_##suffix* head; \
        Node_##suffix* tail; \
        size_t size; \
        int (*compare)(T, T); \
    } List_##suffix; \
    \
    static inline List_##suffix* List_##suffix##_create(void) { \
        List_##suffix* list = (List_##suffix*)malloc(sizeof(List_##suffix)); \
        if (!list) return NULL; \
        \
        list->head = NULL; \
        list->tail = NULL; \
        list->size = 0; \
        list->compare = compare_##suffix; \
        return list; \
    } \
    \
    static inline void List_##suffix##_destroy(List_##suffix* list) { \
        if (!list) return; \
        \
        Node_##suffix* current = list->head; \
        while (current) { \
            Node_##suffix* next = current->next; \
            free(current); \
            current = next; \
        } \
        free(list); \
    } \
    \
    static inline CSTL_Error List_##suffix##_push_front(List_##suffix* list, T value) { \
        if (!list) return CSTL_ERROR_INVALID_ARGUMENT; \
        \
        Node_##suffix* node = (Node_##suffix*)malloc(sizeof(Node_##suffix)); \
        if (!node) return CSTL_ERROR_MEMORY; \
        \
        node->data = value; \
        node->next = list->head; \
        node->prev = NULL; \
        \
        if (list->head) \
            list->head->prev = node; \
        else \
            list->tail = node; \
        \
        list->head = node; \
        list->size++; \
        return CSTL_SUCCESS; \
    } \
    \
    static inline CSTL_Error List_##suffix##_push_back(List_##suffix* list, T value) { \
        if (!list) return CSTL_ERROR_INVALID_ARGUMENT; \
        \
        Node_##suffix* node = (Node_##suffix*)malloc(sizeof(Node_##suffix)); \
        if (!node) return CSTL_ERROR_MEMORY; \
        \
        node->data = value; \
        node->next = NULL; \
        node->prev = list->tail; \
        \
        if (list->tail) \
            list->tail->next = node; \
        else \
            list->head = node; \
        \
        list->tail = node; \
        list->size++; \
        return CSTL_SUCCESS; \
    } \
    \
    static inline CSTL_Error List_##suffix##_pop_front(List_##suffix* list) { \
        if (!list || !list->head) return CSTL_ERROR_EMPTY_CONTAINER; \
        \
        Node_##suffix* node = list->head; \
        list->head = node->next; \
        \
        if (list->head) \
            list->head->prev = NULL; \
        else \
            list->tail = NULL; \
        \
        free(node); \
        list->size--; \
        return CSTL_SUCCESS; \
    } \
    \
    static inline CSTL_Error List_##suffix##_pop_back(List_##suffix* list) { \
        if (!list || !list->tail) return CSTL_ERROR_EMPTY_CONTAINER; \
        \
        Node_##suffix* node = list->tail; \
        list->tail = node->prev; \
        \
        if (list->tail) \
            list->tail->next = NULL; \
        else \
            list->head = NULL; \
        \
        free(node); \
        list->size--; \
        return CSTL_SUCCESS; \
    } \
    \
    static inline size_t List_##suffix##_size(List_##suffix* list) { \
        return list ? list->size : 0; \
    } \
    \
    static inline T* List_##suffix##_front(List_##suffix* list) { \
        return (list && list->head) ? &list->head->data : NULL; \
    } \
    \
    static inline T* List_##suffix##_back(List_##suffix* list) { \
        return (list && list->tail) ? &list->tail->data : NULL; \
    }

// 预定义常用类型的链表
CSTL_DEFINE_LIST(int, int)
CSTL_DEFINE_LIST(float, float)
CSTL_DEFINE_LIST(double, double)
CSTL_DEFINE_LIST(char, char)
CSTL_DEFINE_LIST(char*, string)

#endif // CSTL_LIST_H
