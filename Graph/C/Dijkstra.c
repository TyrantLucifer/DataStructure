/**
 * File Name: Dijkstra.c
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
 * get the min edge index
 * @param d the pointer of d array
 * @param s the pointer of s array
 * @param G the pointer of graph
 * @return
 */
int getMin(int* d, int* s, Graph* G) {
    int min = MAX;
    int index;
    for (int i = 0; i < G -> vexNum; i++) {
        if (!s[i] && d[i] < min) {
            min = d[i];
            index = i;
        }
    }
    return index;
}

/**
 * dijkstra
 * @param G the pointer of graph
 * @param index the index you want to start
 */
void dijkstra(Graph* G, int index) {
    // 准备辅助数组
    int* s = (int*)malloc(sizeof(int) * G -> vexNum);
    int* p = (int*)malloc(sizeof(int) * G -> vexNum);
    int* d = (int*)malloc(sizeof(int) * G -> vexNum);
    // 初始化辅助数组
    for (int i = 0; i < G -> vexNum; i++) {
        if (G -> arcs[index][i] > 0 && G -> arcs[index][i] != MAX) {
            d[i] = G -> arcs[index][i];
            p[i] = index;
        }
        else {
            d[i] = MAX;
            p[i] = -1;
        }
        if (i == index) {
            s[i] = 1;
            d[i] = 0;
        }
        else
            s[i] = 0;
    }
    for (int i = 0; i < G -> vexNum - 1; i++) {
        int index = getMin(d, s, G);
        s[index] = 1;
        for (int j = 0; j < G -> vexNum; j++) {
            if (!s[j] && d[index] + G -> arcs[index][j] < d[j]) {
                d[j] = d[index] + G -> arcs[index][j];
                p[j] = index;
            }
        }
    }
    for (int i = 0; i < G ->vexNum; i++) {
        printf("%d %d %d\n", s[i], p[i], d[i]);
    }
}

/**
 * main function
 * @param argc the num of args
 * @param argv the command args
 * @return int
 */
int main() {
    Graph* G = initGraph(7);
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++)
        visited[i] = 0;
    int arcs[7][7] = {
            0, 12, MAX, MAX, MAX, 16, 14,
            12, 0, 10, MAX, MAX, 7, MAX,
            MAX, 10, 0, 3, 5, 6, MAX,
            MAX, MAX, 3, 0, 4, MAX, MAX,
            MAX, MAX, 5, 4, 0, 2, 8,
            16, 7, 6, MAX, 2, 0, 9,
            14, MAX, MAX, MAX, 8, 9, 0
    };
    createGraph(G, "1234567", (int*)arcs);
    DFS(G, visited, 0);
    printf("\n");
    dijkstra(G, 0);
    return 0;
}