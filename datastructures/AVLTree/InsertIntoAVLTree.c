//
// Created by Theon on 2024/2/28.
//
#include <stdlib.h>
#include <stdio.h>

typedef struct TreeNode {
    int key;
    struct TreeNode *left, *right;
    int height;
} TreeNode;

int height(TreeNode *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int max(int a, int b) {
    return ((a > b)? a : b);
}

TreeNode* newNode(int key) {
    TreeNode *newNode = (TreeNode *) malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        return NULL;
    }

    newNode->key = key;
    newNode->height = 1; //New node is initially added at leaf
    newNode->left = newNode->right = NULL;

    return newNode;
}

TreeNode* rightRotate(TreeNode *y) {
    TreeNode *x = y->left;
    TreeNode *T2 = x->right;

    y->left = T2;
    x->right = y;

    //Update height
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

TreeNode* leftRotate(TreeNode *x) {
    TreeNode *y = x->right;
    TreeNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    //Update height
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(TreeNode *node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

TreeNode* insert(TreeNode *node, int key) {
    if (node == NULL) {
        return newNode(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    }else if (key > node->key) {
        node->right = insert(node->right, key);
    }else {
        return node;
    }

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalance(node);
    //If this node becomes unbalanced, then there are 4 cases

    //1. Left-left case
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    //2. Left-right case
    if (balance > 1 && key > node->left->key) {
        node->left  = leftRotate(node->left);
        return rightRotate(node);
    }

    //3. Right-left case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    //4. Right-right case
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    return node;
}

void preOrder(TreeNode *node) {
    if (node == NULL) {
        return;
    }

    printf("%d ", node->key);
    preOrder(node->left);
    preOrder(node->right);
}

int main() {
    TreeNode *root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Preorder traversal of the constructed AVL tree is \n");
    preOrder(root);
    return 0;
}
