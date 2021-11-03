/*************************************************************************
* File Name: LoopDoubleLinkList.c
* Author: tyrantlucifer
* E-mail: tyrantlucifer@gmail.com
* Blog: https://tyrantlucifer.com
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/**
 * define the struct of list node
 */
typedef struct Node {
    int data;
    struct Node* pre;
    struct Node* next;
}Node;

/**
 * init a link list
 * @return the head pointer of link list's head
 */
Node* initList() {
    Node* L = (Node*)malloc(sizeof(Node));
    L -> data = 0;
    L -> pre = L;
    L -> next = L;
    return L;
}

/**
 * insert item in link list's head
 * @param L the head pointer of link list
 * @param data  the data you want to insert
 */
void headInsert(Node* L, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node -> data = data;
    node -> next = L -> next;
    node -> pre = L;
    L -> next -> pre = node;
    L -> next = node;
    L -> data ++;
}

/**
 * insert item in link list's tail
 * @param L the head pointer of link list
 * @param data the data you want to insert
 */
void tailInsert(Node* L, int data) {
    Node* node = L;
    while (node->next != L) {
        node = node -> next;
    }
    Node* n = (Node*)malloc(sizeof(Node));
    n -> data = data;
    n -> pre = node;
    n -> next = L;
    L -> pre = n;
    node -> next = n;
    L -> data ++;
}

/**
 * delete item in link list
 * @param L the head pointer of link list
 * @param data the data you want to delete
 * @return success flag
 */
int delete(Node* L, int data) {
    Node* node = L -> next;
    while (node != L) {
        if (node -> data == data) {
            node -> pre -> next = node -> next;
            node -> next -> pre = node -> pre;
            free(node);
            L -> data --;
            return 1;
        }
        node = node -> next;
    }
    return 0;
}

/**
 * print all items in a link list
 * @param L the head pointer of link list
 */
void printList(Node* L) {
    Node* node = L -> next;
    while (node != L) {
        printf("%d -> ", node -> data);
        node = node -> next;
    }
    printf("NULL\n");
}

/**
 * main function
 * @return null
 */
int main()
{
    Node* L = initList();
    headInsert(L, 1);
    headInsert(L, 2);
    headInsert(L, 4);
    headInsert(L, 5);
    printList(L);
    tailInsert(L, 6);
    tailInsert(L, 7);
    printList(L);
    delete(L, 7);
    printList(L);
    return 0;
}