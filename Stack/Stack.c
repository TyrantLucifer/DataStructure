/*************************************************************************
 * File Name: Stack.c
 * Author: tyrantlucifer
 * E-mail: tyrantlucifer@gmail.com
 * Blog: https://tyrantlucifer.com
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/**
 * define struct of stack
 */
typedef struct Node {
    int data;
    struct Node *next;
} Node;

/**
 * init stack
 * @return the head pointer of stack
 */
Node *initStack() {
    Node *L = (Node *)malloc(sizeof(Node));
    L->data = 0;
    L->next = NULL;
    return L;
}

/**
 * push item in stack
 * @param L the head pointer of stack
 * @param data the data you want to push
 */
void push(Node *L, int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = L->next;
    L->next = node;
    L->data++;
}

/**
 * pop item in stack
 * @param L the head pointer of stack
 * @return data
 */
int pop(Node *L) {
    if (L->data == 0) {
        return 0;
    } else {
        Node *node = L->next;
        int data = node->data;
        L->next = node->next;
        free(node);
        L->data--;
        return data;
    }
}

/**
 * judge stack is or not empty
 * @param L the head pointer of stack
 * @return empty flag
 */
int isEmpty(Node *L) {
    if (L->data == 0 || L->next == NULL) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * print all items in stack
 * @param stack the head pointer of stack
 */
void printStack(Node *stack) {
    Node *node = stack->next;
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
    Node *stack = initStack();
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    push(stack, 4);
    printStack(stack);
    printf("pop = %d\n", pop(stack));
    printStack(stack);
}