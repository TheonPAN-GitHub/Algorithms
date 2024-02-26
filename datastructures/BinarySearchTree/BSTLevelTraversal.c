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
    TreeNode *newTreeNode = (TreeNode *) malloc(sizeof(TreeNode));
    if (newTreeNode == NULL) {
        return NULL;
    }
    newTreeNode->key = key;
    newTreeNode->left = NULL;
    newTreeNode->right = NULL;
    return newTreeNode;
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

int height(TreeNode *node) {
    if (node == NULL) {
        return 0;
    }

    int lheight = height(node->left);
    int rheight = height(node->right);

    if (lheight > rheight) {
        return (lheight + 1);
    }else {
        return (rheight + 1);
    }
}

void printGivenLevel(TreeNode *node, int level) {
    if (node == NULL) {
        return;
    }
    if (level == 1) {
        printf("%d ", node->key);
        return;
    }
    if (level > 1) {
        printGivenLevel(node->left, level - 1);
        printGivenLevel(node->right, level - 1);
    }
}

void printLevelOrder(TreeNode *root) {
    int treeHeight = height(root);
    for (int i = 1; i <= treeHeight; i++) {
        printGivenLevel(root, i);
        printf("\n");
    }
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

    printLevelOrder(root);
}
