/**
 * File Name: Prim.c
 * Author: tyrantlucifer
 * E-mail: tyrantlucifer@gmail.com
 * Blog: https://tyrantlucifer.com
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX 32767

/**
 * define graph struct
 */
typedef struct Graph {
    char* vexs;
    int** arcs;
    int vexNum;
    int arcNum;
}Graph;

typedef struct Edge {
    char vex;
    int weight;
}Edge;

/**
 * init edge information
 * @param G
 * @param index
 * @return
 */
Edge* initEdge(Graph* G, int index) {
    Edge* edge = (Edge*)malloc(sizeof(Edge) * G -> vexNum);
    for (int i = 0; i < G ->vexNum; i++) {
        edge[i].vex = G -> vexs[index];
        edge[i].weight = G -> arcs[index][i];
    }
    return edge;
}

/**
 * get the most min edge
 * @param edge the pointer of edge array
 * @param G the pointer of graph
 * @return
 */
int getMinEdge(Edge* edge, Graph* G) {
    int index;
    int min = MAX;
    for (int i = 0; i < G -> vexNum; i++) {
        if (edge[i].weight != 0 && min > edge[i].weight) {
            min = edge[i].weight;
            index = i;
        }
    }
    return index;
}

/**
 * prim
 * @param G the pointer of graph
 * @param index the index of you visited
 */
void prim(Graph* G, int index) {
    int min;
    Edge* edge = initEdge(G, index);
    for (int i = 0; i < G -> vexNum - 1; i++) {
        min = getMinEdge(edge, G);
        printf("v%c --> v%c, weight = %d\n", edge[min].vex, G -> vexs[min], edge[min].weight);
        edge[min].weight = 0;
        for (int j = 0; j < G -> vexNum; j++) {
            if (G -> arcs[min][j] < edge[j].weight) {
                edge[j].weight = G -> arcs[min][j];
                edge[j].vex = G -> vexs[min];
            }
        }
    }
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
            if (G -> arcs[i][j] != 0 && G -> arcs[i][j] != MAX)
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
        if (G -> arcs[index][i] > 0 && G -> arcs[index][i] != MAX && !visited[i]) {
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
            0, 6, 1, 5, MAX, MAX,
            6, 0, 5, MAX, 3, MAX,
            1, 5, 0, 5, 6, 4,
            5, MAX, 5, 0, MAX, 2,
            MAX, 3, 6, MAX, 0, 6,
            MAX, MAX, 4, 2, 6, 0
    };
    createGraph(G, "123456", (int*)arcs);
    DFS(G, visited, 0);
    printf("\n");
    prim(G, 0);
    return 0;
}