/**
 * File Name: Queue.c
 * Author: tyrantlucifer
 * E-mail: tyrantlucifer@gmail.com
 * Blog: https://tyrantlucifer.com
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * define the node of queue
 */
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* pre;
} Node;

/**
 * init queue
 * @return the head pointer of queue
 */
Node* initQueue() {
    Node* Q = (Node*)malloc(sizeof(Node));
    Q->data = 0;
    Q->pre = Q;
    Q->next = Q;
    return Q;
}

/**
 * enqueue
 * @param Q the head pointer of queue
 * @param data the data you want to enqueue
 */
void enQueue(Node* Q, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = Q;
    node->pre = Q->pre;
    Q->pre->next = node;
    Q->pre = node;
    Q->data++;
}

/**
 * judge queue is or not empty
 * @param Q the head pointer of queue
 * @return empty flag
 */
int isEmpty(Node* Q) {
    if (Q->data == 0 || Q->next == Q) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * dequeue
 * @param Q the head pointer of queue
 * @return the data of dequeue
 */
int deQueue(Node* Q) {
    if (isEmpty(Q)) {
        return 0;
    } else {
        Node* node = Q->next;
        Q->next = Q->next->next;
        Q->next->pre = Q;
        return node->data;
    }
}

/**
 * print all item in queue
 * @param Q the head pointer of queue
 */
void printQueue(Node* Q) {
    Node* node = Q -> next;
    while (node != Q) {
        printf("%d -> ", node -> data);
        node = node -> next;
    }
    printf("NULL\n");
}

/**
 * main function
 * @return null
 */
int main() {
    Node* Q = initQueue();
    enQueue(Q, 1);
    enQueue(Q, 2);
    enQueue(Q, 3);
    enQueue(Q, 4);
    printQueue(Q);
    printf("dequeue = %d\n", deQueue(Q));
    printf("dequeue = %d\n", deQueue(Q));
    printQueue(Q);
    return 0;
}
