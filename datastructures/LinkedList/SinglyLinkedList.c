//
// Created by Theon on 2024/1/17.
//
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

typedef struct Node * Head;
Head head_ref = NULL;

void push(int new_data) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = head_ref;
    head_ref = new_node;
}

void append(int new_data) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;

    if (head_ref == NULL) {
        head_ref = new_node;
        return;
    }

    struct Node *last_ref = head_ref;
    while (last_ref->next != NULL) {
        last_ref = last_ref->next;
    }
    last_ref->next = new_node;
    return;
}

struct Node* find(int position) {
    struct Node* cur_ref = head_ref;
    for (int i = 0; i < position; i++) {
        if (cur_ref == NULL) {
            return NULL;
        }
        cur_ref = cur_ref->next;
    }

    return cur_ref;
}

void insertAfter(struct Node *prevNode, int new_data) {
    if (prevNode == NULL) {
        printf("The given node can not be NULL.\n");
        return;
    }
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = prevNode->next;
    prevNode->next = new_node;
}

void deleteOneNodeFromHead() {
    if (head_ref == NULL) {
        printf("The linked list is empty, no node to delete.\n");
        return;
    }
    struct Node *temp_ref = head_ref;
    head_ref = head_ref->next;
    free(temp_ref);
}

void delete(int position) {
    if (head_ref == NULL) {
        printf("The linked list is empty, no node to delete.\n");
        return;
    }

    if (position == 0) {
        struct Node *temp_ref = head_ref;
        head_ref = head_ref->next;
        free(temp_ref);
    }
    struct Node *cur_ref = head_ref;
    struct Node *prev_ref = head_ref;
    for (int i = 0; i < position; i++) {
        if (cur_ref == NULL) {
            printf("The position is larger than the size of the linked list.\n");
            return;
        }
        prev_ref = cur_ref;
        cur_ref = cur_ref->next;
    }
    if (cur_ref != NULL) {
        struct Node *temp_ref = cur_ref;
        prev_ref->next = cur_ref->next;
        free(temp_ref);
    }
    return;
}

void printLinkedList(Head head_ref) {
    struct Node *cur_ref = head_ref;
    printf("The contents of the linked list is [");
    while (cur_ref != NULL) {
        printf("%d ", cur_ref->data);
        cur_ref = cur_ref->next;
    }
    printf("].\n");
}

int detectLoop(struct Node* list) {
    struct Node* slow_p = list;
    struct Node* fast_p = list;
    while(slow_p && fast_p && fast_p->next) {
        slow_p = slow_p->next;
        fast_p = fast_p->next->next;
        if (fast_p == slow_p) {
            return 1;
        }
    }
    return 0;
}
int main() {
    int A[] = {2, 3, 4, 6, 3, 5, 8};
    int size = sizeof(A) / sizeof(A[0]);
    for (int i = 0; i < size; i++) {
        append(A[i]);
    }
    if (head_ref == NULL) {
        printf("The linked list is empty.\n");
        return -1;
    }
    printLinkedList(head_ref);
    if (detectLoop(head_ref)) {
        printf("Loop found.\n");
    }else {
        printf("No loop.\n");
    }

    push(1);
    push(3);
    printLinkedList(head_ref);

    deleteOneNodeFromHead();
    deleteOneNodeFromHead();
    printLinkedList(head_ref);

    struct Node* node = find(5);
    if (node != NULL)
        printf("The value of node[%d] is %d.\n", 5, node->data);
    delete(5);
    printLinkedList(head_ref);
    head_ref->next->next->next->next = head_ref;
    if (detectLoop(head_ref)) {
        printf("Loop found.\n");
    }else {
        printf("No loop.\n");
    }


    return 0;
}
