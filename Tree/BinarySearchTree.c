/**
 * File Name: BinarySearchTree.c
 * Author: tyrantlucifer
 * E-mail: tyrantlucifer@gmail.com
 * Blog: https://tyrantlucifer.com
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * define struct of tree node
 */
typedef struct TreeNode {
    int data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

/**
 * search the data node from a binary search tree
 * @param T the pointer of tree root node
 * @param data the data you want to search
 * @return the pointer of you want to search
 */
TreeNode* bstSearch(TreeNode* T,  int data) {
    if (T) {
        if (T -> data == data) {
            return T;
        }
        else if (data < T -> data) {
            return bstSearch(T -> lchild, data);
        }
        else {
            return bstSearch(T -> rchild, data);
        }
    }
    else {
        return NULL;
    }
}

/**
 * insert a node to a binary search tree
 * @param T the pointer of tree root node
 * @param data the data you want to insert
 */
void bstInsert(TreeNode** T, int data) {
    if (*T == NULL) {
        *T = (TreeNode*)malloc(sizeof(TreeNode));
        (*T) -> data = data;
        (*T) -> lchild = NULL;
        (*T) -> rchild = NULL;
    }
    else if (data == (*T) -> data) {
        return;
    }
    else if (data < (*T) -> data) {
        bstInsert(&((*T) -> lchild), data);
    }
    else {
        bstInsert(&((*T) -> rchild), data);
    }
}

/**
 * pre order tree
 * @param T the pointer of tree root node
 */
void preOrder(TreeNode* T) {
    if (T) {
        printf("%d ", T -> data);
        preOrder(T -> lchild);
        preOrder(T -> rchild);
    }
}

/**
 * main function
 * @param argc the num of args
 * @param argv the command args
 * @return int
 */
int main() {
    TreeNode* T = NULL;
    int nums[6] = {8, 6, 10, 9, 11, 23};
    for (int i = 0; i < 6; i++) {
        bstInsert(&T, nums[i]);
    }
    preOrder(T);
    printf("\n");
}