
struct election_t{
    Map tribe_id_to_name;
    Map area_id_to_name;
    Ballot ballots[];


};
struct ballot_t{
    int area_id;
    Map tribe_votes;//
} *Ballot ;
//creates a ballot, inits an empty map for it.
Ballot createBallot(int area_id);

//adds a vote to a specified tribe
void ballotAddVote(Ballot ballot, int tribe_id,int num_of_votes);


// removes the requested number of votes from the specified tribe.
void ballotRemoveVote (Ballot ballot, int tribe_id, int num_of_votes);

*char getMaxTribe(Ballot ballot);

