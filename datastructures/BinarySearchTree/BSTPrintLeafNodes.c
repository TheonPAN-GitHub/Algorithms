//
// Created by Theon on 2024/2/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int key;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* newNode(int key) {
    TreeNode *newNode = (TreeNode *) malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        return NULL;
    }

    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

TreeNode* insert(TreeNode *node, int key) {
    if (node == NULL) {
        return newNode(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
        return node;
    }
    if (key > node->key) {
        node->right = insert(node->right, key);
        return node;
    }
    return node;
}

void printLeafNodes(TreeNode *node) {
    if (node == NULL) {
        return;
    }
    if (node->left == NULL && node->right == NULL) {
        printf("%d ", node->key);
        return;
    }

    if (node->left) {
        printLeafNodes(node->left);
    }

    if (node->right) {
        printLeafNodes(node->right);
    }
}

void printNonLeafNodes(TreeNode *node) {
    if (node == NULL || (node->left == NULL && node->right == NULL)) {
        return;
    }
    if (node->left || node->right) {
        printf("%d ", node->key);
    }
    printNonLeafNodes(node->left);
    printNonLeafNodes(node->right);
}

int main() {
    TreeNode *root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printLeafNodes(root);
    printf("\n");
    printNonLeafNodes(root);

    return 0;
}
