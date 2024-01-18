//
// Created by Theon on 2024/1/18.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;

void push(Node* head_ref, int new_data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->next = head_ref;
    new_node->data = new_data;

    head_ref = new_node;
}

void append(Node** head_ref, int new_data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->next = NULL;
    new_node->data = new_data;

    if (*head_ref == NULL){
        *head_ref = new_node;
        return;
    }
    Node* cur_node_ref = *head_ref;
    while (cur_node_ref->next != NULL) {
        cur_node_ref = cur_node_ref->next;
    }
    cur_node_ref->next = new_node;
    return;
}

void printLinkedlist(Node* head_ref) {
    printf("The contents of linked list is [");
    Node* cur_node_ref = head_ref;
    while(cur_node_ref != NULL) {
        printf("%d ", cur_node_ref->data);
        cur_node_ref = cur_node_ref->next;
    }
    printf("]\n");
}

/**
 * The basic and straightforward one, detecting the loop by using Floyd's algo, then checking the node
 * from head one by one, to find the first node which can be reached from the common point, it's the start node
 * of the loop.
 *
 * @param head
 */
void solution1(Node* head_ref) {
    if (head_ref == NULL) {
        printf("The linked list is empty.\n");
    }
    Node* slow_p = head_ref;
    Node* fast_p = head_ref;

    while (slow_p && fast_p && fast_p->next) {
        slow_p = slow_p->next;
        fast_p = fast_p->next->next;
        if (slow_p == fast_p) {
            break;
        }
    }

    //Loop exists.
    if (slow_p == fast_p) {
        //Check node from head one by one, to find the first node which can be reached from fast_p
        slow_p = head_ref;
        while (slow_p) {
            Node* cur_node_p = fast_p;
            do {
                if (slow_p == cur_node_p->next) {
                    cur_node_p->next = NULL;
                    return;
                }else {
                    cur_node_p = cur_node_p->next;
                }
            }while(cur_node_p != fast_p);
            slow_p = slow_p->next;
        }
    }
}

/**
  The better one:
    1 This method is also dependent on Floyd’s Cycle detection algorithm.
    2 Detect Loop using Floyd’s Cycle detection algorithm and get the pointer to a loop node.
    3 Count the number of nodes in the loop. Let the count be k.
    4 Fix one pointer to the head and another to a kth node from the head.
    5 Move both pointers at the same pace, they will meet at the loop starting node.
    6 Get a pointer to the last node of the loop and make the next of it NULL.

 */
void solution2RemoveLoop(Node* loop_node, Node* head_ref) {
    Node* ptr1 = loop_node;
    Node* ptr2 = loop_node;

    //Count the number of nodes int the loop.
    int k = 1;
    while(ptr1->next != ptr2) {
        k++;
        ptr1 = ptr1->next;
    }
    ptr1 = head_ref;
    ptr2 = head_ref;

    //Move ptr2 to the k nodes after head.
    for (int i = 0; i < k; i++) {
        ptr2 = ptr2->next;
    }

    //Move ptr1 and ptr2 at the same pace, they will meet at loop start node.
    while (ptr1 != ptr2) {
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    //Move to the last node
    while (ptr2->next != ptr1) {
        ptr2 = ptr2->next;
    }
    ptr2->next = NULL;
    return;
}
void solution2(Node* head_ref) {
    //Using Floyd's algo to find the "common point" of the loop.
    Node* slow_p = head_ref;
    Node* fast_p = head_ref;
    while (slow_p && fast_p && fast_p->next) {
        slow_p = slow_p->next;
        fast_p = fast_p->next->next;
        if (slow_p == fast_p) {
            solution2RemoveLoop(slow_p, head_ref);
            return;
        }
    }
    return;
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
void solution3(Node* head_ref) {
    Node* slow_p = head_ref;
    Node* fast_p = head_ref;
    while (slow_p && fast_p && fast_p->next) {
        slow_p = slow_p->next;
        fast_p = fast_p->next->next;
        if (slow_p == fast_p) {
            slow_p = head_ref;

            if (slow_p == fast_p) {
                while (fast_p->next != slow_p) {
                    fast_p = fast_p->next;
                }
            }else{
                while (fast_p->next != slow_p->next) {
                    fast_p = fast_p->next;
                    slow_p = slow_p->next;
                }
            }
            fast_p->next = NULL;
        }
    }
}
int main() {
    int A[] = {50, 20, 15, 4, 10};
    int size = sizeof(A) / sizeof(A[0]);
    Node* list = NULL;
    for (int i = 0; i < size; i++) {
        append(&list, A[i]);
    }
    printLinkedlist(list);
    list->next->next->next->next->next = list->next->next;
    solution3(list);
    printLinkedlist(list);
}
