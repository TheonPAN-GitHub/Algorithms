//
// Created by Theon on 2024/1/19.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

void append(Node** list, int new_data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = new_data;

    if (*list == NULL) {
        new_node->next = *list;
        *list = new_node;
        new_node->prev = NULL;
        return;
    }

    Node* cur_node_ref = *list;
    while(cur_node_ref->next != NULL) {
        cur_node_ref = cur_node_ref->next;
    }
    new_node->next = cur_node_ref->next;
    new_node->prev = cur_node_ref;
    cur_node_ref->next = new_node;

    return;
}

void printLinkedList(Node* list) {
    Node* cur_node_list = list;
    printf("The contents of the linked list is [");
    while(cur_node_list != NULL) {
        printf("%d ", cur_node_list->data);
        cur_node_list = cur_node_list->next;
    }
    printf("]\n");
}

void reverse(Node** list) {
    Node* cur_node_ref = *list;

    while (cur_node_ref != NULL) {
        Node* tmp = cur_node_ref->next;
        cur_node_ref->next = cur_node_ref->prev;
        cur_node_ref->prev = tmp;

        if (cur_node_ref->prev == NULL) {
            *list = cur_node_ref;
        }
        cur_node_ref = cur_node_ref->prev;
    }
}

int main() {
    int A[] = {1,2, 3, 4, 5, 6, 7, 8};
    int size = sizeof(A) / sizeof(A[0]);
    Node* list = NULL;
    for (int i = 0; i < size; i++) {
        append(&list, A[i]);
    }
    printLinkedList(list);
    reverse(&list);
    printLinkedList(list);
}