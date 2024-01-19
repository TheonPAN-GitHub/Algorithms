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

void push(Node** list, int new_data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->prev = NULL;
    new_node->next = *list;
    if ((*list)){
        (*list)->prev = new_node;
    }
    *list = new_node;
}

void insertAfter(Node* prev_node, int new_data) {
    if (prev_node == NULL) {
        printf("The given previous node cannot be NULL.\n");
        return;
    }
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
    new_node->prev = prev_node;
    if (new_node->next != NULL) {
        new_node->next->prev = new_node;
    }
}

void insertBefore(Node** list, Node* next_node, int new_data) {
    if (next_node == NULL) {
        printf("The given next node cannot be NULL.\n");
        return;
    }
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->prev = next_node->prev;
    new_node->next = next_node;
    next_node->prev = new_node;
    if (new_node->prev != NULL) {
        new_node->prev->next = new_node;
    }else{
        *list = new_node;
    }
}

void append(Node** list, int new_data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = new_data;
    if (*list == NULL) {
        new_node->prev = *list;
        new_node->next = NULL;
        *list = new_node;
        return;
    }

    Node* cur_node_ref = *list;
    while (cur_node_ref->next) {
        cur_node_ref = cur_node_ref->next;
    }

    new_node->next = cur_node_ref->next;
    cur_node_ref->next = new_node;
    new_node->prev = cur_node_ref;
}

void deleteNode(Node** list, Node* delNode) {
    if (*list == NULL || delNode == NULL) {
        return;
    }
    if (*list == delNode) {
        *list = delNode->next;
    }
    if (delNode->next){
        delNode->next->prev = delNode->prev;
    }
    if (delNode->prev) {
        delNode->prev->next = delNode->next;
    }
    free(delNode);
}

void deleteBeginningNode(Node** list) {
    if (*list == NULL) {
        return;
    }

    Node* delNode = *list;
    *list = delNode->next;
    if (delNode->next) {
        delNode->next->prev = NULL;
    }
    free(delNode);
}

void deleteEndNode(Node** list) {
    if (*list == NULL) {
        return;
    }

    Node* cur_node_ref = *list;
    while(cur_node_ref->next) {
        cur_node_ref = cur_node_ref->next;
    }

    cur_node_ref->prev->next = NULL;
    free(cur_node_ref);
}

void printLinkedList(Node* list) {
    Node* cur_node_ref = list;
    printf("The contents of the linked list is [");
    while(cur_node_ref) {
        printf("%d ", cur_node_ref->data);
        cur_node_ref = cur_node_ref->next;
    }
    printf("]\n");
}

int main() {
    int A[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int size = sizeof(A) / sizeof(A[0]);
    Node* list1 = NULL;
    for (int i = 0; i < size; i++) {
        append(&list1, A[i]);
    }
    printLinkedList(list1);

    Node* list2 = NULL;
    for (int i = 0; i < size; i++) {
        push(&list2, A[i]);
    }
    printLinkedList(list2);

    Node* cur_node_list = list1;
    while (cur_node_list) {
        if (cur_node_list->data == 1) {
            break;
        }
        cur_node_list = cur_node_list->next;
    }
    if (cur_node_list) {
        insertAfter(cur_node_list, 999);
        insertBefore(&list1, cur_node_list, 888);
        printLinkedList(list1);
        deleteBeginningNode(&list1);
        deleteNode(&list1, cur_node_list->next);
        deleteEndNode(&list1);
        printLinkedList(list1);
    }



}