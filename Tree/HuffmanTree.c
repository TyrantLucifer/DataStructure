#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10000

typedef struct HFTreeNode{
    int weight;
    int parent;
    int lchild;
    int rchild;
}HFTreeNode;

typedef struct HFTree{
    struct HFTreeNode* data;
    int length;
}HFTree;

HFTree* initHFTree(int* weight, int len){
    HFTree* T = (HFTree*)malloc(sizeof(HFTree));
    T->length = len;
    T->data = (HFTreeNode*)malloc(sizeof(HFTreeNode) * (len * 2 - 1));
    for(int i = 0;i < len;i++){
        T->data[i].weight = weight[i];
        T->data[i].parent = 0;
        T->data[i].lchild = 0;
        T->data[i].rchild = 0;
    }
    return T;
}

int* selectMinimum(HFTree* T){
    int min = MAXSIZE;
    int minIndex = 0;
    int secondMin = MAXSIZE;
    int secondMinIndex = 0;
    for(int i = 0;i < T->length;i++){
        if(T->data[i].parent == 0){
            if(T->data[i].weight < min){
                min = T->data[i].weight;
                minIndex = i;
            }
        }
    }
    for(int i = 0;i < T->length;i++){
        if(T->data[i].parent == 0){
            if(i != minIndex){
                if(T->data[i].weight < secondMin){
                    secondMin = T->data[i].weight;
                    secondMinIndex = i;
                }
            }
        }
    }
    int* minArray = (int*)malloc(sizeof(int) * 2);
    minArray[0] = minIndex;
    minArray[1] = secondMinIndex;
    return minArray;
}

int createHFTree(HFTree* T){
    int* minArray;
    int minIndex;
    int secondMinIndex;
    int len = (T->length) * 2 - 1;
    for(int i = T->length;i < len;i++){
        minArray = selectMinimum(T);
        minIndex = minArray[0];
        secondMinIndex = minArray[1];
        T->data[i].weight = T->data[minIndex].weight + T->data[secondMinIndex].weight;
        T->data[i].lchild = minIndex;
        T->data[i].rchild = secondMinIndex;
        T->data[minIndex].parent = i;
        T->data[secondMinIndex].parent = i;
        T->length++; 
    }
    return EXIT_SUCCESS;
}

int printHFTree(HFTree* T){
    printf("index\tweight\tparent\tlchild\trchild\n");
    for(int i = 0;i < T->length;i++){
        printf("%d\t%d\t%d\t%d\t%d\n", 
        i,
        T->data[i].weight,
        T->data[i].parent,
        T->data[i].lchild,
        T->data[i].rchild);
    }
    return EXIT_SUCCESS;
}

int main(){
    int weight[8] = {7,19,2,6,32,3,21,10};
    HFTree* T = initHFTree(weight, 8);
    createHFTree(T);
    printHFTree(T);
    return EXIT_SUCCESS;
}