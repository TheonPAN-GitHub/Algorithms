//
// Created by Theon on 2024/2/27.
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

void inorder(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}
TreeNode *minValuNode(TreeNode *node) {
    TreeNode *current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

TreeNode* deleteNode(TreeNode *root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
        return root;
    }

    if (key > root->key) {
        root->right = deleteNode(root->right, key);
        return root;
    }

    if (root->left == NULL) {
        TreeNode *tmp = root->right;
        free(root);
        return tmp;
    }

    if (root->right == NULL) {
        TreeNode *tmp = root->left;
        free(root);
        return tmp;
    }

    //The deleted node has left and right child.
//    TreeNode *successorParent = root;
//
//    //The successor should exist in right treee.
//    TreeNode *successor = root->right;
//    while (successor->left != NULL) {
//        successorParent = successor;
//        successor = successor->left;
//    }
//    if (successorParent != root) {
//        successorParent->left = successor->right;
//    }else {
//        successorParent->right = successor->right;
//    }
//
//    root->key = successor->key;
//    free(successor);
//    return root;
    TreeNode* successor = minValuNode(root->right);
    root->key = successor->key;
    root->right = deleteNode(root->right, successor->key);
    return root;
}

int countTreeNodes(TreeNode *root) {
    if (root == NULL) {
        return 0;
    }

    return countTreeNodes(root->left) + countTreeNodes(root->right) + 1;
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

    printf("Original BST: ");
    inorder(root);

    printf("\n\nDelete a leaf node: 20\n");
    root = deleteNode(root, 20);
    printf("Modified BST tree after deleting single child node:\n");
    inorder(root);

    printf("\n\nDelete node with both children:70\n");
    root = deleteNode(root, 70);
    printf("Modified BST tree after deleting both children:\n");
    inorder(root);
}
