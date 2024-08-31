#include "list.h"
#include <stdlib.h>

void list_init(List_node **head) {
    *head = NULL;
}

void list_append(List_node **head, int data) {
    List_node *new_node = (List_node *)malloc(sizeof(List_node));
    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        List_node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void list_free(List_node *head) {
    List_node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

size_t list_size(const List_node *head) {
    size_t size = 0;
    const List_node *temp = head;
    while (temp != NULL) {
        size++;
        temp = temp->next;
    }
    return size;
}
