/*
* Author: TyrantLucifer
* Function: Loop Single Link List
* Time: 2020-07-08
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define SUCCESS 1
#define FAIL 0

/*define struct*/
typedef struct LNode{
    int data;
    struct LNode* next;
}LNode;

/*init Loop Single Link List*/
LNode* initSList(){
    LNode* L = (LNode*)malloc(sizeof(LNode));
    L->data = 0;
    L->next = L;
    return L;
}

/*
* print Loop Single Link List
* L: the head pointer of Loop Single Link List
*/
int printSList(LNode* L){
    LNode* r = L->next;
    while(r != L){
        printf("%d\t", r->data);
        r = r->next;
    }
    printf("\n");
    return SUCCESS;
}

/*
* tail insert elem in Loop Single Link List
* data: the value of elem that you want to insert
* L: the head pointer of Loop Single Link List
*/
int tailInsertElem(int data, LNode* L){
    LNode* node = (LNode*)malloc(sizeof(LNode));
    node->next = L;
    node->data = data;
    LNode* r = L;
    while(r->next != L){
        r = r->next;
    }
    r->next = node;
    L->data++;
    return SUCCESS;
}

/*
* head insert elem in Loop Single Link List
* data: the value of elem that you want to insert
* L: the head pointer of Loop Single Link List
*/
int headInsertElem(int data, LNode* L){
    LNode* node = (LNode*)malloc(sizeof(LNode));
    node->next = L->next;
    node->data = data;
    L->next = node;
    L->data++;
    return SUCCESS;
}

/*
* find elem in Loop Single Link List
* data: the value of elem that you want to find
* L: the head pointer of Loop Single Link List
*/
LNode* findElem(int data, LNode* L){
    LNode* r = L->next;
    while(r != L){
        if(r->data == data)
            return r;
        else
            r = r->next;
    }
    return r;
}

/*
* delete elem in Loop Single Link List
* data: the value of elem that you want to find
* L: the head pointer of Loop Single Link List
*/
int deleteElem(int data, LNode* L){
    LNode* r = L->next;
    LNode* s = L;
    while(r != L){
        if(r->data == data){
            s->next = r->next;
            free(r);
            L->data--;
            return SUCCESS;
        }  
        else{
            s = r;
            r = r->next;
        }
    }
    return FAIL;
}

/*main function*/
int main(){
    LNode* L = initSList();
    tailInsertElem(1,L);
    tailInsertElem(2,L);
    tailInsertElem(3,L);
    headInsertElem(4,L);
    printSList(L);
    deleteElem(4,L);
    printSList(L);
    return 0;
}