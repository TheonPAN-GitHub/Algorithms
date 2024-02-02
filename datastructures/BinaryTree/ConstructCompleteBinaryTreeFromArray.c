//
// Created by Theon on 2024/1/25.
//
#include <stdio.h>
#include <stdlib.h>
/**
 * The pre-conditions of this approach are:
 * 1. The elements of the array are enough for building a complete binary tree;
 * 2. If the parent node is at index i in the array then the left child of that node is at index (2*i + 1) and the right child is at index (2*i + 2) in the array.
 */
typedef struct Node{
    int key;
    struct Node *left, *right;
} Node;

void createTreeNodes(Node **root, int A[], int index, int N) {
    if ((*root) == NULL) {
        return;
    }
    int leftChildIndex = 2 * index + 1;
    if (leftChildIndex < N) {
        Node *leftChildNode = (Node *) malloc(sizeof(Node));
        (*root)->left = leftChildNode;
        leftChildNode->key = A[leftChildIndex];
        leftChildNode->left = NULL;
        leftChildNode->right = NULL;
        createTreeNodes(&leftChildNode, A, leftChildIndex, N);
    }
    int rightChildIndex = 2 * index + 2;
    if (rightChildIndex < N) {
        Node *rightChildNode = (Node *) malloc(sizeof(Node));
        (*root)->right = rightChildNode;
        rightChildNode->key = A[rightChildIndex];
        rightChildNode->left = NULL;
        rightChildNode->right = NULL;
        createTreeNodes(&rightChildNode, A, rightChildIndex, N);
    }
    return;
}

Node* createCompleteBinaryTree(int A[], int N) {
    if (A == NULL) {
        return NULL;
    }

    Node* root = (Node *) malloc(sizeof(Node));
    root->key = A[0];
    root->left = NULL;
    root->right = NULL;
    createTreeNodes(&root, A, 0, N);
    return root;
}

void printTreeByInorder(Node *treeNode) {
    if (treeNode == NULL) {
        return;
    }

    printTreeByInorder(treeNode->left);
    printf("%d ", treeNode->key);
    printTreeByInorder(treeNode->right);
}
int main() {
    int A[] = {1, 2, 3, 4, 5, 6, 6, 6, 6, 6};
    int size = sizeof(A) / sizeof(A[0]);
    Node* treeRoot = createCompleteBinaryTree(A, size);
    printTreeByInorder(treeRoot);
    exit(0);
}
