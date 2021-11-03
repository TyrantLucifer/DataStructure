/**
 * File Name: SingleLinkList.c
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
    struct Node* next;
} Node;

/**
 * init a link list
 * @return the head pointer of link list's head
 */
Node* initList() {
    Node* L = (Node*)malloc(sizeof(Node));
    L->data = 0;
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
    L->next = node;
    L->data++;
}

/**
 * insert item in link list's tail
 * @param L the head pointer of link list
 * @param data the data you want to insert
 */
void tailInsert(Node* L, int data) {
    Node* node = L;
    for (int i = 0; i < L->data; i++) {
        node = node->next;
    }
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    node->next = n;
    L->data++;
}

/**
 * delete item in link list
 * @param L the head pointer of link list
 * @param data the data you want to delete
 * @return success flag
 */
int delete (Node* L, int data) {
    Node* preNode = L;
    Node* node = L->next;
    while (node) {
        if (node->data == data) {
            preNode->next = node->next;
            free(node);
            L->data--;
            return TRUE;
        }
        preNode = node;
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
        printf("node = %d\n", node->data);
        node = node->next;
    }
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
    headInsert(L, 5);
    tailInsert(L, 6);
    tailInsert(L, 7);
    printList(L);

    if (delete (L, 3)) {
        printf("success delete\n");
    } else {
        printf("fail delete\n");
    }
    printList(L);
    return 0;
}
