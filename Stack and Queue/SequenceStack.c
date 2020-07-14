/*
* Author: TyrantLucifer
* Function: Sequence Stack
* Time: 2020-07-12
*/

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAIL 0
#define MAXSIZE 100

/*define struct*/
typedef struct SqStack{
    int data[MAXSIZE];
    int top;
}SqStack;

/*init Stack*/
SqStack* initStack(){
    SqStack* S = (SqStack*)malloc(sizeof(SqStack));
    S->top = -1;
    return S;
}

/*
* print Stack
* S: the head pointer of Stack
*/
int printStack(SqStack* S){
    for(int i = S->top;i >= 0;i--){
        printf("%d\t", S->data[i]);
    }
    printf("\n");
    return SUCCESS;
}

/*
* judge stack is empty
* S: the head pointer of Stack
*/
int isEmpty(SqStack* S){
    if(S->top == -1){
        return SUCCESS;
    }
    else{
        return FAIL;
    }
}

/*
* judge stack is full
* S: the head pointer of Stack
*/
int isFull(SqStack* S){
    if(S->top + 1 == MAXSIZE){
        return SUCCESS;
    }
    else{
        return FAIL;
    }
}

/*
* push Stack
* data: the value of elem that you want tu push
*/
int pushStack(int data, SqStack* S){
    if(isFull(S)){
        return FAIL;
    }
    else{
        S->data[++S->top] = data;
    }
    return SUCCESS;
}

/*
* pop Stack
* S: the head pointer of Stack
*/
int popStack(SqStack* S){
    if(isEmpty(S)){
        return FAIL;
    }
    else{
        return S->data[S->top--];
    }
}

/*main function*/
int main(){
    SqStack* S = initStack();
    pushStack(1, S);
    pushStack(2, S);
    pushStack(3, S);
    pushStack(4, S);
    pushStack(5, S);
    printStack(S);
    popStack(S);
    popStack(S);
    printStack(S);
    return 0;

}