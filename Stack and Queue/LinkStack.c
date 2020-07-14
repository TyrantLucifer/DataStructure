/*
* Author: TyrantLucifer
* Function: Sequence Stack
* Time: 2020-07-12
*/

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAIL 0

/*define struct*/
typedef struct LStackNode{
    int data;
    struct LStackNode* next;
}LStackNode;

/*init Stack*/
LStackNode* initStack(){
    LStackNode* L = (LStackNode*)malloc(sizeof(LStackNode));
    L->data = 0;
    L->next = NULL;
    return L;
}

/*
* print Stack
* L: the head pointer of Stack
*/
int printStack(LStackNode* L){
    LStackNode* n = L->next;
    while(n){
        printf("%d\t", n->data);
        n = n->next;
    }
    printf("\n");
    return SUCCESS;
}

/*
* judge Stack is empty
* L: the head pointer of Stack
*/
int isEmpty(LStackNode* L){
    if(L->next == NULL){
        return SUCCESS;
    }
    else{
        return FAIL;
    }
}

/*
* push Stack
* L: the head pointer of Stack
* data: the value of elem that you want to push
*/
int pushStack(int data, LStackNode* L){
    LStackNode* node = (LStackNode*)malloc(sizeof(LStackNode));
    node->data = data;
    node->next = L->next;
    L->next = node;
    L->data++;
    return SUCCESS;
}

/*
* pop Stack
* L: the head pointer of Stack
*/
int popStack(LStackNode* L){
    if(isEmpty(L)){
        return FAIL;
    }
    else{
        LStackNode* node = L->next;
        int data = node->data;
        L->next = node->next;
        free(node);
        L->data--;
        return data;
    }
}

/*main function*/
int main(){
    LStackNode* L = initStack();
    pushStack(1, L);
    pushStack(2, L);
    pushStack(3, L);
    printStack(L);
    popStack(L);
    printStack(L);
    return 0;
}