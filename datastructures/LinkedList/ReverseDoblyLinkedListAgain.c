//
// Created by Theon on 2024/3/25.
//
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *prev, *next;
} Node;

Node* newNode(int data) {
    Node *node = (Node *) malloc(sizeof(Node));
    if (node) {
        node->data = data;
        node->next = node->prev = NULL;
    }
    return node;
}

Node* push(Node **head, int data) {
    Node *node = newNode(data);
    if (node == NULL) {
        return NULL;
    }

    node->next = *head;
    if (*head) {
        (*head)->prev = node;
    }
    *head = node;
    return node;
}

Node* insertBefore(Node **head, int beforeData, int data) {
    if (*head == NULL) {
        return NULL;
    }
    Node *node = newNode(data);
    if (node == NULL) {
        printf("Error occurred when allocating memory.\n");
        return NULL;
    }

    Node *current_node = *head;
    while (current_node && current_node->data != beforeData) {
        current_node = current_node->next;
    }
    if (current_node == NULL) {
        printf("Can not find the before node.\n");
        return NULL;
    }

    node->next = current_node;
    node->prev = current_node->prev;
    if (current_node->prev) {
        current_node->prev->next = node;
    }
    current_node->prev = node;


    if (current_node == *head) {
        *head = node;
    }

    return node;
}

Node* insertAfter(Node **head, int afterData, int data) {
    while(*head && (*head)->data != afterData) {
        head = &((*head)->next);
    }
    if (*head == NULL) {
        printf("Can not find the after node.\n");
        return NULL;
    }
    Node *node = newNode(data);
    if (node == NULL) {
        printf("Error occurred when allocating memory.\n");
        return NULL;
    }

    node->next = (*head)->next;
    node->prev = (*head);
    if ((*head)->next) {
        (*head)->next->prev = node;
    }
    (*head)->next = node;

    return node;
}

Node* delete(Node **head, int data) {
    Node *current_node = *head;
    while (current_node && current_node->data != data) {
        current_node = current_node->next;
    }
    if (current_node == NULL) {
        printf("Can not find the node to delete.\n");
        return NULL;
    }
    if (current_node->prev) {
        current_node->prev->next = current_node->next;
    }
    if (current_node->next) {
        current_node->next->prev = current_node->prev;
    }
    if (current_node == (*head)) {
        (*head) = current_node->next;
    }
    current_node->next = NULL;
    current_node->prev = NULL;

    return current_node;
}

Node* append(Node **head, int data) {
    Node *node = newNode(data);
    if (node == NULL) {
        printf("Error occurred when allocating memory.\n");
        return NULL;
    }

    if (*head == NULL) {
        *head = node;
        return node;
    }
    while ((*head)->next) {
        head = &((*head)->next);
    }
    (*head)->next = node;
    node->prev = (*head);
    return node;
}

void printDoublyLinkedList(Node *head) {
    Node *tail = NULL;
    printf("The content of the doubly linked list is [ ");
    while (head) {
        printf("%d ", head->data);
        if (head->next == NULL) {
            tail = head;
        }
        head = head->next;
    }
    printf("]\n");

    printf("The reversely traverse of the doubly linked list is [ ");
    while (tail) {
        printf("%d ", tail->data);
        tail = tail->prev;
    }
    printf("].\n");
}

int main() {
    Node *doublyLinkedList = NULL;
    append(&doublyLinkedList, 1);
    append(&doublyLinkedList, 2);
    append(&doublyLinkedList, 3);
    append(&doublyLinkedList, 4);
    append(&doublyLinkedList, 5);
    append(&doublyLinkedList, 6);
    printDoublyLinkedList(doublyLinkedList);

    Node* node = delete(&doublyLinkedList, 6);
    if (node){
        free(node);
    }
    printDoublyLinkedList(doublyLinkedList);

//    Node *doublyLinkedList1 = NULL;
//    push(&doublyLinkedList1, 6);
//    push(&doublyLinkedList1, 5);
//    push(&doublyLinkedList1, 4);
//    push(&doublyLinkedList1, 3);
//    push(&doublyLinkedList1, 2);
//    push(&doublyLinkedList1, 1);

//    printDoublyLinkedList(doublyLinkedList1);
}
