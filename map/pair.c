#include "pair.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <stdio.h>

struct pair_h{
    char* key;
    char* data;
};

//a macro for checking null of a parameter and returning null if so
#define CHECK_NULL(parameter) \
if(!parameter) {\
    return NULL; \
}\
(void)0

Pair createPair(const char* key,const char* data){
    Pair new_pair=malloc(sizeof(*new_pair));
    CHECK_NULL(new_pair);

    new_pair->key=malloc(sizeof(char)*strlen(key)+1);
    CHECK_NULL(new_pair->key);

    new_pair->data=malloc(sizeof(char)*strlen(data)+1);
    CHECK_NULL(new_pair->data);

    strcpy(new_pair->key,key);
    strcpy(new_pair->data,data);

    return new_pair;
}

void destroyPair(Pair to_destroy){
    assert(to_destroy);
    free(to_destroy->key);
    free(to_destroy->data);
    free(to_destroy);
}

char* getKeyPair(Pair pair){
    CHECK_NULL(pair);
    return pair->key;
}

char* getDataPair(Pair pair){
    CHECK_NULL(pair);
    return pair->data;
}

void setDataPair(Pair pair,const char* data){
    assert(pair);
    assert(pair->data);
    free(pair->data);
    pair->data=malloc(sizeof(char)*strlen(data)+1);
    strcpy(pair->data,data);
}

Pair copyPair(Pair to_copy){
    Pair new_pair=createPair(getKeyPair(to_copy),getDataPair(to_copy));
    CHECK_NULL(new_pair);
    return new_pair;
}

void printPair(Pair to_print){

    printf("key: %s , data: %s\n",to_print->key,to_print->data);
}





