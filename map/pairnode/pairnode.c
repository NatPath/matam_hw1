#include "pairnode.h"
#include <stdlib.h>


PairNode createPairNode(char *key,char* value){
    PairNode new_node=malloc(sizeof(*new_node));
    strcpy(new_node->key,key);
    strcpy(new_node->data,value);
    new_node->next=NULL;
    return new_node;
}
char* getKeyPairNode(PairNode node){
    return node->key;
}
char* getDataPairNode(PairNode node){
    return node->data;
}

PairNode getNextPairNode(PairNode node){
    return node->next;
}
void setNextPairNode(PairNode node,PairNode next){
    node->next=next;
}

void setDataPairNode(PairNode node,char* data){
    node->data=data;
}

void freePairNode(PairNode node){
    free(node);
}

void destroyPairNode(PairNode to_destroy){
    while(to_destroy){
        PairNode next=to_destroy->next;
        freePairNode(to_destroy);
        to_destroy=next;
    }
}

/*
    debug zone
*/
void printPairNode(PairNode to_print){
    puts("Printing PairNode...\n");
    while(to_print){
        printf("key: %s , data: %s\n",to_print->key,to_print->data);
        to_print=to_print->next;
    }
}
