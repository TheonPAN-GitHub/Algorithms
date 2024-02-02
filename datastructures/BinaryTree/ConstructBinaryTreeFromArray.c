//
// Created by Theon on 2024/1/24.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
}Node;

Node* createRoot(int key) {
    Node* root = (Node*) malloc(sizeof(Node));
    if (root != NULL) {
        root->key = key;
        root->left = NULL;
        root->right = NULL;
    }
    return root;
}

void createChildNode(Node* parent, int A[], int N) {
    if (parent != NULL && A != NULL && N > 0) {
        for (int i = 0; i < N; i++) {
            if (A[i] == parent->key) {
                if (parent->left == NULL) {
                    Node* leftChild = (Node*) malloc(sizeof(Node));
                    leftChild->key = i;
                    leftChild->left = NULL;
                    leftChild->right = NULL;
                    parent->left = leftChild;
                    createChildNode(leftChild, A, N);
                }else if (parent->right == NULL) {
                    Node* rightChild = (Node*) malloc(sizeof(Node));
                    rightChild->key = i;
                    rightChild->left = NULL;
                    rightChild->right = NULL;
                    parent->right = rightChild;
                    createChildNode(rightChild, A, N);
                }
            }
        }
    }
}

/**
    The brute-force solution.
 */
Node* solution1(int A[], int N){
    Node* tree = NULL;
    for (int i = 0; i < N; i++) {
        if (A[i] == -1) {
            tree = createRoot(i);
            createChildNode(tree, A, N);
        }
    }
    return tree;
}

Node* newNode(int key) {
    Node* new_node = (Node *) malloc(sizeof(Node));
    new_node->key = key;
    new_node->left = new_node->right = NULL;
    return new_node;
}
void createNode(int A[], int i, Node *created[], Node** root) {
    if (created[i] != NULL) {
        return;
    }
    created[i] = newNode(i);

    //Deal with root node
    if (A[i] == -1) {
        *root = created[i];
        return;
    }

    if (created[A[i]] == NULL) {
        createNode(A, A[i], created, root);
    }
    Node* parentNode = created[A[i]];
    if (parentNode->left == NULL) {
        parentNode->left = created[i];
    }else if (parentNode->right == NULL){
        parentNode->right = created[i];
    }
}

/**
    Efficient solution.
 */
Node* solution2(int A[], int N) {
    Node *created[N];
    for (int i = 0; i < N; i++) {
        created[i]  = NULL;
    }

    Node *root = NULL;
    for (int i = 0; i < N; i++) {
        createNode(A, i,created, &root);
    }

    return root;
}

/**
    More efficient solution.
 */
Node* solution3(int A[], int N) {
    Node* created[N];
    Node* root = NULL;
    for (int i = 0; i < N; i++) {
        created[i] = newNode(i);
    }

    for (int i = 0; i < N; i++) {
        if (A[i] == -1) {
            root = created[i];
        }else {
            Node *parentNode = created[A[i]];
            if (parentNode->left == NULL) {
                parentNode->left = created[i];
            }else if (parentNode->right == NULL) {
                parentNode->right = created[i];
            }
        }
    }

    return root;
}

void printTreeInorder(Node* tree) {
    if (tree == NULL) {
        return;
    }
    printTreeInorder(tree->left);
    printf("%d ", tree->key);
    printTreeInorder(tree->right);
}

int main() {
//    int A[] = {1, 5, 5, 2, 2, -1, 3};
    int A[] = {-1, 0, 0, 1, 1, 3, 5};
    int size = sizeof(A) / sizeof(A[0]);
    Node* tree1 = solution1(A, size);
    Node* tree2 = solution2(A, size);
    Node* tree3 = solution3(A, size);
    printTreeInorder(tree1);
    printf("\n");
    printTreeInorder(tree2);
    printf("\n");
    printTreeInorder(tree3);
}
