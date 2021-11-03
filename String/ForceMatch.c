/**
 * File Name: ForceMatch.c
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
 * @param data the value you want to assign
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
 * force match
 * @param master the pointer of master string
 * @param sub the pointer of sub string
 */
void forceMatch(String* master, String* sub) {
    int i = 0;
    int j = 0;
    while (i < master->len && j < sub->len) {
        if (master->data[i] == sub->data[j]) {
            i++;
            j++;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == sub->len) {
        printf("force match success.\n");
    } else {
        printf("force match fail.\n");
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
    stringAssign(s1, argv[2]);
    printString(s);
    printString(s1);
    forceMatch(s, s1);
    return 0;
}