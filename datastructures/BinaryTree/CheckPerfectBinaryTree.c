//
// Created by Theon on 2024/2/23.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
}TreeNode;

typedef struct QueueNode {
    TreeNode *treeNode;
    struct QueueNode *next;
}QueueNode;

typedef struct Queue {
    QueueNode *queueBody;
    QueueNode *front;
    QueueNode *rear;
    int size;
}Queue;

void initialQueue(Queue *queue) {
    queue->queueBody = NULL;
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

int isQueueEmpty(Queue queue) {
    return (queue.front == NULL);
}

void enQueue(Queue *queue, TreeNode *treeNode) {
    QueueNode * newQueueNode = (QueueNode *) malloc(sizeof(QueueNode));
    if (newQueueNode == NULL) {
        return;
    }
    newQueueNode->treeNode = treeNode;
    newQueueNode->next = NULL;
    if (isQueueEmpty(*queue)) {
        queue->front = newQueueNode;
        queue->queueBody = queue->front;
        queue->rear = queue->queueBody;
    }else {
        queue->rear->next = newQueueNode;
        queue->rear = newQueueNode;
    }
    queue->size ++;
}

TreeNode* deQueue(Queue *queue) {
    if (isQueueEmpty(*queue)) {
        return NULL;
    }
    TreeNode *treeNode = queue->front->treeNode;
    QueueNode *tmp = queue->front;
    queue->front = queue->front->next;
    queue->queueBody = queue->front;
    if (queue->queueBody == NULL) {
        queue->rear = NULL;
    }
    free(tmp);
    queue->size--;
    return treeNode;
}

int queueSize(Queue queue) {
    return queue.size;
}

int isPerfectByUsingRecursion(TreeNode *root) {
    if (root == NULL) {
        return 1;
    }
    if ((root->left == NULL) != (root->right == NULL)) {
        return 0;
    }
    if (root->left == NULL) {
        return 1;
    }
    //Make sure either left child or right child is not a leaf.
    if ((root->left->left == NULL) != (root->right->left == NULL)) {
        return 0;
    }
    if ((!isPerfectByUsingRecursion(root->left) || !isPerfectByUsingRecursion(root->right))) {
        return 0;
    }

    return 1;
}

TreeNode* newNode(int data) {
    TreeNode *newNode = (TreeNode *) malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int numberOfTreeNodes(TreeNode *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + numberOfTreeNodes(root->left) + numberOfTreeNodes(root->right);
}

int isPerfectByNumberOfNodes(TreeNode *root) {
    int numberOfNodes = numberOfTreeNodes(root);
//    printf("Number of treeNodes is %d.\n", numberOfNodes);
//    printf("%d.\n", (numberOfNodes & (numberOfNodes + 1)) == 0);
    //If the number of tree nodes plus 1 is power of 2, then it's a perfect binary tree.
    return ((numberOfNodes & (numberOfNodes + 1)) == 0);
}

/**
 Check the node number level by level.
 */
int isPerfectByQ(TreeNode *root) {
    if (root == NULL) {
        return 1;
    }
    Queue queue;
    initialQueue(&queue);
    enQueue(&queue, root);
    int level = 1;
    while (!isQueueEmpty(queue)) {
        int levelElementsCount = 0;
        int queueSize = queue.size;
        for (int i = 0; i < queueSize; i++) {
            TreeNode *treeNode = deQueue(&queue);
            levelElementsCount++;

            if (treeNode->left) {
                enQueue(&queue, treeNode->left);
            }

            if (treeNode->right) {
                enQueue(&queue, treeNode->right);
            }
        }

        if (levelElementsCount != level) {
            return 0;
        }
        level = level * 2;
    }
    return 1;
}

int main() {
    TreeNode *root = newNode(10);
    root->left = newNode(20);
    root->right = newNode(30);
    root->left->left = newNode(40);
    root->left->right = newNode(50);
    root->right->left = newNode(60);
    root->right->right = newNode(70);

    if (isPerfectByUsingRecursion(root)) {
        printf("Prefect Binary Tree.\n");
    }else {
        printf("NOT perfect binary tree.\n");
    }

    if (isPerfectByNumberOfNodes(root)) {
        printf("Prefect Binary Tree.\n");
    }else {
        printf("NOT perfect binary tree.\n");
    }

    if (isPerfectByQ(root)) {
        printf("Prefect Binary Tree.\n");
    }else {
        printf("NOT perfect binary tree.\n");
    }
    return 0;
}