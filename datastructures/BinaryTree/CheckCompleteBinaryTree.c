//
// Created by Theon on 2024/2/22.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

typedef struct QueueNode {
    TreeNode *treeNode;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *queueBody;
    QueueNode *front;
    QueueNode *rear;
} Queue;

void initialQueue(Queue *queue) {
    queue->queueBody = NULL;
    queue->front = NULL;
    queue->rear = NULL;
}

int isQueueEmpty(Queue queue) {
   return (queue.front == NULL);
}

void enQueue(Queue *queue, TreeNode *treeNode) {
    if (queue == NULL) {
        return;
    }
    QueueNode *newQueueNode = (QueueNode *) malloc(sizeof(QueueNode));
    newQueueNode->treeNode = treeNode;
    newQueueNode->next = NULL;

    if (isQueueEmpty(*queue)) {
        queue->front = newQueueNode;
        queue->rear = newQueueNode;
        queue->queueBody = newQueueNode;
    }else {
        queue->rear->next = newQueueNode;
        queue->rear = newQueueNode;
    }
    return;
}

TreeNode* deQueue(Queue *queue) {
    if (queue == NULL) {
        return NULL;
    }
    if (isQueueEmpty(*queue)) {
        return NULL;
    }else {
        QueueNode *current = queue->front;
        queue->front = queue->front->next;
        queue->queueBody = queue->front;
        if (queue->queueBody == NULL) {
            queue->rear = NULL;
        }
        TreeNode* treeNode = current->treeNode;
        free(current);
        return treeNode;
    }
}

TreeNode* newTreeNode(int data) {
    TreeNode* newTreeNode = (TreeNode*) malloc(sizeof(TreeNode));
    newTreeNode->data = data;
    newTreeNode->left = NULL;
    newTreeNode->right = NULL;
    return newTreeNode;
}
/**
 Solution 1:
 To understand the approach, let us first define the term ‘Full Node’. A node is ‘Full Node’ if both left and right children are not empty (or not NULL).

The approach is to do a level order traversal starting from the root. In the traversal, once a node is found which is NOT a Full Node, all the following nodes must be leaf nodes.

Also, one more thing needs to be checked to handle the below case: If a node has an empty left child, then the right child must be empty.
 */
int isCompleteBinaryTree1(TreeNode *root) {
    if (root == NULL) {
        return 1;
    }
    Queue queue;
    initialQueue(&queue);
    enQueue(&queue, root);
    int flag = 0;
    while (!isQueueEmpty(queue)) {
        TreeNode* currentTreeNode = deQueue(&queue);
        if (currentTreeNode->left) {
            if (flag) {
                return 0;
            }
            enQueue(&queue, currentTreeNode->left);
        }else {
            flag = 1;
        }

        if (currentTreeNode->right) {
            if (flag) {
                return 0;
            }
            enQueue(&queue, currentTreeNode->right);
        }else {
            flag = 1;
        }
    }
    return 1;
}
/**
 A more simple approach would be to check whether the NULL Node encountered is the last node of the Binary Tree.
 If the null node encountered in the binary tree is the last node then it is a complete binary tree and if there
 exists a valid node even after encountering a null node then the tree is not a complete binary tree.
 */
int isCompleteBinaryTree2(TreeNode *root) {
    if (root == NULL) {
        return 1;
    }
    Queue queue;
    initialQueue(&queue);
    enQueue(&queue, root);
    int flag = 0;
    while (!isQueueEmpty(queue)) {
        TreeNode *currentTreeNode = deQueue(&queue);
        if (currentTreeNode == NULL) {
            flag = 1;
        }else {
            if (flag) {
                return 0;
            }
            enQueue(&queue, currentTreeNode->left);
            enQueue(&queue, currentTreeNode->right);
        }
    }
    return 1;
}

int main() {
    TreeNode *root = newTreeNode(1);
    root->left = newTreeNode(2);
    root->right = newTreeNode(3);
    root->left->left = newTreeNode(4);
    root->left->right = newTreeNode(5);
    root->right->left =newTreeNode(6);
    if (isCompleteBinaryTree1(root)) {
        printf("Complete Binary Tree\n");
    }else {
        printf("NOT Complete Binary Tree\n");
    }
    if (isCompleteBinaryTree2(root)) {
        printf("Complete Binary Tree\n");
    }else {
        printf("NOT Complete Binary Tree\n");
    }
    return 0;
}
