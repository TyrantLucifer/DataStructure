/*************************************************************************
* File Name: bTree.c
* Author: TyrantLucifer
* E-mail: TyrantLucifer@gmail.com
* Blog: https://tyrantlucifer.com
* Created Time: Sat 26 Mar 2022 11:30:30 PM CST
 ************************************************************************/
#include <endian.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int level; // 树的阶数
    int keyNum; // 关键字数量
    int childNum; // 孩子数量
    int* keys; // 关键字数组
    struct Node** chidren; // 孩子数组
    struct Node* parent; // 父亲指针
} Node;

// 初始化结点
Node* initNode(int level) {
    Node* node = (Node*)malloc(sizeof(Node));
    node -> level = level;
    node -> keyNum = 0;
    node -> childNum = 0;
    node -> keys = (int*)malloc(sizeof(int) * (level + 1));
    node -> chidren = (Node**)malloc(sizeof(Node*) * (level + 1));
    node -> parent = NULL;
    int i;
    for (i = 0; i < level; i++) {
        node -> keys[i] = 0;
        node -> chidren[i] = NULL;
    }
    node -> keys[i] = 0;
    return node;
}

// 在结点处寻找合适的插入索引
int findSuiteIndex(Node* node, int data) {
    int index;
    for (index = 1; index <= node -> keyNum; index++) {
        if (data < node -> keys[index]) {
            break;
        }
    }
    return index;
}

// 找到合适的叶子结点
Node* findSuiteLeafNode(Node* T, int data) {
    if (T -> childNum == 0) {
        return T;
    } else {
        int index = findSuiteIndex(T, data);
        return findSuiteLeafNode(T -> chidren[index - 1], data);
    }
}

void addData(Node* node, int data, Node** T) {
    int index = findSuiteIndex(node, data);
    for (int i = node -> keyNum; i >= index; i--) {
        node -> keys[i + 1] = node -> keys[i];
    }
    node -> keys[index] = data;
    node -> keyNum++;
    // 判断是否进行分裂
    if (node -> keyNum == node -> level) {
        // 找到分裂位置
        int mid = node -> level / 2 + node -> level % 2;
        // 分裂
        Node* lchild = initNode(node -> level);
        Node* rchild = initNode(node -> level);
        for (int i = 1; i < mid; i++) {
            addData(lchild, node -> keys[i], T);
        }
        for (int i = mid + 1; i <= node -> keyNum; i++) {
            addData(rchild, node -> keys[i], T);
        }
        for (int i = 0; i < mid; i++) {
            lchild -> chidren[i] = node -> chidren[i];
            if (node -> chidren[i] != NULL) {
                node -> chidren[i] -> parent = lchild;
                lchild -> childNum ++;
            }
        }
        int index = 0;
        for (int i = mid; i < node -> childNum; i++) {
            rchild -> chidren[index++] = node -> chidren[i];
            if (node -> chidren[i] != NULL) {
                node -> chidren[i] -> parent = rchild;
                rchild -> childNum ++;
            }
        }
        // 对父亲进行判断
        if (node -> parent == NULL) {
            Node* newParent = initNode(node -> level);
            addData(newParent, node -> keys[mid], T);
            newParent -> chidren[0] = lchild;
            newParent -> chidren[1] = rchild;
            newParent -> childNum = 2;
            lchild -> parent = newParent;
            rchild -> parent = newParent;
            *T = newParent;
        } else {
            int index = findSuiteIndex(node -> parent, node -> keys[mid]);
            lchild -> parent = node -> parent;
            rchild -> parent = node -> parent;
            node -> parent -> chidren[index - 1] = lchild;
            if (node -> parent -> chidren[index] != NULL) {
                for (int i = node -> parent -> childNum - 1; i >= index; i--) {
                    node -> parent -> chidren[i + 1] = node -> parent -> chidren[i];
                }
            }
            node -> parent -> chidren[index] = rchild;
            node -> parent -> childNum++;
            addData(node -> parent, node -> keys[mid], T);
        }
    }
}

void insert(Node** T, int data) {
    Node* node = findSuiteLeafNode(*T, data);
    addData(node, data, T);
}

void printTree(Node* T) {
    if (T != NULL) {
        for (int i = 1; i <= T -> keyNum; i++) {
            printf("%d ", T -> keys[i]);
        }
        printf("\n");
        for (int i = 0; i < T -> childNum; i++) {
            printTree(T -> chidren[i]);
        }
    }
}

int main()
{
    Node* T = initNode(5);
    insert(&T, 1);
    insert(&T, 2);
    insert(&T, 3);
    insert(&T, 4);
    insert(&T, 5);
    insert(&T, 10);
    insert(&T, 15);
    insert(&T, 17);
    insert(&T, 19);
    insert(&T, 20);
    insert(&T, 21);
    insert(&T, 22);
    insert(&T, 23);
    insert(&T, 24);
    insert(&T, 6);
    insert(&T, 7);
    insert(&T, 8);
    printTree(T);
    return 0;
}


