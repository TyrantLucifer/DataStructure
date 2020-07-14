/*
* Author: TyrantLucifer
* Function: Sequence Queue
* Time: 2020-07-14
*/

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAIL 0
#define MAXSIZE 100

/*define struct*/
typedef struct SqQueue{
    int data[MAXSIZE];
    int front;
    int rear;
}SqQueue;

/*init queue*/
SqQueue* initQueue(){
    SqQueue* S = (SqQueue*)malloc(sizeof(SqQueue));
    S->front = 0;
    S->rear = 0;
}

/*
* print queue
* S: the pointer of queue
*/
int printQueue(SqQueue* S){
    int i = S->front;
    while(i != S->rear){
        i = (i + 1) % MAXSIZE;
        printf("%d\t", S->data[i]);
    }
    printf("\n");
}

/* 
* judge queue is or not empty
* S: the pointer of queue
*/
int isEmpty(SqQueue* S){
    if(S->front == S->rear){
        return SUCCESS;
    }
    else{
        return FAIL;
    }
}

/*
* judge queue is or not full
* S: the pointer of queue
*/
int isFull(SqQueue* S){
    if((S->rear + 1) % MAXSIZE == S->front){
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
int enQueue(int data, SqQueue* S){
    if(isFull(S)){
        return FAIL;
    }
    else{
        S->rear = (S->rear + 1) % MAXSIZE;
        S->data[S->rear] = data;
        return SUCCESS; 
    }
}

/*
* dequeue
* S: the pointer of queue
*/
int deQueue(SqQueue* S){
    if(isEmpty(S)){
        return FAIL;
    }
    else{
        S->front = (S->front + 1) % MAXSIZE;
        return S->data[S->front];
    }
}

/*main function*/
int main(){
    SqQueue* S = initQueue();
    enQueue(1, S);
    enQueue(2, S);
    enQueue(3, S);
    enQueue(4, S);
    enQueue(5, S);
    printQueue(S);
    deQueue(S);
    deQueue(S);
    printQueue(S);
    return 0;
}