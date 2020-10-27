/*************************************************************************
* File Name: AdjacencyListGraph.c
* Author: TyrantLucifer
* E-mail: TyrantLucifer@gmail.com
* Blog: https://tyrantlucifer.com
* Created Time: Wed 21 Oct 2020 10:41:24 PM CST
 ************************************************************************/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define INFINITY 32767

typedef char VexType;
typedef int ArcType;

/*
 * Define arc(边) struct
 * vexIndex: the index's value of vex array
 * weight: the weight of this arc
 * next: the pointer of next arc
 */
typedef struct ArcNode{
    int vexIndex;
    ArcType weight;
    struct ArcNode* next;
}ArcNode;

/*
 * Define vex(顶点) struct
 * data: the name of this vex
 * firstVex: the first arc's pointer of this vex
 */
typedef struct VexNode{
    VexType data;
    ArcNode* firstVex;
}VexNode;

/*
 * Define Graph struct
 * vexs: the pointer of ver array
 * vexNum: the num of this graph's vexs
 * arcNum: the num of this graph's arcs
 */
typedef struct ALGraph{
    VexNode* vexs;
    int vexNum;
    int arcNum;
}ALGraph;

/*
 * Init graph
 * vexNum: the vex's num of this graph
 */
ALGraph* initGraph(int vexNum){
    ALGraph* G = (ALGraph*)malloc(sizeof(ALGraph));
    G->vexs = (VexNode*)malloc(sizeof(VexNode) * vexNum);
    for(int i = 0; i < vexNum; i++){
        G->vexs[i].data = '0';
        G->vexs[i].firstVex = NULL;
    }
    G->vexNum = vexNum;
    G->arcNum = 0;
    return G;
}

/*
 * Create graph
 * vexs: the pointer of vex's name array
 * weight: the pointer of arc's value
 * G: the pointer of graph
 */
void createGraph(VexType* vexs, ArcType* weight, ALGraph* G){
    for(int i = 0; i < G->vexNum; i++){
        G->vexs[i].data = vexs[i];
        for(int j = 0; j < G->vexNum; j++){
            if(*(weight + G->vexNum * i + j) != INFINITY && \
               *(weight + G->vexNum * i + j) != 0){
                ArcNode* node = (ArcNode*)malloc(sizeof(ArcNode));
                node->vexIndex = j;
                node->weight = *(weight + G->vexNum * i + j);
                node->next = G->vexs[i].firstVex;
                G->vexs[i].firstVex = node;
                G->arcNum++;
            }
        }
    }
}

/*Main function*/
int main()
{
    ALGraph* G = initGraph(2);
    ArcType weight[2][2] = {
        0,2,
        2,0
    };
    createGraph("ABC", (int*)weight, G);
    printf("G->vexNum = %d\n", G->vexNum);
    printf("G->arcNum = %d\n", G->arcNum);
    return 0;
}

