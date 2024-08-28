#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct List_node_t {
    int data;
    struct List_node_t *next;
} List_node;

void list_init(List_node **head);
void list_append(List_node **head, int data);
void list_free(List_node *head);
size_t list_size(const List_node *head);

#endif // LIST_H
