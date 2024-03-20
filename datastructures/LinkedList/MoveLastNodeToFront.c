//
// Created by Theon on 2024/3/20.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* newNode(int data) {
    Node *node = (Node *) malloc(sizeof(Node));
    if (node) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}
Node* push(Node **head, int data){
    Node *node = newNode(data);
    if (NULL == node) {
        printf("Error occurred when allocating memory.\n");
        return NULL;
    }

    node->next = *head;
    *head = node;
    return node;
}

Node* append(Node **head, int data) {
    Node *node = newNode(data);
    if (NULL == node) {
        printf("Error occurred when allocating memory.\n");
        return NULL;
    }
    if (NULL == *head) {
        *head = node;
        return node;
    }
    Node *current = *head;
    while (current->next) {
        current = current->next;
    }
    node->next = current->next;
    current->next = node;
    return node;
}

void printLinkedList(Node *head) {
    printf("The content of the linked list [ ");
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("].\n");
}

void swap (Node **x, Node **y) {
    Node *tmp = *x;
    *x = *y;
    *y = tmp;
}

void moveLastToFront(Node **head) {
    Node **last = head;
    while (*last && (*last)->next) {
        last = &((*last)->next);
    }

    swap(head, last);
    swap(&((*head)->next), &((*last)->next));
}

int main(){
    Node *linkedList = NULL;
    for (int i = 1; i <= 10; i++) {
        append(&linkedList, i);
    }
    printf("Before moving: \n");
    printLinkedList(linkedList);

    moveLastToFront(&linkedList);

    printf("After moving: \n");
    printLinkedList(linkedList);

    moveLastToFront(&linkedList);
    printf("After moving: \n");
    printLinkedList(linkedList);
}
