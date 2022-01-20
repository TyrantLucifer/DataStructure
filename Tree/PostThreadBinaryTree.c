/**
 * File Name: PostThreadBinaryTree.c
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
    struct TreeNode* parent;
    int ltag;
    int rtag;
}TreeNode;

/**
 * use the char sequence to create a binary tree use pre order
 * @param T the second level of tree root node
 * @param data char sequence
 * @param index the index of char sequence
 */
void createTree(TreeNode** T, char* data, int* index, TreeNode* parent) {
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
        (*T) -> parent = parent;
        // 创建左子树，逻辑一致，进行递归
        createTree(&((*T)->lchild), data, index, *T);
        // 创建右子树，逻辑一致，进行递归
        createTree(&((*T)->rchild), data, index, *T);
    }
}

/**
 * create post thread for a binary tree
 * @param T the pointer of tree root node
 * @param pre the second level pointer of the pre node for current node
 */
void postThreadTree(TreeNode* T, TreeNode** pre) {
    if (T) {
        postThreadTree(T -> lchild, pre);
        postThreadTree(T -> rchild, pre);
        // do something
        if (T -> lchild == NULL) {
            T -> ltag = 1;
            T -> lchild = *pre;
        }
        if (*pre != NULL && (*pre) -> rchild == NULL) {
            (*pre) -> rtag = 1;
            (*pre) -> rchild = T;
        }
        *pre = T;
    }
}

/**
 * find the traverse first node in tree
 * @param T the pointer of tree root node
 * @return the pointer of first node
 */
TreeNode* getFirst(TreeNode* T) {
    while (T -> ltag == 0)
        T = T -> lchild;
    if (T -> rtag == 0) {
        return getFirst(T -> rchild);
    }
    return T;
}

/**
 * find a next tree node for current node
 * @param node the pointer of current node
 * @return the pointer of next node
 */
TreeNode* getNext(TreeNode* node) {
    if (node -> rtag == 1)
        return node -> rchild;
    else {
        // 如果是根节点
        if (node -> parent == NULL) {
            return NULL;
        }
            // 如果是右孩子
        else if (node -> parent -> rchild == node) {
            return node -> parent;
        }
            // 如果是左孩子
        else {
            if (node -> parent -> ltag == 0) {
                return getFirst(node -> parent -> rchild);
            }
            else {
                return node -> parent;
            }
        }
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
    TreeNode* pre = NULL;
    int index = 0;
    createTree(&T, argv[1], &index, NULL);
    postThreadTree(T, &pre);
    for (TreeNode* node = getFirst(T); node != NULL; node = getNext(node)) {
        printf("%c ", node -> data);
    }
    printf("\n");
    return 0;
}