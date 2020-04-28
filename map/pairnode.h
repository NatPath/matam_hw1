#ifndef PAIRNODE_H_
#define PAIRNODE_H_
#include "pair.h"

typedef struct pairnode_h{
    Pair pair;
    struct pairnode_h *next;
}*PairNode;

//Gets a key and a value and returns a single pairnode which holds them together
/**
 * 
 * 
 * */
//PairNode createPairNode(const char* key,const char* data);
PairNode createPairNode(Pair pair);

//Returns the pair holden in the node
/**
 * 
 * 
 * */
Pair getPairPairNode(PairNode node);

// gets a node, returns the next node linked to it
/**
 * 
 * 
 * */
PairNode getNextPairNode(PairNode node);

//gets a, and sets the next node to be "next"
/**
 * 
 * 
 * */
void setNextPairNode(PairNode node,PairNode next);

// frees only the specified node
/**
 * 
 * 
 * */
void freePairNode(PairNode node);

//gets a node(as a head of a list), free the list and all the data it holds. 
/**
 * 
 * 
 * */
void destroyPairNode(PairNode to_destroy);

//gets a node(as a head of a list), returns the last node in the list. 
/**
 * 
 * 
 * */
PairNode getLastPairNode(PairNode node);

//gets a node(as a head of a list), returns a copy of the list.
/**
 * 
 * 
 * */
PairNode copyPairNode(PairNode to_copy);

/*
    debug functions
*/
void printPairNode(PairNode to_print);




#endif
/**
 * FUNCTIONS GRAVEYARD
 * */

/* 
 ---Before pairnode was split---

//gets a node returns the key it holds
char* getKeyPairNode(PairNode node);

//gets a node returns the value it holds
char* getDataPairNode(PairNode node);

//gets a node return the data 
void setDataPairNode(PairNode node,const char* data);

*/