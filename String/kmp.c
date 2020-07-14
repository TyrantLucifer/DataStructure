/*
* Author: TyrantLucifer
* Function: KMP Match
* Time: 2020-07-07
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define SUCCESS 1
#define FAIL 0

/*define struct*/
typedef struct Str{
    char* str;
    int length;
}Str;

/*init Str*/
Str* initStr(){
    Str* S = (Str*)malloc(sizeof(Str));
    return S;
}

/*
* print Str
* S: the pointer of Str
*/
int printStr(Str* S){
    for(int i = 0; i < S->length; i++){
        printf("%c\t", S->str[i]);
    }
    printf("\n");
    return SUCCESS;
}

/*
* print next array
* S: the pointer of Str
* next: the pointer of next array
*/
int printNext(Str* S, int* next){
    for(int i = 0; i < S->length; i++){
        printf("%d\t", next[i]);
    }
    printf("\n");
    return SUCCESS;
}

/*
* assing string to Str
* S: the pointer of Str
* str: the string content that you want to assign
*/
int strAssign(Str* S, char* str){
    int len = 0;
    if(S->str){
        free(S->str);
    }
    char* c = str;
    while(*c){
        len++;
        c++;
    }
    if(len == 0){
        S->str = NULL;
        S->length = 0;
        return SUCCESS;
    }
    else{
        S->str = (char*)malloc(sizeof(char) * len + 1);
        c = str;
        for(int i =0; i <= len; i++, c++){
            S->str[i] = *c;
        }
        S->length = len;
        return SUCCESS;
    }

}

/*
* get next array of Str
* S: the pointer of Str
*/
int* getNext(Str* S){
    int* next = (int*)malloc(sizeof(int) * S->length);
    int i = 0, j = -1;
    next[i] = j;
    while(i < S->length - 1){
        if(j == -1 || S->str[i] == S->str[j]){
            i++;
            j++;
            next[i] = j;
        }
        else{
            j = next[j];
        }
        
    }
    return next;
}

/*
* get nextval array of Str
* S: the pointer of Str
*/
int* getNextval(Str* S){
    int* nextval = (int*)malloc(sizeof(int) * S->length);
    int i = 0, j = -1;
    nextval[i] = j;
    while(i < S->length - 1){
        if(j == -1 || S->str[i] == S->str[j]){
            i++;
            j++;
            if(S->str[i] != S->str[j]){
                nextval[i] = j;
            }
            else{
                nextval[i] = nextval[j];
            }
            
        }
        else{
            j = nextval[j];
        }
        
    }
    return nextval;
}

/*
* KMP match
* masterStr: the pointer of master Str
* subStr: the pointer of sub Str 
* next: the next array's pointer of sub Str
*/
int kmpMatch(Str* masterStr, Str* subStr, int* next){
    int i = 0, j = 0;
    while(i < masterStr->length && j < subStr->length){
        if(j == -1 || masterStr->str[i] == subStr->str[j]){
            i++;
            j++;
        }
        else{
            j = next[j];
        }
    }
    if(j == subStr->length){
        return SUCCESS;
    }
    else{
        return FAIL;
    }
    
}

/*main function*/
int main(){
    Str* S1 = initStr();
    strAssign(S1, "ABABA");
    printStr(S1);
    Str* S2 = initStr();
    strAssign(S2, "ABABA");
    printStr(S2);
    int* next = getNext(S2);
    int* nextval = getNextval(S2);
    printNext(S2, next);
    printNext(S2, nextval);
    if(kmpMatch(S1, S2, next)){
        printf("Match Success\n");
    }
    else{
        printf("Match Fail\n");
    }
    return 0;
}