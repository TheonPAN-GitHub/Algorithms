//
// Created by Theon on 2024/1/18.
//
#include <stdio.h>
#include <stdlib.h>
#define MAX_BITMAP_SIZE 1000

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void push(Node** head_ref, int new_data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = *head_ref;
    *head_ref = new_node;
    return;
}

void append(Node** head_ref, int new_data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    Node* cur_node_ref = *head_ref;
    while (cur_node_ref->next != NULL) {
        cur_node_ref = cur_node_ref->next;
    }
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
    return;
}
/**
    The Naive approach.
 */
void removeDuplicates(Node** list) {
    Node* ptr1 = *list;
    while (ptr1 && ptr1->next) {
        Node* ptr2 = ptr1;
        while (ptr2->next) {
            if (ptr1->data == ptr2->next->data) {
                Node* dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                free(dup);
            }else {
                ptr2 = ptr2->next;
            }
        }
        ptr1 = ptr1->next;
    }
}

/**
    This approach uses a bitmap to check if a node is duplicated.
 */

int isDuplicated(int* bitmap, Node* node) {
    if (node == NULL) {
        return 0;
    }

    return bitmap[node->data];
}

void removeDuplicatesUsingBitmap(Node** list) {
    int* bitmap = (int *) calloc(MAX_BITMAP_SIZE, sizeof(int));
    Node* cur_node_ref = *list;
    bitmap[cur_node_ref->data] = 1;
    while (cur_node_ref->next) {
        if (isDuplicated(bitmap, cur_node_ref->next)) {
            Node* dup = cur_node_ref->next;
            cur_node_ref->next = cur_node_ref->next->next;
            free(dup);
        }else {
            bitmap[cur_node_ref->next->data] = 1;
            cur_node_ref = cur_node_ref->next;
        }
    }
    free(bitmap);
}


int main() {
    int A[] = {10, 12, 11, 11, 12, 11, 10, 13,14, 13};
    int size = sizeof(A) / sizeof(A[0]);
    Node* list = NULL;
    for (int i = 0; i < size; i++) {
        append(&list, A[i]);
    }
    printLinkedList(list);
    removeDuplicatesUsingBitmap(&list);
    printLinkedList(list);

}
