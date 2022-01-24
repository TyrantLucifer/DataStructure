/**
 * File Name: TopLogicalSort.c
 * Author: tyrantlucifer
 * E-mail: tyrantlucifer@gmail.com
 * Blog: https://tyrantlucifer.com
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * define graph struct
 */
typedef struct Graph {
    char* vexs;
    int** arcs;
    int vexNum;
    int arcNum;
}Graph;

/**
 * define stack node struct
 */
typedef struct Node {
    int data;
    struct Node* next;
}Node;

/**
 * init a stack
 * @return the pointer of stack
 */
Node* initStack() {
    Node* stack = (Node*)malloc(sizeof(Node));
    stack -> data = 0;
    stack -> next = NULL;
    return stack;
}

/**
 * judge the stack is or not empty
 * @param stack the pointer of stack
 * @return 0 or 1
 */
int isEmpty(Node* stack) {
    if (stack -> next == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

/**
 * push stack
 * @param stack the pointer of stack
 * @param data the data you want to push
 */
void push(Node* stack, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node -> data = data;
    node -> next = stack -> next;
    stack -> next = node;
    stack -> data ++;
}

/**
 * pop stack
 * @param stack the pointer of stack
 * @return the top item in stack
 */
int pop(Node* stack) {
    if (!isEmpty(stack)) {
        Node* node = stack -> next;
        stack -> next = node -> next;
        return node -> data;
    }
    else {
        return -1;
    }
}

/**
 * find the vexs in degrees of graph
 * @param G the pointer of graph
 * @return the information of in degrees
 */
int* findInDegrees(Graph* G) {
    int* inDegrees = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++) {
        inDegrees[i] = 0;
    }
    for (int i = 0 ; i < G -> vexNum; i++) {
        for (int j = 0; j < G -> vexNum; j++) {
            if (G -> arcs[i][j])
                inDegrees[j] = inDegrees[j] + 1;
        }
    }
    return inDegrees;
}

/**
 * top logical sort
 * @param G the pointer of graph
 */
void topologicalSort(Graph* G) {
    int index = 0;
    int* top = (int*)malloc(sizeof(int) * G -> vexNum);
    int* inDegrees = findInDegrees(G);
    Node* stack = initStack();
    for (int i = 0 ; i < G -> vexNum; i++) {
        if (inDegrees[i] == 0) {
            push(stack, i);
        }
    }
    while (!isEmpty(stack)) {
        int vex = pop(stack);
        top[index++] = vex;
        for (int i = 0 ; i < G -> vexNum; i++) {
            if (G -> arcs[vex][i]) {
                inDegrees[i] = inDegrees[i] - 1;
                if (inDegrees[i] == 0)
                    push(stack, i);
            }
        }
    }
    for (int i = 0; i < index; i++) {
        printf("%c ", G -> vexs[top[i]]);
    }
    printf("\n");
}

/**
 * init graph
 * @param vexNum the vex num of graph
 * @return
 */
Graph* initGraph(int vexNum) {
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G -> vexs = (char*)malloc(sizeof(char) * vexNum);
    G -> arcs = (int**)malloc(sizeof(int*) * vexNum);
    for (int i = 0 ; i < vexNum; i++) {
        G -> arcs[i] = (int*)malloc(sizeof(int) * vexNum);
    }
    G -> vexNum = vexNum;
    G -> arcNum = 0;
    return G;
}

/**
 * create graph
 * @param G
 * @param vexs
 * @param arcs
 */
void createGraph(Graph* G, char* vexs, int* arcs) {
    for (int i = 0 ; i < G -> vexNum; i++) {
        G -> vexs[i] = vexs[i];
        for (int j = 0; j < G -> vexNum; j++) {
            G -> arcs[i][j] = *(arcs + i * G -> vexNum + j);
            if (G -> arcs[i][j] != 0)
                G -> arcNum ++;
        }
    }
    G -> arcNum /= 2;
}

/**
 * dfs graph
 * @param G the pointer of graph
 * @param visited the visited array
 * @param index the index you visited
 */
void DFS(Graph* G, int* visited, int index) {
    printf("%c\t", G -> vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G ->vexNum; i++) {
        if (G -> arcs[index][i] == 1 && !visited[i]) {
            DFS(G, visited, i);
        }
    }
}

/**
 * main function
 * @param argc the num of args
 * @param argv the command args
 * @return int
 */
int main() {
    Graph* G = initGraph(6);
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++)
        visited[i] = 0;
    int arcs[6][6] = {
            0,1,1,1,0,0,
            0,0,0,0,0,0,
            0,1,0,0,1,0,
            0,0,0,0,1,0,
            0,0,0,0,0,0,
            0,0,0,1,1,0
    };
    createGraph(G, "123456", (int*)arcs);
    DFS(G, visited, 0);
    printf("\n");
    topologicalSort(G);
    return 0;
}