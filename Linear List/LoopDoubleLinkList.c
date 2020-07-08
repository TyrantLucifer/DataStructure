/*
* Author: TyrantLucifer
* Function: Loop Double Link List
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
    struct LNode* prior;
}LNode;

/*init Loop Double Link List*/
LNode* initSList(){
    LNode* L = (LNode*)malloc(sizeof(LNode));
    L->data = 0;
    L->next = L;
    L->prior = L->next;
    return L;
}

/*
* print Loop Double Link List
* L: the head pointer of Loop Double Link List
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
* tail insert elem in Loop Double Link List
* data: the value of elem that you want to insert
* L: the head pointer of Loop Double Link List
*/
int tailInsertElem(int data, LNode* L){
    LNode* node = (LNode*)malloc(sizeof(LNode));
    node->data = data;
    node->next = L->prior->next;
    node->prior = L->prior;
    L->prior->next = node;
    L->prior = node;
    L->data++;
    return SUCCESS;
}

/*
* head insert elem in Loop Double Link List
* data: the value of elem that you want to insert
* L: the head pointer of Loop Double Link List
*/
int headInsertElem(int data, LNode* L){
    LNode* node = (LNode*)malloc(sizeof(LNode));
    node->next = L->next;
    node->prior = L;
    node->data = data;
    L->next->prior = node;
    L->next = node;
    return SUCCESS;
}

/*
* find elem in Loop Double Link List
* data: the value of elem that you want to find
* L: the head pointer of Loop Double Link List
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
* delete elem in Loop Double Link List
* data: the value of elem that you want to find
* L: the head pointer of Loop Double Link List
*/
int deleteElem(int data, LNode* L){
    LNode* r = L->next;
    while(r != L){
        if(r->data == data){
            r->prior->next = r->next;
            r->next->prior = r->prior;
            free(r);
            L->data--;
            return SUCCESS;
        }  
        else{
            r = r->next;
        }
    }
    return FAIL;
}

/*main function*/
int main(){
    LNode* L = initSList();
    headInsertElem(1,L);
    headInsertElem(2,L);
    headInsertElem(3,L);
    tailInsertElem(4,L);
    tailInsertElem(5,L);
    tailInsertElem(6,L);
    printSList(L);
    deleteElem(1,L);
    printSList(L);
    return 0;
}

