//
// Created by Theon on 2024/2/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int key;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* newNode(int key){
    TreeNode *newTreeNode = (TreeNode *) malloc(sizeof(TreeNode));
    newTreeNode->key = key;
    newTreeNode->right = NULL;
    newTreeNode->left = NULL;
}

TreeNode* insert(TreeNode *root, int key) {
    if (root == NULL) {
        return newNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
        return root;
    }

    if (key > root->key) {
        root->right = insert(root->right, key);
        return root;
    }

    return root;
}

void inorder(TreeNode *node) {
    if (node == NULL) {
        return;
    }
    inorder(node->left);
    printf("%d ", node->key);
    inorder(node->right);
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
    inorder(root);

    return 0;
}
