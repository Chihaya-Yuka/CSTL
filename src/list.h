#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void list_init(Node **head);
void list_append(Node **head, int data);
void list_free(Node *head);
size_t list_size(const Node *head);

#endif // LIST_H
