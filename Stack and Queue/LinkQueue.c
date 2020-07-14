/*
* Author: TyrantLucifer
* Function: Link Queue
* Time: 2020-07-14
*/

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAIL 0

/*define Queue Node struct*/
typedef struct QNode{
    int data;
    struct QNode* next;
}QNode;

/*define Queue head Node struct*/
typedef struct LiQueue{
    struct QNode* front;
    struct QNode* rear;
}LiQueue;

/*init queue*/
LiQueue* initQueue(){
    LiQueue* L = (LiQueue*)malloc(sizeof(LiQueue));
    L->front = NULL;
    L->rear = NULL;
}

/*
* print queue
* L: the point of queue
*/
int printQueue(LiQueue* L){
    QNode* node = L->front;
    while(node){
        printf("%d\t", node->data);
        node = node->next;
    }
    printf("\n");
}

/*
* judge queue is or not empty
* L: the point of queue
*/
int isEmpty(LiQueue* L){
    if(L->front == NULL || L->rear == NULL){
        return SUCCESS;
    }
    else{
        return FAIL;
    }
}

/*
* enqueue
* data: the value you want to enqueue
* S: the pointer of queue
*/
int enQueue(int data, LiQueue* L){
    QNode* node = (QNode*)malloc(sizeof(QNode));
    node->data = data;
    node->next = NULL;
    if(L->rear == NULL){
        L->rear = L->front = node;
        node->next = NULL;
    }
    else{
        L->rear->next = node;
        L->rear = node;
    }
}

/*
* dequeue
* S: the pointer of queue
*/
int deQueue(LiQueue* L){
    if(isEmpty(L)){
        return FAIL;
    }
    else{
        QNode* node = L->front;
        int data = node->data;
        if(L->front == L->rear){
            L->front = L->rear = NULL;
        }
        else{
            L->front = node->next;
        }
        free(node);
        return data;
    }
}

/*main function*/
int main(){
    LiQueue* L = initQueue();
    enQueue(1, L);
    enQueue(2, L);
    enQueue(3, L);
    printQueue(L);
    deQueue(L);
    printQueue(L); 
    return 0;
}