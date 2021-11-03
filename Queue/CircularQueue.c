/**
 * File Name: CircularQueue.c
 * Author: tyrantlucifer
 * E-mail: tyrantlucifer@gmail.com
 * Blog: https://tyrantlucifer.com
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5

/**
 * define the struct of circular queue
 */
typedef struct Queue {
    int front;
    int rear;
    int data[MAXSIZE];
} Queue;

/**
 * init queue
 * @return the pointer of queue
 */
Queue* initQueue() {
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    Q->front = Q->rear = 0;
    return Q;
}

/**
 * print all items in queue
 * @param Q the pointer of queue
 */
void printQueue(Queue* Q) {
    // 要知道队列当前有多少个元素
    int length = (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
    int index = Q->front;
    for (int i = 0; i < length; i++) {
        printf("%d -> ", Q->data[index]);
        index = (index + 1) % MAXSIZE;
    }
    printf("NULL\n");
}

/**
 * judge queue is or not full
 * @param Q the pointer of queue
 * @return full flag
 */
int isFull(Queue* Q) {
    if ((Q->rear + 1) % MAXSIZE == Q->front) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * judge queue is or not empty
 * @param Q the pointer of queue
 * @return empty flag
 */
int isEmpty(Queue* Q) {
    if (Q->front == Q->rear) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * enqueue
 * @param Q the pointer of queue
 * @param data the data you want to enqueue
 * @return success flag
 */
int enQueue(Queue* Q, int data) {
    if (isFull(Q)) {
        return 0;
    } else {
        Q->data[Q->rear] = data;
        Q->rear = (Q->rear + 1) % MAXSIZE;
        return 1;
    }
}

/**
 * dequeue
 * @param Q the pointer of queue
 * @return the data you want to dequeue
 */
int deQueue(Queue* Q) {
    if (isEmpty(Q)) {
        return -1;
    } else {
        int data = Q->data[Q->front];
        Q->front = (Q->front + 1) % MAXSIZE;
        return data;
    }
}

/**
 * main function
 * @return null
 */
int main() {
    Queue* Q = initQueue();
    enQueue(Q, 1);
    enQueue(Q, 2);
    enQueue(Q, 3);
    enQueue(Q, 4);
    printQueue(Q);
    deQueue(Q);
    printQueue(Q);
    return 0;
}