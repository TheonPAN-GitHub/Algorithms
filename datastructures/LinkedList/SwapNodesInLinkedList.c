//
// Created by Theon on 2024/3/19.
//
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* newNode(int data) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

Node* push(Node **head, int data) {
    Node *node = newNode(data);
    node->next = *head;
    *head = node;
    return node;
}

Node *append(Node **head, int data) {
    Node *node = newNode(data);
    if (*head == NULL) {
        *head = node;
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
    Node *current = head;
    while(current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf(" ].\n");
}

/**
    The naive approach.
 */
void swapNodes(Node **head, int x, int y) {
    if (*head == NULL || x == y) {
        return;
    }

    //Find the position of x, the prev ptr and current ptr
    Node *prev_x = NULL, *current_x = *head;
    while (current_x != NULL && current_x->data != x) {
        prev_x = current_x;
        current_x = current_x->next;
    }
    //Find no x
    if (current_x == NULL) return;

    //Find the position of y, the prev ptr and current ptr
    Node *prev_y = NULL, *current_y = *head;
    while (current_y != NULL && current_y->data != y) {
        prev_y = current_y;
        current_y = current_y->next;
    }
    //Find no y
    if (current_y == NULL) return;

    if (prev_x) {
        prev_x->next = current_y;
    }else {
        *head = current_y;
    }

    if (prev_y) {
        prev_y->next = current_x;
    }else {
        *head = current_x;
    }

    Node *tmp = current_x->next;
    current_x->next = current_y->next;
    current_y->next = tmp;
}

void swap(Node **x, Node **y) {
    Node *tmp = *x;
    *x = *y;
    *y = tmp;
}

/**
     More efficient approach.
 */
void swapNodesInOneTraversal(Node **head, int x, int y) {
    if (x == y) {
        return;
    }

    Node **a = NULL, **b = NULL;
    while (*head) {
        if ((*head)->data == x) {
            a = head;
        }else if ((*head)->data == y) {
            b = head;
        }
        head = &((*head)->next);
    }

    if (a && b) {
        swap(a, b);
        swap(&((*a)->next), &((*b)->next));
    }
}

int main() {
    Node *linkedList = NULL;
    push(&linkedList, 7);
    push(&linkedList, 6);
    push(&linkedList, 5);
    push(&linkedList, 4);
    push(&linkedList, 3);
    push(&linkedList, 2);
    push(&linkedList, 1);

    printf("Before swapping: \n");
    printLinkedList(linkedList);
    swapNodesInOneTraversal(&linkedList, 5, 7);

    printf("After swapping: \n");
    printLinkedList(linkedList);

}
