/*
* Author: TyrantLucifer
* Function: Create Binary Tree and Trverse(Recursive)
* Time: 2020-07-14
*/

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAIL 0

/*define struct*/
typedef struct BiNode{
    char data;
    struct BiNode* lchild;
    struct BiNode* rchild;
}BiNode;

/*
* create Binary Tree use pre order by input(when input '#' it means that create leave node)
* T: the pointer of Binary Tree head node pointer
*/
void createBiTreePreOrder(BiNode** T){
    char ch;
    scanf("%c\n", &ch);
    if(ch == '#'){
        *T = NULL;
    }
    else{
        *T = (BiNode*)malloc(sizeof(BiNode));
        (*T)->data = ch;
        createBiTreePreOrder(&((*T)->lchild));
        createBiTreePreOrder(&((*T)->rchild));
    }
}

/*
* create Binary Tree by String
* T: the pointer of Binary Tree head node pointer
* index: the pointer of string index(init equal 0)
* string: pre order of Binary Tree that you want to create
*/
void createBiTreePreOrderByString(BiNode** T, int* index, char* string){
    char ch;
    ch = string[*index];
    (*index)++;
    if(ch == '#'){
        *T = NULL;
    }
    else{
        *T = (BiNode*)malloc(sizeof(BiNode));
        (*T)->data = ch;
        createBiTreePreOrderByString(&((*T)->lchild), index, string);
        createBiTreePreOrderByString(&((*T)->rchild), index, string);
    }
}

/*
* pre order traverse Binary Tree
* T: the address of Binary Tree head node pointer
*/
void preOrderTraverse(BiNode* T){
    if(T != NULL){
        printf("%c\t", T->data);
        preOrderTraverse(T->lchild);
        preOrderTraverse(T->rchild);
    }
}

/*
* in order traverse Binary Tree
* T: the address of Binary Tree head node pointer
*/
void inOrderTrverse(BiNode* T){
    if(T != NULL){
        inOrderTrverse(T->lchild);
        printf("%c\t", T->data);
        inOrderTrverse(T->rchild);
    }
}

/*
* post order traverse Binary Tree
* T: the address of Binary Tree head node pointer
*/
void postOrderTrverse(BiNode* T){
    if(T != NULL){
        postOrderTrverse(T->lchild);
        postOrderTrverse(T->rchild);
        printf("%c\t", T->data);
    }
}

/*main function*/
int main(){
    BiNode* T;
    int index = 0;
    createBiTreePreOrderByString(&T, &index, "AB##C##");
    preOrderTraverse(T);
    printf("\n");
    inOrderTrverse(T);
    printf("\n");
    postOrderTrverse(T);
    printf("\n");
    return 0;
}

