//
// Created by Theon on 2024/3/12.
//
#include <stdio.h>
#include <stdlib.h>

/**
        First, we use Floyd Cycle-finding algorithm to check if there is a loop in the given linked list, then we should
    find the starting node of the loop in the linked list and uncycle it.

        To find the starting node of the loop, there are 3 approaches:
        1. Check the node one-by-one;
        2. Check the node by loop's length approach;
        3. Floyd Uncycle algorithm.
 */

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* push(Node **head, int data) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;

    newNode->next = *head;
    *head = newNode;

    return newNode;
}

Node* append(Node **head, int data) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;

    if (*head) {
        Node* currentNode = *head;
        while (currentNode->next) {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }else{
        *head = newNode;
    }
    return newNode;
}

void printLinkedList(Node *head) {
    printf("The content of linked list is [");
    Node* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("]\n");
}


void removeLoopCheckOneByOne(Node *head) {
    if (head == NULL) {
        return;
    }

    //First, check if there is a loop in the given linked list
    Node *slow_ptr = head;
    Node *fast_ptr = head;
    while (fast_ptr && slow_ptr && fast_ptr->next) {
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next->next;
        if (slow_ptr == fast_ptr) {
            break;
        }
    }

    //There's a loop, check the starting node of loop one-by-one, and uncycle it
    if (slow_ptr && fast_ptr && slow_ptr == fast_ptr) {
        slow_ptr = head;
        while (slow_ptr) {
            Node *current = fast_ptr;
            do {
                if (current->next != slow_ptr) {
                    current = current->next;
                }else {
                    current->next = NULL;
                    return;
                }
            }while (current != fast_ptr);

            slow_ptr = slow_ptr->next;
        }
    }
}

/**
        In this approach, first counting the nodes number of the loop(the length of loop), let's say it as 'k', then
    we reset a pointer to the head of linked list, the other we set it point to the 'k'th node from the head.
        Moving the two pointer one unit at one time, until they meet again, then uncycle it.
 */
void removeLoopCheckByLoopLength(Node *head) {
    if (head == NULL) {
        return;
    }

    Node *slow_ptr = head;
    Node *fast_ptr = head;
    while (slow_ptr && fast_ptr && fast_ptr->next) {
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next->next;

        if (slow_ptr == fast_ptr) {
            break;
        }
    }

    //Detect the loop, uncycle it
    if (slow_ptr && fast_ptr && slow_ptr == fast_ptr) {
        //Count how many nodes in the loop
        int k = 1;
        while (fast_ptr->next != slow_ptr) {
            fast_ptr = fast_ptr->next;
            k++;
        }

        //Move the slow pointer to head, and the fast pointer to previous node of 'k'th node from head
        slow_ptr = head;
        fast_ptr = head;
        for (int i = 0; i < (k - 1); i++) {
            fast_ptr = fast_ptr->next;
        }

        //Move the slow and fast pointer one node per time, until they meet again
        while (slow_ptr != fast_ptr->next) {
            slow_ptr = slow_ptr->next;
            fast_ptr = fast_ptr->next;
        }

        //uncycle it
        fast_ptr->next = NULL;
    }
}

/**
 We can conclude below from the above diagram

        Distance traveled by fast pointer = 2 * (Distance traveled
                                                 by slow pointer)

        (m + n*x + k) = 2*(m + n*y + k)

        Note that before meeting the point shown above, fast
        was moving at twice speed.

        x -->  Number of complete cyclic rounds made by
               fast pointer before they meet first time

        y -->  Number of complete cyclic rounds made by
               slow pointer before they meet first time

        From the above equation, we can conclude below

            m + k = (x-2y)*n

        Which means m+k is a multiple of n.
        Thus we can write, m + k = i*n or m = i*n - k.
        Hence, distance moved by slow pointer: m, is equal to distance moved by fast pointer:
        i*n - k or (i-1)*n + n - k (cover the loop completely i-1 times and start from n-k).

        So if we start moving both pointers again at same speed such that one pointer (say slow) begins from
        head node of linked list and other pointer (say fast) begins from meeting point. When the slow
        pointer reaches the beginning of the loop (has made m steps), the fast pointer would have made also
        moved m steps as they are now moving at the same pace. Since m+k is a multiple of n and fast starts
        from k, they would meet at the beginning. Can they meet before also? No because slow pointer enters
        the cycle first time after m steps.
 */
void removeLoopByFloydAlg(Node *head) {
    if (head == NULL) {
        return;
    }

    //Detect if there's a loop
    Node *slow_ptr = head;
    Node *loop_tail_ptr = head;
    Node *fast_ptr = head;
    while (slow_ptr && fast_ptr && fast_ptr->next) {
        slow_ptr = slow_ptr->next;
        loop_tail_ptr = fast_ptr->next;
        fast_ptr = loop_tail_ptr->next;

        if (slow_ptr == fast_ptr) {
            break;
        }
    }

    //There's a loop
    if (slow_ptr && fast_ptr && slow_ptr == fast_ptr) {
        //Reset slow pointer to the head, and move slow and fast pointer one node per time, until they meet again.
        slow_ptr = head;
        if (slow_ptr == fast_ptr) {
            loop_tail_ptr->next = NULL;
            return;
        }else {
            while (slow_ptr->next != fast_ptr->next) {
                slow_ptr = slow_ptr->next;
                fast_ptr = fast_ptr->next;
            }
            fast_ptr->next = NULL;
            return;
        }

    }
}

int main(){
    int arr[] = {20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = sizeof(arr) / sizeof(arr[0]);
    Node *linkedList = NULL;
    for (int i = 0; i < n; i++) {
        append(&linkedList, arr[i]);
    }
    if (linkedList == NULL) {
        return 0;
    }

    printf("The linked list before being cycled:\n");
    printLinkedList(linkedList);

    Node *current = linkedList;
    while (current->next) {
        current = current->next;
    }
    current->next = linkedList->next;

    removeLoopByFloydAlg(linkedList);
    printLinkedList(linkedList);
}
