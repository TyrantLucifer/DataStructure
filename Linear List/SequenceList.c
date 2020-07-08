/*
* Author: TyrantLucifer
* Function: Sequence List
* Time: 2020-07-07
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define SUCCESS 1
#define FAIL 0

/*define struct*/
typedef struct SqList{
    int data[MAXSIZE];
    int length;
}SqList;

/*init SqList*/
SqList* initList(){
    SqList* L = (SqList*)malloc(sizeof(SqList));
    L->length = 0;
    return L;
}

/*print SqList*/
int printList(SqList* L){
    for(int i = 0; i < L->length; i++){
        printf("%d\t", L->data[i]);
    }
    printf("\n");
}

/*
* add elem in SqList
* data: the value of elem
* L: the pointer of SqList
*/
int addElem(int data, SqList* L){
    if(L->length == MAXSIZE)
        return FAIL;
    L->data[L->length] = data;
    L->length++;
    return SUCCESS;
}

/*
* insert elem in SqList
* index: the index(array index) that you want to insert
* data: the value of elem
* L: the pointer of SqList
*/
int insertElem(int index, int data, SqList* L){
    if(L->length == MAXSIZE)
        return FAIL;
    if(index < 0 || index > MAXSIZE)
        return FAIL;
    for(int i = L->length - 1; i >= index; i--){
        L->data[i + 1] = L->data[i];
    }
    L->data[index] = data;
    L->length++;
    return SUCCESS;
}

/*
* delete elem in SqList
* index: the index(array index) that you want to delete
* L: the pointer of SqList
*/
int deleteElem(int index, SqList* L){
    if(index < 0 || index > MAXSIZE)
        return FAIL;
    for(int i = index; i < L->length - 1; i++){
        L->data[i] = L->data[i + 1];
    }
    L->length--;
    return SUCCESS;
}

/*
* find elem in SqList
* data: the value of elem that you want to find
* L: the pointer of SqList
*/
int findElem(int data, SqList* L){
    for(int i = 0; i < L->length; i++){
        if(L->data[i] == data){
            return i;
        }
    }
    return FAIL;
}

/*main function*/
int main(){
    SqList *L = initList();
    addElem(1,L);
    addElem(3,L);
    addElem(5,L);
    printList(L);
    insertElem(0, 2, L);
    printList(L);
    deleteElem(0, L);
    printList(L);
    return 0;
}