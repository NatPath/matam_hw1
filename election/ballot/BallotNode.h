#ifndef NODEBALLOT_H_
#define NODEBALLOT_H_

typedef struct ballot_t *BallotNode ;

typedef enum BallotNodeResult_t{
    BALLOT_SUCCESS,
    BALLOT_DOES_NOT_EXIST,
    BALLOT_MAP_ERROR
} BallotNodeResult;

//creates a ballot, inits an empty map for it.
BallotNode ballotNodeCreate(int area_id);

//returns area_id of ballot
int ballotNodeGetAreaId(BallotNode ballot);

//destroy a ballot, frees its memory
void ballotNodeDestroy(BallotNode to_destroy);

/**
* ballotNodeFind: returns a node with the given id it exists, returns NULL otherwise
* @param ballotNode - The first Node in the list
* @param area_id - The id to look for
* @param previous - a pointer of BallotNode, which will point to the element before the one we look for if found
*               if not found, will contain NULL
*               if you're not intrested in the previous, send as NULL
* @return 
* if found, The searched ballotNode with the given area_id
* NULL, if not found
**/
BallotNode ballotNodeFind(BallotNode ballot_list,int area_id,BallotNode* previous);

/**
 * ballotNodeSearchAndDestroy: searches for a node with a given area_id, if it exists, remove it from the List
 * @param ballot_list- The list we search in for the node
 * @param area_id - The id we are looking for
 * @return
 * If found, return BALLOT_FOUND
 * else, BALLOT_DOES_NOT_EXIST
 *
 * */
BallotNodeResult ballotNodeSearchAndDestroy(BallotNode ballot_list,int area_id);

/**
 * ballotNodeAddTribe- Adds a tribe to each ballot in the list(update the map to contain it)
 * @param ballot_list- The list we update each of its elements tribe_votes map
 * @param tribe_id- The id of the tribe we add
 * @return
 *  MAP_SUCCUESS if all the adds were successful
 * if an error accord while updating the map in one of the ballots returns one of these accordingly:
 *    {MAP_OUT_OF_MEMORY, 
 *    MAP_NULL_ARGUMENT,
 *    MAP_ITEM_ALREADY_EXISTS,
 *    MAP_ITEM_DOES_NOT_EXIST,
 *     MAP_ERROR}
 **/
 MapResult ballotNodeAddTribe(BallotNode ballot_list,int tribe_id);

 /**
  * ballotNodeRemoveTribe - removes a given tribe from all the ballots
  * 
  * 
  * 
  * 
  * */
 MapResult ballotNodeRemoveTribe(BallotNode ballot_list,int tribe_id);

//adds a vote to a specified tribe
void ballotNodeAddVote(BallotNode ballot, int tribe_id,int num_of_votes);

// removes the requested number of votes from the specified tribe.
void ballotNodeRemoveVote (BallotNode ballot,int area_id, int tribe_id, int num_of_votes);

char* getMaxTribe(BallotNode ballot);



#endif BALLOT_H_