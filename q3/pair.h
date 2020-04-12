#ifndef PAIR_H_
#define PAIR_H_

typedef struct pair_t{
    char *value;
    char *key;
} *Pair;


typedef enum  { SUCCESS, PAIR_OUT_OF_MEMORY } PairResult;
Pair pairCreate(char *value,char *key);


#endif