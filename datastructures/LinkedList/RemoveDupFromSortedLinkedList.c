//
// Created by Theon on 2024/3/18.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void push(Node **head, int data) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error occurred when memory allocating.\n");
        return;
    }
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

void append(Node **head, int data) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error occurred when memory allocating.\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;
    if (*head == NULL){
        *head = newNode;
        return;
    }
    Node *currentNode = *head;
    while (currentNode->next) {
        currentNode = currentNode->next;
    }
    newNode->next = currentNode->next;
    currentNode->next = newNode;
}

void printLinkedList(Node *head) {
    printf("The content of linked list is [ ");
    Node *currentNode = head;
    while (currentNode) {
        printf("%d ", currentNode->data);
        currentNode = currentNode->next;
    }
    printf("]\n");
}
/**
    The naive approach, using two pointers.
 */
void removeDuplicatesFromSortedLinkedList(Node **head) {
    if (*head == NULL) {
        return;
    }

    Node *ptr1 = *head, *ptr2 = (*head)->next;
    while (ptr2 != NULL) {
        if (ptr1->data == ptr2->data) {
            Node *temp = ptr2;
            ptr2 = ptr2->next;
            if (ptr2 == NULL) {
                ptr1->next = NULL;
            }
            free(temp);
        }else {
            ptr1->next = ptr2;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }
}

void removeDuplicatesMoreEfficiently(Node **head) {
    if (*head == NULL) {
        return;
    }

    Node *current = *head;
    Node *next_next = NULL;
    while (current->next) {
        if (current->data == current->next->data) {
            next_next = current->next->next;
            free(current->next);
            current->next = next_next;
        }else {
            current = current->next;
        }
    }
}

void removeDuplicatesRecursionUtil(Node **left, Node *right) {
    if (right == NULL) {
        return;
    }

    if ((*left)->data != right->data) {
        (*left) = (*left)->next;
    }else {
        Node *next_next = (*left)->next->next;
        free((*left)->next);
        (*left)->next = next_next;
    }
    removeDuplicatesRecursionUtil(left, (*left)->next);
}

void removeDuplicatesRecursively(Node *head) {
    Node *current = head;
    removeDuplicatesRecursionUtil(&current, current->next);
}

Node* removeDuplicatesRecursionMoreEfficiently(Node *head) {
    if (head == NULL) {
        return NULL;
    }
    if (head->next == NULL) {
        return head;
    }

    if (head->data == head->next->data) {
        Node *tmp = head->next;
        head->next = head->next->next;
        free(tmp);
        return removeDuplicatesRecursionMoreEfficiently(head);
    }else{
        head->next = removeDuplicatesRecursionMoreEfficiently(head->next);
        return head;
    }
}


int main() {
    int arr[] = {11, 11, 11, 21, 43, 43, 60, 70, 70, 90,90,100};
    int n = sizeof(arr) / sizeof(arr[0]);
    Node *linkedList = NULL;
    for (int i = 0; i < n; i++) {
        append(&linkedList, arr[i]);
    }
    printf("Linked list before removing duplicates:\n");
    printLinkedList(linkedList);

    linkedList = removeDuplicatesRecursionMoreEfficiently(linkedList);

    printf("Linked list after removing duplicates:\n");
    printLinkedList(linkedList);
}