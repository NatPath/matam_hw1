#ifndef PAIRNODE_H_
#define PAIRNODE_H_
#include "pair.h"

typedef struct pairnode_h{
    Pair pair;
    struct pairnode_h *next;
}*PairNode;

/**
 * createPairNode: gets a Pair and creates a node holding it
 * @param pair- the Pair the node created is going to hold
 * @return 
 *      the node created
 * 
 * */
PairNode createPairNode(Pair pair);

/**
 * getPairPairNode: returns the pair of the node
 * @param node- the node we want the pair of
 * @return 
 *      the pair of the node
 * */
Pair getPairPairNode(PairNode node);

 /**
  * getNextPairNode: returns the next field of the node
  * @param node- the node we want the next of
  * @return 
  *      the next node
  * */
PairNode getNextPairNode(PairNode node);

/**
 * setNextPairNode: sets the "next" field of node
 * @param node - the node we set the next of
 * @param next - the node to be set as next
 * 
 * */
void setNextPairNode(PairNode node,PairNode next);

/**
 * freePairNode: free the memory of the node, including the pair it holds
 * @param node - the node we free the memory of
 * 
 * */
void freePairNode(PairNode node);

/**
 * destroyPairNode: gets a head of a list (of pairs), free the memory of all the elements in it
 * @param to_destroy : the head of the list we want to destroy
 * 
 * */
void destroyPairNode(PairNode to_destroy);

/**
 * getLastPairNode: get last pairnode in the list of pairnodes, the first node which its next is null
 * @param node- the node we start from
 * @return 
 *      The first node which doesn't have a node next to it 
 * 
 * */
PairNode getLastPairNode(PairNode node);

/**
 * copyPairNode: return a copy of the list given
 * @param to_copy- the element we want to return a copy of
 * @return
 *      The head of a list identicle to the one given
 * 
 * */
PairNode copyPairNode(PairNode to_copy);





#endif