/**
 * File Name: SequenceSearch.c
 * Author: tyrantlucifer
 * E-mail: tyrantlucifer@gmail.com
 * Blog: https://tyrantlucifer.com
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * define sequence list struct
 */
typedef struct List {
    int* data;
    int length;
    int num;
}List;

/**
 * init sequence list
 * @param length the length of sequence list
 * @return the pointer of list
 */
List* initList(int length) {
    List* list = (List*)malloc(sizeof(List));
    list -> length = length;
    list -> data = (int*)malloc(sizeof(int) * length);
    list -> num = 0;
    return list;
}

/**
 * add item to list
 * @param list the pointer of sequence list
 * @param data the data you want to add
 */
void listAdd(List* list, int data) {
    list -> data[list -> num] = data;
    list -> num = (list -> num) + 1;
}

/**
 * print sequence list
 * @param list the pointer of list
 */
void printList(List* list) {
    for (int i = 0; i < list -> num; i++) {
        printf("%d -> ", list -> data[i]);
    }
    printf("NULL\n");
}

/**
 * search
 * @param list the pointer of sequence list
 * @param key the key you want to search
 * @return 0 or 1
 */
int search(List* list, int key) {
    for (int i = 0 ; i < list -> num; i++) {
        if (list -> data[i] == key)
            return i;
    }
    return -1;
}

/**
 * main function
 * @param argc the num of args
 * @param argv the command args
 * @return int
 */
int main()
{
    List* list = initList(5);
    listAdd(list, 1);
    listAdd(list, 2);
    listAdd(list, 3);
    listAdd(list, 4);
    printList(list);
    printf("%d\n", search(list, 5));
    return 0;
}