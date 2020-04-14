#ifndef PAIRNODE_H_
#define PAIRNODE_H_

typedef struct pairnode_h{
    char* key;
    char* data;
    struct pairnode_h *next;
}*PairNode;

//Gets a key and a value and returns a single pairnode which holds them together
PairNode createPairNode(const char* key,const char* data);

//gets a node returns the key it holds
char* getKeyPairNode(PairNode node);

//gets a node returns the value it holds
char* getDataPairNode(PairNode node);

// gets a node, returns the next node linked to it
PairNode getNextPairNode(PairNode node);

void setNextPairNode(PairNode node,PairNode next);

void setDataPairNode(PairNode node,const char* data);

// frees only the specified node
void freePairNode(PairNode node);

//gets a pairnode, free each node it leads to including itself. 
void destroyPairNode(PairNode to_destroy);

PairNode getLastPairNode(PairNode node);

PairNode copyPairNode(PairNode to_copy);

/*
    debug zone
*/
void printPairNode(PairNode to_print);




#endif