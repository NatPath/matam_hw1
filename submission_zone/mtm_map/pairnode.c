#include "pair.h"
#include "pairnode.h"
#include <stdlib.h>
#include <string.h>

#include <assert.h>

//a macro for checking null of a parameter and returning null if so
#define CHECK_NULL(parameter) \
if(!parameter) {\
    return NULL; \
}\
(void)0


PairNode createPairNode(Pair pair){
    PairNode new_node=malloc(sizeof(*new_node));
    CHECK_NULL(new_node);
    new_node->pair=pair;
    new_node->next=NULL;

    return new_node;
}

Pair getPairPairNode(PairNode node){
    return node->pair;
}

PairNode getNextPairNode(PairNode node){
    CHECK_NULL(node);
    return node->next;
}

void setNextPairNode(PairNode node,PairNode next){
    node->next=next;
}


void freePairNode(PairNode to_free){
    assert(to_free);
    destroyPair(to_free->pair);
    free(to_free);
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
    Pair dummy_pair=createPair("foo","bar");// dummy element to hold the head of the list
    CHECK_NULL(dummy_pair);
    PairNode dummy=createPairNode(dummy_pair);
    CHECK_NULL(dummy);
    PairNode head=dummy;
    while(to_copy){
        Pair temp=copyPair(to_copy->pair);
        CHECK_NULL(temp);

        dummy->next=createPairNode(temp);
        CHECK_NULL(dummy->next);

        dummy=dummy->next;
        to_copy=to_copy->next;
    }
    PairNode res=head->next;
    freePairNode(head);
    return res;
}

