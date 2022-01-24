/**
 * File Name: AVLBinaryTree.c
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
    int height;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

/**
 * get the height of the tree that root node is current node
 * @param node the pointer of tree node
 * @return the height of tree
 */
int getHeight(TreeNode* node) {
    return node ? node -> height : 0;
}

/**
 * select the max num between a and b
 * @param a num a
 * @param b num b
 * @return the max num
 */
int max(int a, int b) {
    return a > b ? a : b;
}

/**
 * rr adjust
 * @param node the pointer of current node
 * @param root the pointer of tree root node
 */
void rrRotation(TreeNode* node, TreeNode** root) {
    TreeNode* temp = node -> rchild;
    node -> rchild = temp -> lchild;
    temp -> lchild = node;
    node -> height = max(getHeight(node -> lchild), getHeight(node -> rchild)) + 1;
    temp -> height = max(getHeight(temp -> lchild), getHeight(temp -> rchild)) + 1;
    *root = temp;
}

/**
 * ll adjust
 * @param node the pointer of current node
 * @param root the pointer of tree root node
 */
void llRotation(TreeNode* node, TreeNode** root) {
    TreeNode* temp = node -> lchild;
    node -> lchild = temp -> rchild;
    temp -> rchild = node;
    node -> height = max(getHeight(node -> lchild), getHeight(node -> rchild)) + 1;
    temp -> height = max(getHeight(temp -> lchild), getHeight(temp -> rchild)) + 1;
    *root = temp;
}

/**
 * insert node to a avl tree
 * @param T the second level pointer of tree root node
 * @param data the data you want to insert
 */
void avlInsert(TreeNode** T, int data) {
    if (*T == NULL) {
        *T = (TreeNode*)malloc(sizeof(TreeNode));
        (*T) -> data = data;
        (*T) -> height = 0;
        (*T) -> lchild = NULL;
        (*T) -> rchild = NULL;
    }
    else if (data < (*T) -> data) {
        avlInsert(&(*T) -> lchild, data);
        // 拿到当前节点左右子树的高度
        int lHeight = getHeight((*T) -> lchild);
        int rHeight = getHeight((*T) -> rchild);
        // 判断高度差
        if (lHeight - rHeight == 2) {
            if (data < (*T) -> lchild -> data) {
                // LL 调整
                llRotation(*T, T);
            }
            else {
                // LR 调整
                rrRotation((*T) -> lchild, &(*T) -> lchild);
                llRotation(*T, T);
            }
        }
    }
    else if (data > (*T) -> data) {
        avlInsert(&(*T) -> rchild, data);
        // 拿到当前节点左右子树的高度
        int lHeight = getHeight((*T) -> lchild);
        int rHeight = getHeight((*T) -> rchild);
        // 判断高度差
        if (rHeight - lHeight == 2) {
            if (data > (*T) -> rchild -> data) {
                // RR 调整
                rrRotation(*T, T);
            }
            else {
                // RL 调整
                llRotation((*T) -> rchild, &(*T) -> rchild);
                rrRotation(*T, T);
            }
        }
    }
    (*T) -> height = max(getHeight((*T) -> lchild), getHeight((*T) -> rchild)) + 1;
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
    int nums[5] = {1,8,6,7,10};
    for (int i = 0; i < 5; i++) {
        avlInsert(&T, nums[i]);
    }
    preOrder(T);
    printf("\n");
}