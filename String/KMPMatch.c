/**
 * File Name: KMPMatch.cpp
 * Author: tyrantlucifer
 * E-mail: tyrantlucifer@gmail.com
 * Blog: https://tyrantlucifer.com
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * define struct of string
 */
typedef struct String {
    char* data;
    int len;
} String;

/**
 * init string
 * @return the pointer of string
 */
String* initString() {
    String* s = (String*)malloc(sizeof(String));
    s->data = NULL;
    s->len = 0;
    return s;
}

/**
 * assign value to a string
 * @param s the pointer of string
 * @param data the data you want to assign
 */
void stringAssign(String* s, char* data) {
    if (s->data) {
        free(s->data);
    }
    int len = 0;
    char* temp = data;
    while (*temp) {
        len++;
        temp++;
    }
    if (len == 0) {
        s->data = NULL;
        s->len = 0;
    } else {
        temp = data;
        s->len = len;
        s->data = (char*)malloc(sizeof(char) * (len + 1));
        for (int i = 0; i < len; i++, temp++) {
            s->data[i] = *temp;
        }
    }
}

/**
 * print string
 * @param s the pointer of string
 */
void printString(String* s) {
    for (int i = 0; i < s->len; i++) {
        printf(i == 0 ? "%c " : "-> %c ", s->data[i]);
    }
    printf("\n");
}

/**
 * get next array for a string
 * @param s the pointer of string
 * @return the next array pointer
 */
int* getNext(String* s) {
    int* next = (int*)malloc(sizeof(int) * s->len);
    int i = 0;
    int j = -1;
    next[i] = j;
    while (i < s->len - 1) {
        if (j == -1 || s->data[i] == s->data[j]) {
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
    return next;
}

/**
 * print next array
 * @param next the pointer of array
 * @param len the len of next array
 */
void printNext(int* next, int len) {
    for (int i = 0; i < len; i++) {
        printf(i == 0 ? "%d " : "-> %d ", next[i] + 1);
    }
    printf("\n");
}

/**
 * kmp match
 * @param master the pointer of master string
 * @param sub the pointer of sub string
 * @param next the next array pointer array
 */
void kmpMatch(String* master, String* sub, int* next) {
    int i = 0;
    int j = 0;
    while (i < master->len && j < sub->len) {
        if (j == -1 || master->data[i] == sub->data[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    if (j == sub->len) {
        printf("kmp match success.\n");
    } else {
        printf("kmp match fail.\n");
    }
}

/**
 * main function
 * @param argc the num of args
 * @param argv the array of args
 * @return null
 */
int main(int argc, char* argv[]) {
    String* s = initString();
    String* s1 = initString();
    stringAssign(s, argv[1]);
    printString(s);
    stringAssign(s1, argv[2]);
    printString(s1);
    int* next = getNext(s1);
    printNext(next, s1->len);
    kmpMatch(s, s1, next);
    return 0;
}