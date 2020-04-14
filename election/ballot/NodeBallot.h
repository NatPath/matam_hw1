#ifndef NODEBALLOT_H_
#define NODEBALLOT_H_


struct ballot_t{
    int area_id;
    Map tribe_votes;//
} *NodeBallot ;

//creates a ballot, inits an empty map for it.
NodeBallot nodeBallotCreate(int area_id);

//destroy a ballot, frees its memory
void nodeBallotDestroy(NodeBallot to_destroy);

//adds a vote to a specified tribe
void nodeBallotAddVote(NodeBallot ballot, int tribe_id,int num_of_votes);

// removes the requested number of votes from the specified tribe.
void nodeBallotRemoveVote (NodeBallot ballot, int tribe_id, int num_of_votes);

char* getMaxTribe(NodeBallot ballot);



#endif BALLOT_H_