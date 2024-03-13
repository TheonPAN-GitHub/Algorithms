//
// Created by Theon on 2024/3/13.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_STACK_SIZE 100000

typedef struct Stack {
    char *contents;
    int top;
    int maxSize;
} Stack;

Stack* inintiateStack(int maxSize) {
    if (maxSize <= 0) {
        return NULL;
    }
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (stack == NULL) {
        return NULL;
    }
    char *stackContents = (char *) malloc(sizeof(char) * maxSize);
    if (stackContents == NULL) {
        return NULL;
    }
    stack->contents = stackContents;
    stack->top = -1;
    stack->maxSize = maxSize;
    return stack;
}

void freeStack(Stack *stack) {
    if (stack) {
        if (stack->contents) {
            free(stack->contents);
        }
        free(stack);
    }
}

bool isStackEmpty(Stack *stack) {
    if (stack == NULL) {
        return true;
    }

    return (stack->top < 0);
}

bool push(Stack *stack, char data) {
    if (stack == NULL || stack->top >= stack->maxSize) {
        return false;
    }

    stack->contents[++stack->top] = data;
    return true;
}

char pop(Stack *stack) {
    if (stack == NULL || isStackEmpty(stack)){
        return '\0';
    }
    return stack->contents[stack->top--];
}

typedef struct Node {
    char data;
    struct Node *next;
} Node;

Node* pushLinkedList(Node **head, char data) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = (*head);
    *head = newNode;

    return newNode;
}

Node* append(Node **head, char data) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return newNode;
    }

    Node *currNode = *head;
    while (currNode->next) {
        currNode = currNode->next;
    }
    currNode->next = newNode;

    return newNode;
}

bool checkPalindromeByStack(Node *head) {
    if (head == NULL) {
        return true;
    }
    Stack *stack = inintiateStack(MAX_STACK_SIZE);
    Node *currNode = head;
    while (currNode) {
        if (!push(stack, currNode->data)) {
            return false;
        }
        currNode = currNode->next;
    }

    currNode = head;
    while (currNode) {
        char c = pop(stack);
        if (c == '\0') {
            return false;
        }
        if (c != currNode->data) {
            return false;
        }
        currNode = currNode->next;
    }

    free(stack);

    return true;
}

void reverseLinkedList(Node ** head) {
    Node *current = *head;
    Node *prev = NULL;
    Node *next = NULL;
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        if (next == NULL) {
            *head = current;
        }
        current = next;
    }
}

bool compareLinkedList(Node *l1, Node *l2) {
    while (l1 && l2) {
        if (l1->data != l2->data) {
            return false;
        }
        l1 = l1->next;
        l2 = l2->next;
    }

    if (l1 == NULL && l2 == NULL) {
        return true;
    }else {
        return false;
    }
}

bool checkPalindromeByReverse(Node *head) {
    if (head == NULL) {
        return true;
    }
    Node *slow_ptr = head, *fast_ptr = head;
    Node *prev_slow_ptr = NULL, *mid_node = NULL;
    Node *second_ptr = NULL;

    /*
        Find the mid node of the linked list by using slow-fast pointers,
        it depends on whether the number of nodes is odd or even.

    */
    while (fast_ptr && fast_ptr->next) {
        prev_slow_ptr = slow_ptr;
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next->next;
    }

    //There are odd number of nodes
    if (fast_ptr != NULL) {
        mid_node = slow_ptr;
        slow_ptr = slow_ptr->next;
    }

    prev_slow_ptr->next = NULL;
    second_ptr = slow_ptr;

    reverseLinkedList(&second_ptr);

    bool res = compareLinkedList(head, second_ptr);

    reverseLinkedList(&second_ptr);
    if (mid_node != NULL) {
        prev_slow_ptr->next = mid_node;
        mid_node->next = second_ptr;
    }else {
        prev_slow_ptr->next = second_ptr;
    }
    return res;
}

/**
    Reversely visit the singly linked list by using recursion.
 */
bool checkPalindromeByRecursionUtil(Node **left, Node *right) {
    if (right == NULL) {
        return true;
    }
    bool res = checkPalindromeByRecursionUtil(left, right->next);
    if (res == false) {
        return false;
    }
    bool isEqual = ((*left)->data == right->data);
    *left = (*left)->next;

    return isEqual;
}

bool checkPalindromeByRecursion(Node *head) {
    return checkPalindromeByRecursionUtil(&head, head);
}

void printLinkedList(Node *head) {
    printf("The content of linkedlist is [ ");
    Node *currentNode = head;
    while (currentNode) {
        printf("%c ", currentNode->data);
        currentNode = currentNode->next;
    }
    printf("]\n");
}


int main() {
    char *arr = "level";
    Node *linkedList = NULL;
    int i = 0;
    while (arr[i] != '\0') {
        append(&linkedList, arr[i++]);
    }
    if (checkPalindromeByStack(linkedList)) {
        printf("It's palindrome.\n");
    }else {
        printf("It's not palindrome.\n");
    }

    if (checkPalindromeByReverse(linkedList)) {
        printf("It's palindrome.\n");
    }else {
        printf("It's not palindrome.\n");
    }
    printLinkedList(linkedList);
    if (checkPalindromeByRecursion(linkedList)) {
        printf("It's palindrome.\n");
    }else{
        printf("It's not palindrome.\n");
    }

    return 0;
}


