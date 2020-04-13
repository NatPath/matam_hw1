#ifndef PAIRNODE_H_
#define PAIRNODE_H_

typedef struct pairnode_h{
    char* key;
    char* data;
    struct pairnode_h *next;
}*PairNode;

//Gets a key and a value and returns a single pairnode which holds them together
PairNode createPairNode(char* key,char* data);

//gets a node returns the key it holds
char* getKeyPairNode(PairNode node);

//gets a node returns the value it holds
char* getDataPairNode(PairNode node);

// gets a node, returns the next node linked to it
PairNode getNextPairNode(PairNode node);

void setNextPairNode();

void setDataPairNode(PairNode node,char* data);

// frees only the specified node
void freePairNode(PairNode node);

//gets a pairnode, free each node it leads to including itself. 
void destroyPairNode(PairNode to_destroy);

/*
    debug zone
*/
void printPairNode(PairNode to_print);




#endif