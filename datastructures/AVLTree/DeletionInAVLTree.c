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

TreeNode* newNode(int key) {
    TreeNode *newNode = (TreeNode *) malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;

    return newNode;
}

int max(int a, int b) {
    return (a > b)? a : b;
}

int height(TreeNode *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

TreeNode* rightRotate(TreeNode *y) {
    if (y == NULL) {
        return NULL;
    }

    TreeNode *x = y->left;
    TreeNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

TreeNode* leftRotate(TreeNode *x) {
    if (x == NULL) {
        return NULL;
    }

    TreeNode *y = x->right;
    TreeNode *T2 = y->left;

    y->left = x;
    x->right = T2;

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

TreeNode* minValueNode(TreeNode* node) {
    TreeNode *current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
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

    //If the node is unbalanced, there are 4 cases
    //1. Left-left case
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    //2. Left-right case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
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

TreeNode* deleteNode(TreeNode *node, int key) {
    if (node == NULL) {
        return NULL;
    }

    if (key < node->key) {
        node->left = deleteNode(node->left, key);
    }else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    }else {
        if (node->left == NULL || node->right == NULL) {
            TreeNode *tmp = node->left ? node->left : node->right;

            if (tmp == NULL) {
                tmp = node;
                node == NULL;
            } else {
                *node = *tmp;
            }
            free(tmp);
        } else {
            TreeNode *minNode = minValueNode(node->right);
            node->key = minNode->key;
            node->right = deleteNode(node->right, minNode->key);
        }
    }

    if (node == NULL) {
        return node;
    }

    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = getBalance(node);

    //1. Left-left case
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }

    //2. Left-right case
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    //3. Right-left case
    if (balance < -1 && getBalance(node->right) >= 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    //4. Right-right case
    if (balance < -1 && getBalance(node->right) < 0) {
        return leftRotate(node);
    }

    return node;
}

void preOrder(TreeNode *root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->key);
    preOrder(root->left);
    preOrder(root->right);
}

/* Driver program to test above function*/
int main()
{
    TreeNode *root = NULL;

    /* Constructing tree given in the above figure */
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);

    /* The constructed AVL Tree would be
            9
           /  \
          1    10
        /  \     \
       0    5     11
      /    /  \
     -1   2    6
    */

    printf("Preorder traversal of the constructed AVL "
           "tree is \n");
    preOrder(root);

    root = deleteNode(root, 10);

    /* The AVL Tree after deletion of 10
            1
           /  \
          0    9
        /     /  \
       -1    5     11
           /  \
          2    6
    */

    printf("\nPreorder traversal after deletion of 10 \n");
    preOrder(root);

    return 0;
}