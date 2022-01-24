/**
 * File Name: BinaryTreeLevelTraverse.c
 * Author: tyrantlucifer
 * E-mail: tyrantlucifer@gmail.com
 * Blog: https://tyrantlucifer.com
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * define struct of tree node
 */
typedef struct TreeNode {
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

/**
 * define struct of queue node
 */
typedef struct QueueNode {
    TreeNode* data;
    struct QueueNode* pre;
    struct QueueNode* next;
}QueueNode;

/**
 * use the char sequence to create a binary tree use pre order
 * @param T the second level of tree root node
 * @param data char sequence
 * @param index the index of char sequence
 */
void createTree(TreeNode** T, char* data, int* index) {
    char ch;
    ch = data[*index];
    *index += 1;
    if (ch == '#') {
        *T = NULL;
    }
    else {
        *T = (TreeNode*)malloc(sizeof(TreeNode));
        (*T) -> data = ch;
        createTree(&((*T)->lchild), data, index);
        createTree(&((*T)->rchild), data, index);
    }
}

/**
 * pre order binary tree
 * @param T the pointer of binary tree
 */
void preOrder(TreeNode* T) {
    if (T == NULL) {
        return;
    }
    else {
        printf("%c ", T->data);
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}

/**
 * init a new queue
 * @return the pointer of queue
 */
QueueNode* initQueue() {
    QueueNode* Q = (QueueNode*)malloc(sizeof(QueueNode));
    Q->data = NULL;
    Q->next = Q;
    Q->pre = Q;
    return Q;
}

/**
 * enqueue
 * @param data the data node pointer your want to enqueue
 * @param Q the pointer of queue
 */
void enQueue(TreeNode* data, QueueNode* Q) {
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = data;
    node->pre = Q;
    node->next = Q;
    Q->pre->next = node;
    Q->pre = node;
}

/**
 * judge the queue is or not empty
 * @param Q the pointer of queue
 * @return 0 or 1
 */
int isEmpty(QueueNode* Q) {
    if (Q->next == Q) {
        return 1;
    }
    else {
        return 0;
    }
}

/**
 * dequeue
 * @param Q the pointer of queue
 * @return the queue node
 */
QueueNode* deQueue(QueueNode* Q) {
    if (isEmpty(Q)) {
        return NULL;
    }
    else {
        QueueNode* node = Q->next;
        Q->next->next->pre = Q;
        Q->next = Q->next->next;
        return node;
    }
}

/**
 * level traverse tree use queue
 * @param Q the pointer of queue
 * @param T the pointer of tree root node
 */
void levelTraverse(QueueNode* Q, TreeNode* T) {
    enQueue(T, Q);
    while (!isEmpty(Q)) {
        QueueNode* node = deQueue(Q);
        printf("%c ", node->data->data);
        if (node->data->lchild) {
            enQueue(node->data->lchild, Q);
        }
        if (node->data->rchild) {
            enQueue(node->data->rchild, Q);
        }
    }
}

/**
 * main function
 * @param argc the num of args
 * @param argv the command args
 * @return int
 */
int main (int argc, char* argv[]) {
    TreeNode* T;
    int index = 0;
    QueueNode* Q = initQueue();
    createTree(&T, argv[1], &index);
    preOrder(T);
    printf("\n");
    levelTraverse(Q, T);
    printf("\n");
    return 0;
}