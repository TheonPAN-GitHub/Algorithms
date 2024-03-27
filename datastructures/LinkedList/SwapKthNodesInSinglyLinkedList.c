//
// Created by Theon on 2024/3/27.
//
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* newNode(int data) {
    Node *node = (Node *) malloc(sizeof(Node));
    if (node) {
        node->data = data;
        node->next = NULL;
    }else {
        printf("Error occurred when allocating memory.\n");
    }
    return node;
}

Node* push(Node **headRef, int data) {
    Node *node = newNode(data);
    if (node) {
        node->next = *headRef;
        *headRef = node;
    }
    return node;
}

Node* append(Node **headRef, int data) {
    Node *node = newNode(data);
    if (node) {
        while (*headRef && (*headRef)->next) {
            headRef = &((*headRef)->next);
        }
        if (NULL == *headRef) {
            *headRef = node;
        }else {
            (*headRef)->next = node;
        }
    }
    return node;
}

void printLinkedList(Node *head) {
    printf("The content of the linked list is: [ ");
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf(" ].\n");
}

int getLinkedListSize(Node *head) {
    int size = 0;
    while (head) {
        size ++;
        head = head->next;
    }
    return size;
}

Node** getKthNode(Node **headRef, int k) {
    int cnt = 1;
    while (*headRef) {
        if (cnt == k) {
            return headRef;
        }else{
            headRef = &((*headRef)->next);
            cnt++;
        }
    }
    return headRef;
}

void swap(Node **x, Node **y) {
    Node *tmp = *x;
    *x = *y;
    *y = tmp;
}

void swapKthNodes(Node **head, int k) {
    int size = getLinkedListSize(*head);
    if (k > size) {
        return;
    }
    int secondNodeIndex = size - k + 1;

    Node **a = getKthNode(head, k);
    Node **b = getKthNode(head, secondNodeIndex);
    if (a == b || (!a) || (!b)) {
        return;
    }
    swap(a, b);
    swap(&((*a)->next), &((*b)->next));
}

int main(){
    Node *linkedList = NULL;
    append(&linkedList, 5);
    append(&linkedList, 10);
    append(&linkedList, 8);
    append(&linkedList, 5);
    append(&linkedList, 9);
    append(&linkedList, 3);

    printLinkedList(linkedList);
    swapKthNodes(&linkedList, 5);
    printLinkedList(linkedList);
}
