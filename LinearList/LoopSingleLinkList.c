/*************************************************************************
* File Name: LoopSingleLinkList.c
* Author: tyrantlucifer
* E-mail: tyrantlucifer@gmail.com
* Blog: https://tyrantlucifer.com
 ************************************************************************/
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
}Node;

/**
 * init a link list
 * @return the head pointer of link list's head
 */
Node* initList() {
    Node* L = (Node*)malloc(sizeof(Node));
    L -> data = 0;
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
    L -> next = node;
    L -> data ++;
}

/**
 * insert item in link list's tail
 * @param L the head pointer of link list
 * @param data the data you want to insert
 */
void tailInsert(Node* L, int data) {
    Node* n = L;
    Node* node = (Node*)malloc(sizeof(Node));
    node -> data = data;
    while(n -> next != L){
        n = n -> next;
    }
    node -> next = L;
    n -> next = node;
    L -> data ++;
}

/**
 * delete item in link list
 * @param L the head pointer of link list
 * @param data the data you want to delete
 * @return success flag
 */
int delete(Node* L, int data) {
    Node* preNode = L;
    Node* node = L -> next;
    while(node != L){
        if(node -> data == data){
            preNode -> next = node -> next;
            free(node);
            L -> data --;
            return TRUE;
        }
        preNode = node;
        node = node -> next;
    }
    return FALSE;
}

/**
 * print all items in a link list
 * @param L the head pointer of link list
 */
void printList(Node* L) {
    Node* node = L -> next;
    while(node != L){
        printf("%d->", node -> data);
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
    headInsert(L, 3);
    headInsert(L, 4);
    headInsert(L, 5);
    tailInsert(L, 6);
    tailInsert(L, 7);
    printList(L);
    delete(L, 4);
    delete(L, 7);
    printList(L);
    return 0;
}