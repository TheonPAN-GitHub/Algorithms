//
// Created by Theon on 2024/3/26.
//
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *prev, *next;
} Node;

Node *newNode(int data) {
    Node* node = (Node *) malloc(sizeof(Node));
    if (node) {
        node->data = data;
        node->next = NULL;
        node->prev = NULL;
    }else{
        printf("Error occurred when allocating memory.\n");
    }
    return node;
}

Node* push(Node **headRef, int data) {
    Node* node = newNode(data);
    if (node) {
        node->next = *headRef;
        if (*headRef) {
            (*headRef)->prev = node;
        }
        *headRef = node;
    }
    return node;
}

Node* append(Node **headRef, int data) {
    Node* node = newNode(data);
    if (node) {
        if (*headRef) {
            while ((*headRef)->next) {
                headRef = &((*headRef)->next);
            }
            (*headRef)->next = node;
            node->prev = (*headRef);
        }else {
            *headRef = node;
        }
    }
    return node;
}

void printDoublyLinkedList(Node *head) {
    printf("The content of the doubly linked list is [ ");
    Node *current_node = head;
    Node *tail_node = NULL;
    while (current_node) {
        printf("%d ", current_node->data);
        if (NULL == current_node->next) {
            tail_node = current_node;
        }
        current_node = current_node->next;
    }
    printf("]\n");

    printf("The reversed content of the doubly linked list is [ ");
    while(tail_node) {
        printf("%d ", tail_node->data);
        tail_node = tail_node->prev;
    }
    printf("]\n");
}

int split(Node *head, Node **front_ref, Node **back_ref) {
    *front_ref = NULL;
    *back_ref = NULL;
    Node *slow = head, *fast = head;
    if (head){
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        *front_ref = head;
        *back_ref = slow->next;
        slow->next = NULL;
        return 1;
    }else {
        return 0;
    }
}

Node* sortedMerge(Node *a, Node *b) {
    Node *result = NULL;

    if (NULL == a) {
        return b;
    }else if (NULL == b) {
        return a;
    }

    if (a->data <= b->data) {
        result = a;
        result->next = sortedMerge(a->next, b);
        if (result->next) {
            result->next->prev = a;
        }
        result->prev = NULL;
    }else {
        result = b;
        result->next = sortedMerge(a, b->next);
        if (result->next) {
            result->next->prev = b;
        }
        result->prev = NULL;
    }
    return result;
}
void mergeSort(Node **headRef) {
    Node *a;
    Node *b;

    if (NULL == *headRef || NULL == (*headRef)->next) {
        return;
    }

    if (split(*headRef, &a, &b)) {
        mergeSort(&a);
        mergeSort(&b);
        *headRef = sortedMerge(a, b);
    }
}

int main(){
    Node *doublyLinkedList = NULL;
    append(&doublyLinkedList, 5);
    append(&doublyLinkedList, 20);
    append(&doublyLinkedList, 4);
    append(&doublyLinkedList, 3);
    append(&doublyLinkedList, 30);
    append(&doublyLinkedList, 10);
    printf("Before sorting:\n");
    printDoublyLinkedList(doublyLinkedList);

    mergeSort(&doublyLinkedList);

    printf("After sorting:\n");
    printDoublyLinkedList(doublyLinkedList);


}

