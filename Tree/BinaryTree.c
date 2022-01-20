/**
 * FILE NAME: BINARYTREE.C
 * AUTHOR: TYRANTLUCIFER
 * E-MAIL: TYRANTLUCIFER@GMAIL.COM
 * BLOG: HTTPS://TYRANTLUCIFER.COM
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * define struct of tree node
 */
typedef struct TreeNode {
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

/**
 * use the char sequence to create a binary tree use pre order
 * @param T the second level of tree root node
 * @param data char sequence
 * @param index the index of char sequence
 */
void createTree(TreeNode** T, char* data, int* index) {
    char ch;
    ch = data[*index];
    *index += 1;
    if (ch == '#') {
        // 此时为空节点
        *T = NULL;
    }
    else {
        // 此时不为空
        *T = (TreeNode*)malloc(sizeof(TreeNode));
        (*T) -> data = ch;
        // 创建左子树，逻辑一致，进行递归
        createTree(&((*T)->lchild), data, index);
        // 创建右子树，逻辑一致，进行递归
        createTree(&((*T)->rchild), data, index);
    }
}

/**
 * pre order binary tree
 * @param T the pointer of binary tree
 */
void preOrder(TreeNode* T) {
    if (T == NULL) {
        return;
    }
    else {
        // 先办事
        printf("%c ", T->data);
        // 处理左孩子
        preOrder(T->lchild);
        // 处理右孩子
        preOrder(T->rchild);
    }
}

/**
 * in order binary tree
 * @param T the pointer of binary tree
 */
void inOrder(TreeNode* T) {
    if (T == NULL) {
        return;
    }
    else {
        // 处理左孩子
        inOrder(T->lchild);
        // 中办事
        printf("%c ", T->data);
        // 处理右孩子
        inOrder(T->rchild);
    }
}

/**
 * post order binary tree
 * @param T the pointer of binary tree
 */
void postOrder(TreeNode* T) {
    if (T == NULL) {
        return;
    }
    else {
        // 处理左孩子
        postOrder(T->lchild);
        // 处理右孩子
        postOrder(T->rchild);
        // 后办事
        printf("%c ", T->data);
    }
}

/**
 * main function
 * @param argc the num of args
 * @param argv the command args
 * @return int
 */
int main(int argc, char* argv[]) {
    TreeNode* T;
    int index = 0;
    createTree(&T, argv[1], &index);
    preOrder(T);
    printf("\n");
    inOrder(T);
    printf("\n");
    postOrder(T);
    printf("\n");
    return 0;
}