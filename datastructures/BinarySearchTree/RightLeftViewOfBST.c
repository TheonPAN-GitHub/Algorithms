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
    TreeNode* newNode = (TreeNode *) malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->key = key;
    newNode->left = newNode->right = NULL;
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

void printRightViewUtil(TreeNode *root, int level, int *maxLevel) {
    if (root == NULL) {
        return;
    }

    if (level > *maxLevel) {
        *maxLevel = level;
        printf("%d ", root->key);
    }

    printRightViewUtil(root->right, level + 1, maxLevel);
    printRightViewUtil(root->left, level + 1, maxLevel);
}

void printRightView(TreeNode *root) {
    int maxLevel = 0;
    printRightViewUtil(root, 1, &maxLevel);
    printf("\n");
}

void printLeftViewUtil(TreeNode *root, int level, int *maxLevel) {
    if (root == NULL) {
        return;
    }

    if (level > *maxLevel) {
        *maxLevel = level;
        printf("%d ", root->key);
    }

    printLeftViewUtil(root->left, level + 1, maxLevel);
    printLeftViewUtil(root->right, level + 1, maxLevel);
}

void printLeftView(TreeNode *root) {
    int maxLevel = 0;
    printLeftViewUtil(root, 1, &maxLevel);
    printf("\n");
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

    printRightView(root);
    printLeftView(root);

    TreeNode *root1 = newNode(1);
    root1->left = newNode(2);
    root1->right = newNode(3);
    root1->left->left = newNode(4);
    root1->left->right = newNode(5);
    root1->right->left = newNode(6);
    root1->right->right = newNode(7);
    root1->right->left->right = newNode(8);
    printRightView(root1);
    printLeftView(root1);

    return 0;
}