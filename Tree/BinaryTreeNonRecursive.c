/*
* Author: TyrantLucifer
* Function: Create Binary Tree and Trverse(Non Recursive)
* Time: 2020-07-14
*/

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAIL 0

/*define Binary Tree Node Struct*/
typedef struct BiNode{
    char data;
    struct BiNode* lchild;
    struct BiNode* rchild;
    int flag;
}BiNode;

/*define Binary Tree Node Struct*/
typedef struct LStackNode{
    BiNode* data;
    struct LStackNode* next;
}LStackNode;

/*init Stack*/
LStackNode* initStack(){
    LStackNode* L = (LStackNode*)malloc(sizeof(LStackNode));
    L->next = NULL;
    L->data = NULL;
    return L;
}

/*
* Judge is or not empty
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
* push stack
* data: the pointer of Binary Tree node
* L: the head pointer of Stack
*/
int pushStack(BiNode* data, LStackNode* L){
    LStackNode* node = (LStackNode*)malloc(sizeof(LStackNode));
    node->data = data;
    node->next = L->next;
    L->next = node;
    return SUCCESS;
}

/*
* pop stack
* L: the head pointer of Stack
*/
LStackNode* popStack(LStackNode* L){
    LStackNode* node = L->next;
    L->next = node->next;
    return node;
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
        (*T)->flag = 0;
        createBiTreePreOrderByString(&((*T)->lchild), index, string);
        createBiTreePreOrderByString(&((*T)->rchild), index, string);
    }
}

/*
* pre order traverse Binary Tree
* T: the address of Binary Tree head node pointer
*/
void preOrderNonRecusiveTraverse(BiNode* T){
    if(T != NULL){
        LStackNode* L = initStack();
        BiNode* bNode;
        LStackNode* lNode;
        pushStack(T, L);
        while(!isEmpty(L)){
            lNode = popStack(L);
            bNode = lNode->data;
            printf("%c\t", bNode->data);
            if(bNode->rchild != NULL){
                pushStack(bNode->rchild, L);
            }
            if(bNode->lchild != NULL){
                pushStack(bNode->lchild, L);
            }
        }
        printf("\n");
    }
}

/*
* in order traverse Binary Tree
* T: the address of Binary Tree head node pointer
*/
void inOrderNonRecusiveTraverse(BiNode* T){
    if(T != NULL){
        LStackNode* L = initStack();
        BiNode* bNode = T;
        LStackNode* lNode;
        while(!isEmpty(L) || bNode != NULL){
            while(bNode != NULL){
                pushStack(bNode, L);
                bNode = bNode->lchild;
            }
            if(!isEmpty(L)){
                lNode = popStack(L);
                bNode = lNode->data;
                printf("%c\t", bNode->data);
                bNode = bNode->rchild;
            }
        }
        printf("\n");
    }
}

/*
* post order traverse Binary Tree
* T: the address of Binary Tree head node pointer
*/
void postOrderNonRecusiveTraverse(BiNode* T){
    LStackNode* L = initStack();
    LStackNode* lNode;
    BiNode* bNode = T;
    T->flag = 1;
    pushStack(T, L);
    while(!isEmpty(L)){
        while(bNode != NULL){
            if((bNode->rchild != NULL) && (bNode->rchild->flag == 0)){
                bNode->rchild->flag = 1;
                pushStack(bNode->rchild, L);                
            }
            if((bNode->lchild != NULL) && (bNode->lchild->flag == 0)){
                bNode->lchild->flag = 1;
                pushStack(bNode->lchild, L);                
            }
            bNode = bNode->lchild;
        }
        if(!isEmpty(L)){
            lNode = popStack(L);
            bNode = lNode->data;
            printf("%c\t", bNode->data);
            if(L->next){
                bNode = L->next->data;
            }
        }
    }
    printf("\n");
}

/*main function*/
int main(){
    BiNode* T;
    int index = 0;
    createBiTreePreOrderByString(&T, &index, "ABC###D##");
    preOrderNonRecusiveTraverse(T);
    inOrderNonRecusiveTraverse(T);
    postOrderNonRecusiveTraverse(T);
    return 0;
}