//
// Created by Theon on 2024/3/20.
//
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* newNode(int data) {
    Node *node = (Node *) malloc(sizeof(Node));
    if (node){
        node->data = data;
        node->next = NULL;
    }
    return node;
}

Node* push(Node **head, int data) {
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
    while ((*head)->next) {
        head = &((*head)->next);
    }
    node->next = (*head)->next;
    (*head)->next = node;
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

Node* intersect(Node *linkedList1, Node *linkedList2) {
    Node *intersection = NULL;
    while (linkedList1 && linkedList2) {
        if (linkedList1->data > linkedList2->data) {
            linkedList2 = linkedList2->next;
        }else if (linkedList1->data < linkedList2->data) {
            linkedList1 = linkedList1->next;
        }else {
            append(&intersection, linkedList1->data);
            linkedList1 = linkedList1->next;
            linkedList2 = linkedList2->next;
        }
    }
    return intersection;
}

Node* intersectRecursively(Node *linkedList1, Node *linkedList2) {
    if (NULL == linkedList1 || NULL == linkedList2) {
        return NULL;
    }

    if (linkedList1->data > linkedList2->data) {
        return intersectRecursively(linkedList1, linkedList2->next);
    }else if (linkedList1->data < linkedList2->data) {
        return intersectRecursively(linkedList1->next, linkedList2);
    }else {
        Node *node = newNode(linkedList1->data);
        node->next = intersectRecursively(linkedList1->next, linkedList2->next);
        return node;
    }
}

int main() {
    Node *linkedList1 = NULL, *linkedList2 = NULL;
    append(&linkedList1, 1);
    append(&linkedList1, 2);
    append(&linkedList1, 5);
    append(&linkedList1, 8);
    append(&linkedList1, 9);
    printLinkedList(linkedList1);

    append(&linkedList2, 2);
    append(&linkedList2, 5);
    append(&linkedList2, 8);
    //append(&linkedList2, 8);
    printLinkedList(linkedList2);

    Node *intersection = intersect(linkedList1, linkedList2);
    if (intersection) {
        printf("The intersection of the two linked list is: \n");
        printLinkedList(intersection);
    }else{
        printf("There's no intersection.\n");
    }

    printf("Intersecting recursively:\n");
    Node *intersection1 = intersectRecursively(linkedList1, linkedList2);
    if (intersection) {
        printf("The intersection of the two linked list is: \n");
        printLinkedList(intersection1);
    }else{
        printf("There's no intersection.\n");
    }

}