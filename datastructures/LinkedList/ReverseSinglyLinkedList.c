//
// Created by Theon on 2024/1/19.
//
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void append(Node** list, int new_data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = new_data;

    if (*list == NULL) {
        new_node->next = *list;
        *list = new_node;
        return;
    }

    Node* cur_node_ref = *list;
    while(cur_node_ref->next != NULL) {
        cur_node_ref = cur_node_ref->next;
    }
    new_node->next = cur_node_ref->next;
    cur_node_ref->next = new_node;

    return;
}

void printLinkedList(Node* list) {
    Node* cur_node_ref = list;
    printf("The contents of the linked list is [");
    while (cur_node_ref != NULL) {
        printf("%d ", cur_node_ref->data);
        cur_node_ref = cur_node_ref->next;
    }
    printf("]\n");
}

void reverse(Node** list) {
    if (*list == NULL || (*list)->next == NULL) {
        return;
    }

    Node* ptr1 = *list;
    Node* ptr2 = (*list)->next;
    while (ptr2 != NULL) {
        if (ptr1 == *list) {
            ptr1->next = NULL;
        }
        Node* tmp = ptr2->next;
        ptr2->next = ptr1;
        ptr1 = ptr2;
        ptr2 = tmp;

        if (ptr2 == NULL) {
            *list = ptr1;
        }
    }

    return;
}

int main() {
    int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(A) / sizeof(A[0]);
    Node* list = NULL;
    for (int i = 0; i < size; i++) {
        append(&list, A[i]);
    }
    printLinkedList(list);
    reverse(&list);
    printLinkedList(list);
    return 0;
}
