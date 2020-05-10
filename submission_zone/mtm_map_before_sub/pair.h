#ifndef PAIR_H_
#define PAIR_H_

//The purpose of Pair is to hold 2 Strings together as a pair.
typedef struct pair_h* Pair; 


/**
 * createPair: Creates a Pair, allocation of memory 
 * 
 * @param key- One of the strings to hold together
 * @param data- The other 
 * @return 
 *  The Pair created if all memoery allocation went well.
 *  NULL, if malloc failed somewhere.
 * 
 * */
Pair createPair(const char* key,const char* data);

/**
 * destroyPair: Destroy a Pair, free all the memory it holds
 * 
 * @param to_destory- the Pair to be destroyed
 * 
 * */
void destroyPair(Pair to_destroy);

/**
 * getKeyPair: Return the "key" field of the Pair given.
 * 
 * @param pair- The Pair we grab the key of.
 * @return 
 *      the actual key string (not a copy of it)
 * 
 * */
char* getKeyPair(Pair pair);

/**
 * getDataPair: Return the "data" field of the Pair given.
 * 
 * @param pair- The Pair we grab the data of.
 * @return 
 *      the actual data string (not a copy of it)
 * 
 * */
char* getDataPair(Pair pair);
/**
 * setDataPair: Change the data field of pair
 * 
 * @param pair- The Pair we set the data of.
 * @param data- The new data
 * 
 * */
void setDataPair(Pair pair,const char* data);

/**
 * copyPair: Copy a given pair
 * @param to_copy- the pair to be copied
 * @return 
 *      The resultant pair, if succeded
 *      NULL, if malloc failed somewehere
 * 
 * */
Pair copyPair(Pair to_copy);


#endif