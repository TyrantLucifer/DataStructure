/*************************************************************************
* File Name: BinarySearchTree.c
* Author: TyrantLucifer
* E-mail: TyrantLucifer@gmail.com
* Blog: https://tyrantlucifer.com
* Created Time: Sat 10 Oct 2020 04:22:23 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAIL 0

/*Define binary tree node struct*/
typedef struct BiNode{
    int data;
    struct BiNode* lchild;
    struct BiNode* rchild;
}BiNode;

/*Insert node in binary search tree*/
int insertBST(BiNode** T, int data){
    if(*T == NULL){
        *T = (BiNode*)malloc(sizeof(BiNode));
        (*T)->data = data;
        (*T)->lchild = (*T)->rchild = NULL;
        return SUCCESS;
    }
    else if(data == (*T)->data){
        return FAIL;
    }
    else if(data < (*T)->data){
        return insertBST(&((*T)->lchild), data);
    }
    else{
        return insertBST(&((*T)->rchild), data);
    }
}

/*Find node in binary search tree*/
BiNode* findBST(BiNode* T, int data){
    if(T == NULL){
        return NULL;
    }
    else if(data == T->data){
        return T;
    }
    else if(data < T->data){
        return findBST(T->lchild, data);
    }
    else{
        return findBST(T->rchild, data);
    }
}

/*In order trverse binary tree*/
void inOrderTrverse(BiNode* T){
    if(T != NULL){
        inOrderTrverse(T->lchild);
        printf("%d\t", T->data);
        inOrderTrverse(T->rchild);
    }
}

/*Create binary search tree*/
void createBST(BiNode** T, int* nums, int n){
    for(int i = 0; i < n; i++){
        insertBST(T, nums[i]);
    }
}

/*Main function*/
int main()
{
    BiNode* T = NULL;
    int nums[5] = {5,4,3,2,1};
    createBST(&T, nums, 5);
    inOrderTrverse(T);
    printf("\n");
    return 0;
}

