//
// Created by Theon on 2024/3/26.
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
    }else {
        printf("Error occurred when allocating memory.\n");
    }
    return node;
}

Node* push(Node **head, int data) {
    Node *node = newNode(data);
    if (node) {
        node->next = (*head);
        *head = node;
    }
    return node;
}

Node* append(Node **head, int data) {
    Node *node = newNode(data);
    if (node) {
        if (*head) {
            while ((*head)->next) {
                head = &((*head)->next);
            }
            (*head)->next = node;
        }else {
            (*head) = node;
        }
    }
    return node;
}

void printSinglyLinkedList(Node *head) {
    printf("The content of the singly linked list is [");
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("]\n");
}

int FrontBackSplit(Node *head, Node **frontRef, Node **backRef){
    if (head){
        Node *slow = head, *fast = head->next;
        while (fast) {
            fast = fast->next;
            if (fast) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        *frontRef = head;
        *backRef = slow->next;
        slow->next = NULL;
        return 1;
    }else {
        return 0;
    }
}

Node* sortedMerge(Node *a, Node *b) {
    Node *result = NULL;

    if (a == NULL) {
        return b;
    }else if (b == NULL) {
        return a;
    }

    if (a->data <= b->data) {
        result = a;
        result->next = sortedMerge(a->next, b);
    }else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return result;
}

void mergeSort(Node **headRef) {
    Node *head = *headRef;
    Node *a = NULL;
    Node *b = NULL;

    if (head == NULL || head->next == NULL) {
        return;
    }

    if (FrontBackSplit(head, &a, &b)) {
        mergeSort(&a);
        mergeSort(&b);
        *headRef = sortedMerge(a, b);
    }
}

int main() {
    Node *singlyLinkedList = NULL;
    push(&singlyLinkedList, 15);
    push(&singlyLinkedList, 10);
    push(&singlyLinkedList, 5);
    push(&singlyLinkedList, 20);
    push(&singlyLinkedList, 3);
    push(&singlyLinkedList, 2);

    printf("Before sorting:\n");
    printSinglyLinkedList(singlyLinkedList);

    mergeSort(&singlyLinkedList);

    printf("After sorting:\n");
    printSinglyLinkedList(singlyLinkedList);
}


