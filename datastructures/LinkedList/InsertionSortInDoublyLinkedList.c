//
// Created by Theon on 2024/3/28.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev, *next;
} Node;

Node* newNode(int data) {
    Node *node = (Node *) malloc(sizeof(Node));
    if (node) {
        node->data = data;
        node->prev = node->next = NULL;
    }else {
        printf("Error occurred when allocating memory.\n");
    }
    return node;
}

Node* push(Node **headRef, int data) {
    Node *node = newNode(data);
    if (node) {
        if (*headRef) {
            (*headRef)->prev = node;
        }
        node->next = *headRef;
        *headRef = node;
    }
    return node;
}

Node* append(Node **headRef, int data) {
    Node *node = newNode(data);
    if (node) {
        if (NULL == *headRef) {
            *headRef = node;
        }else {
            while((*headRef)->next) {
                headRef = &((*headRef)->next);
            }
            (*headRef)->next = node;
            node->prev = (*headRef);
        }
    }
    return node;
}

void printDoublyLinkedList(Node *head) {
    Node *tail = NULL;
    printf("The content of doubly linked list is [ ");
    while (head){
        printf("%d ",head->data);
        if (NULL == head->next){
            tail = head;
        }
        head = head->next;
    }
    printf("]\n");

    printf("The reversed content of doubly linked list is [ ");
    while (tail) {
        printf("%d ", tail->data);
        tail = tail->prev;
    }
    printf("]\n");
}


void swapUtil(Node **headRef, Node *a, Node *b) {
    Node *tmp_a_prev = a->prev;
    Node *tmp_a_next = a->next;
    a->next = b->next;
    if (b->prev != a) {
        a->prev = b->prev;
    }else {
        a->prev = b;
    }

    if (tmp_a_next != b) {
        b->next = tmp_a_next;
    }else {
        b->next = a;
    }
    b->prev = tmp_a_prev;

    if (a->prev && a->prev != b) {
        a->prev->next = a;
    }
    if (a->next) {
        a->next->prev = a;
    }
    if(b->prev){
        b->prev->next = b;
    }
    if (b->next && b->next != a) {
        b->next->prev = b;
    }

    if (b->prev == NULL) {
        *headRef = b;
    }else if (a->prev == NULL) {
        *headRef = a;
    }
}

void swap(Node **headRef, Node *a, Node *b) {
    //As per two node are adjacent, need to order the params by the order in the list to swapUtil.
    if (b->next == a) {
        swapUtil(headRef, b, a);
    }else {
        swapUtil(headRef, a, b);
    }
}

void insertionSort(Node **headRef){
    if (*headRef == NULL) {
        return;
    }
    for (Node *i = (*headRef)->next; i != NULL; i = i->next) {
        Node *j = i;
        while(j->prev && j->data < j->prev->data) {
            swap(headRef, j, j->prev);
        }
    }
}

int main() {
    Node *doublyLinkedList1 = NULL;
    push(&doublyLinkedList1, 8);
    push(&doublyLinkedList1, 56);
    push(&doublyLinkedList1, 12);
    push(&doublyLinkedList1, 2);
    push(&doublyLinkedList1, 6);
    push(&doublyLinkedList1, 3);

    printDoublyLinkedList(doublyLinkedList1);
    insertionSort(&doublyLinkedList1);
    //swap(&doublyLinkedList1, doublyLinkedList1->next->next->next->next->next, doublyLinkedList1->next);
    printDoublyLinkedList(doublyLinkedList1);

    Node *doublyLinkedList2 = NULL;
    append(&doublyLinkedList2, 5);
    append(&doublyLinkedList2, 8);
    append(&doublyLinkedList2, 13);
    append(&doublyLinkedList2, 7);
    append(&doublyLinkedList2, 9);
    append(&doublyLinkedList2, 10);

    printDoublyLinkedList(doublyLinkedList2);
    insertionSort(&doublyLinkedList2);
    printDoublyLinkedList(doublyLinkedList2);
}
