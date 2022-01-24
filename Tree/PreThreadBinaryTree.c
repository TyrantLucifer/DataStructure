/**
 * File Name: PreThreadBinaryTree.c
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
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
    int ltag;
    int rtag;
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
        (*T) -> ltag = 0;
        (*T) -> rtag = 0;
        // 创建左子树，逻辑一致，进行递归
        createTree(&((*T)->lchild), data, index);
        // 创建右子树，逻辑一致，进行递归
        createTree(&((*T)->rchild), data, index);
    }
}

/**
 * create pre thread for a binary tree
 * @param T the pointer of tree root node
 * @param pre the second level pointer of the pre node for current node
 */
void preThreadTree(TreeNode* T, TreeNode** pre) {
    if (T) {
        if (T -> lchild == NULL) {
            T -> ltag = 1;
            T -> lchild = *pre;
        }
        if (*pre != NULL && (*pre) -> rchild == NULL) {
            (*pre) -> rtag = 1;
            (*pre) -> rchild = T;
        }
        *pre = T;
        if (T -> ltag == 0)
            preThreadTree(T -> lchild, pre);
        preThreadTree(T -> rchild, pre);
    }
}

/**
 * find a next tree node for current node
 * @param node the pointer of current node
 * @return the pointer of next node
 */
TreeNode* getNext(TreeNode* node) {
    if (node -> rtag == 1 || node -> ltag == 1)
        return node -> rchild;
    else
        return node -> lchild;
}

/**
 * main function
 * @param argc the num of args
 * @param argv the command args
 * @return int
 */
int main(int argc, char* argv[]) {
    TreeNode* T;
    TreeNode* pre = NULL;
    int index = 0;
    createTree(&T, argv[1], &index);
    preThreadTree(T, &pre);
    pre -> rtag = 1;
    pre -> rchild = NULL;
    for (TreeNode* node = T; node != NULL; node = getNext(node)) {
        printf("%c ", node -> data);
    }
    printf("\n");
    return 0;
}