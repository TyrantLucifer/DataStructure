/**
 * File Name: BinaryTreeNonRecursivePost.c
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
    int flag;
}TreeNode;

/**
 * define struct of stack
 */
typedef struct StackNode {
    TreeNode* data;
    struct StackNode* next;
}StackNode;

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
        (*T) -> flag = 0;
        // 创建左子树，逻辑一致，进行递归
        createTree(&((*T)->lchild), data, index);
        // 创建右子树，逻辑一致，进行递归
        createTree(&((*T)->rchild), data, index);
    }
}

/**
 * init stack
 * @return the pointer of stack
 */
StackNode* initStack() {
    StackNode* S = (StackNode*)malloc(sizeof(StackNode));
    S->data = NULL;
    S->next = NULL;
    return S;
}

/**
 * push stack
 * @param data the pointer of data node you want to push
 * @param S the pointer of stack
 */
void push(TreeNode* data, StackNode* S) {
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->data = data;
    node->next = S->next;
    S->next = node;
}

/**
 * judge stack is or not empty
 * @param S the pointer of stack
 * @return 0 or 1
 */
int isEmpty(StackNode* S) {
    if (S->next == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

/**
 * pop stack
 * @param S the pointer of stack
 * @return the pointer data node that you pop
 */
StackNode* pop(StackNode* S) {
    if (isEmpty(S)) {
        return NULL;
    }
    else {
        StackNode* node = S->next;
        S->next = node->next;
        return node;
    }
}

/**
 * get top data node in a stack
 * @param S the pointer of stack
 * @return the pointer of top data node
 */
StackNode* getTop(StackNode* S) {
    if (isEmpty(S)) {
        return NULL;
    }
    else {
        StackNode* node = S->next;
        return node;
    }
}

/**
 * post order tree
 * @param T the pointer of tree root node
 */
void postOrder(TreeNode* T) {
    TreeNode* node = T;
    StackNode* S = initStack();
    while (node || !isEmpty(S)) {
        if (node) {
            push(node, S);
            node = node -> lchild;
        }
        else {
            TreeNode* top = getTop(S) -> data;
            if (top -> rchild && top -> rchild -> flag == 0) {
                top = top -> rchild;
                push(top, S);
                node = top -> lchild;
            }
            else {
                top = pop(S) -> data;
                printf("%c ", top -> data);
                top -> flag = 1;
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
    int index = 0;
    createTree(&T, argv[1], &index);
    postOrder(T);
    printf("\n");
    return 0;
}