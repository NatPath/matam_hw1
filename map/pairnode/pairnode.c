#include "pairnode.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

//a macro for checking null of a parameter and returning null if so
#define CHECK_NULL(parameter) \
if(!parameter) {\
    return NULL; \
}\
(void)0

PairNode createPairNode(const char *key,const char* data){
    PairNode new_node=malloc(sizeof(*new_node));
    CHECK_NULL(new_node);
    new_node->key=malloc(sizeof(char)*strlen(key)+1);
    CHECK_NULL(new_node->key);
    new_node->data=malloc(sizeof(char)*strlen(data)+1);
    CHECK_NULL(new_node->data);

    strcpy(new_node->key,key);
    strcpy(new_node->data,data);
    new_node->next=NULL;
    return new_node;
}
char* getKeyPairNode(PairNode node){
    CHECK_NULL(node);
    return node->key;
}
char* getDataPairNode(PairNode node){
    CHECK_NULL(node);
    return node->data;
}

PairNode getNextPairNode(PairNode node){
    CHECK_NULL(node);
    return node->next;
}
void setNextPairNode(PairNode node,PairNode next){
    node->next=next;
}

void setDataPairNode(PairNode node,const char* data){
    assert(node);
    assert(node->data);
    free(node->data);
    node->data=malloc(sizeof(char)*strlen(data)+1);
    strcpy(node->data,data);
}

void freePairNode(PairNode node){
    assert(node);
    free(node->key);
    free(node->data);
    free(node);
}

void destroyPairNode(PairNode to_destroy){
    while(to_destroy){
        PairNode next=to_destroy->next;
        freePairNode(to_destroy);
        to_destroy=next;
    }
}
PairNode getLastPairNode(PairNode node){
    CHECK_NULL(node);
    while (node->next){
        node=node->next;
    }
    return node;
}
PairNode copyPairNode(PairNode to_copy){
    PairNode dummy=createPairNode("foo","bar");
    CHECK_NULL(dummy);
    PairNode head=dummy;
    while(to_copy){
        dummy->next=createPairNode(getKeyPairNode(to_copy),getDataPairNode(to_copy));
        CHECK_NULL(dummy->next);
        dummy=dummy->next;
        to_copy=to_copy->next;
    }
    PairNode res=head->next;
    freePairNode(head);
    return res;
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
