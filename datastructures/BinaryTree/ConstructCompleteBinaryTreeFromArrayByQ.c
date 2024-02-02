//
// Created by Theon on 2024/2/2.
//
#include <stdio.h>
#include <stdlib.h>
/**
   Create a TreeNode struct to represent a node in the binary tree.
   Define a function buildTree that takes the nums array as a parameter.
   If the nums array is empty, return NULL.
   Create the root node with the value at index 0 and push it into a queue.
   Initialize an integer i to 1.
   Loop while the queue is not empty:
       Pop the front node from the queue and assign it to curr.
       If i is less than the size of the nums array, create a new node with the value at index i and set it as the left child of curr. Increment i by 1. Push the left child node into the queue.
       If i is less than the size of the nums array, create a new node with the value at index i and set it as the right child of curr. Increment i by 1. Push the right child node into the queue.
   Return the root node.
   Define a printTree function to print the values of the tree in preorder traversal order.
   Call the buildTree function with the given nums array to construct the complete binary tree.
   Call the printTree function to print the values of the tree.

   Time complexity: The buildTree function has to visit every element in the nums array once, so the time complexity is O(n), where n is the size of the nums array.
 */
typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

typedef struct Node {
    TreeNode *data;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *queueBody;
    Node *front;
    Node *rear;
} Queue;

void initializeQueue(Queue *queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->queueBody = NULL;
}
int isQueueEmpty(Queue *queue) {
   return queue->front == NULL;
}

void enQueue(Queue *queue, TreeNode *data) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    if (isQueueEmpty(queue)) {
        queue->queueBody = new_node;
        queue->front = new_node;
        queue->rear = new_node;
    }else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

TreeNode* deQueue(Queue *queue) {
    TreeNode *item = NULL;
    if (isQueueEmpty(queue)) {
        return item;
    }

    Node* current_node = queue->front;
    if (current_node->next == NULL) {
        initializeQueue(queue);
    }else {
        queue->queueBody = queue->front->next;
        queue->front = queue->front->next;
    }
    current_node->next = NULL;
    item = current_node->data;
    free(current_node);

    return item;
}

void emptyQueue(Queue *queue) {
    while (deQueue(queue)) {

    }
}

TreeNode* buildTree(int B[], int N) {
    if (B == NULL || N < 0) {
        return NULL;
    }

    TreeNode *root = (TreeNode *) malloc(sizeof(TreeNode));
    root->data = B[0];
    Queue queue;
    initializeQueue(&queue);
    enQueue(&queue,root);
    int i = 1;
    while (i < N) {
        TreeNode *cur = deQueue(&queue);

        TreeNode *leftChild = (TreeNode *) malloc(sizeof(TreeNode));
        leftChild->data = B[i++];
        leftChild->left = NULL;
        leftChild->right = NULL;
        cur->left = leftChild;
        enQueue(&queue, leftChild);

        if (i < N) {
            TreeNode *rightChild = (TreeNode *) malloc(sizeof(TreeNode));
            rightChild->left = NULL;
            rightChild->data = B[i++];
            rightChild->right = NULL;
            cur->right = rightChild;
            enQueue(&queue, rightChild);
        }
    }
    emptyQueue(&queue);
    return root;
}

void printInorder(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    printInorder(root->left);
    printf("%d ", root->data);
    printInorder(root->right);
}

int main() {
    int B[] = {1, 2, 3, 4, 5,6, 6, 6, 6, 6};
    int sizeB = sizeof(B) / sizeof(B[0]);

    TreeNode *root = buildTree(B, sizeB);
    printInorder(root);
    exit(0);
}
