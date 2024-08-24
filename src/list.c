#include "list.h"
#include <stdlib.h>

void list_init(Node **head) {
    *head = NULL;
}

void list_append(Node **head, int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void list_free(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

size_t list_size(const Node *head) {
    size_t size = 0;
    const Node *temp = head;
    while (temp != NULL) {
        size++;
        temp = temp->next;
    }
    return size;
}
