/**
 * File Name: DoubleLinkList.c
 * Author: tyrantlucifer
 * E-mail: tyrantlucifer@gmail.com
 * Blog: https://tyrantlucifer.com
 */
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/**
 * define the struct of list node
 */
typedef struct Node {
    int data;
    struct Node* pre;
    struct Node* next;
} Node;

/**
 * init a link list
 * @return the head pointer of link list's head
 */
Node* initList() {
    Node* L = (Node*)malloc(sizeof(Node));
    L->data = 0;
    L->pre = NULL;
    L->next = NULL;
    return L;
}

/**
 * insert item in link list's head
 * @param L the head pointer of link list
 * @param data  the data you want to insert
 */
void headInsert(Node* L, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = L->next;
    node->pre = L;
    if (L->next) {
        L->next->pre = node;
        L->next = node;
    } else {
        L->next = node;
    }
}

/**
 * insert item in link list's tail
 * @param L the head pointer of link list
 * @param data the data you want to insert
 */
void tailInsert(Node* L, int data) {
    Node* node = L;
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    while (node->next) {
        node = node->next;
    }
    n->next = node->next;
    node->next = n;
    n->pre = node;
    L->data++;
}

/**
 * delete item in link list
 * @param L the head pointer of link list
 * @param data the data you want to delete
 * @return success flag
 */
int delete (Node* L, int data) {
    Node* node = L->next;
    while (node) {
        if (node->data == data) {
            node->pre->next = node->next;
            if (node->next) {
                node->next->pre = node->pre;
            }
            L->data--;
            free(node);
            return TRUE;
        }
        node = node->next;
    }
    return FALSE;
}

/**
 * print all items in a link list
 * @param L the head pointer of link list
 */
void printList(Node* L) {
    Node* node = L->next;
    while (node) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

/**
 * main function
 * @return null
 */
int main() {
    Node* L = initList();
    headInsert(L, 1);
    headInsert(L, 2);
    headInsert(L, 3);
    headInsert(L, 4);
    tailInsert(L, 5);
    tailInsert(L, 6);
    printList(L);
    delete (L, 6);
    printList(L);
    return 0;
}
