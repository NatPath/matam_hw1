#include "NodeBallot.h"
#include "map.h"

NodeBallot nodeBallotCreate(int area_id){
    NodeBallot new_ballot = malloc(sizeof(*new_ballot));
    if(!new_ballot){
        return NULL;
    }
    new_ballot->area_id = area_id;
    new_ballot->tribe_votes = mapCreate();
}

void nodeBallotDestroy(NodeBallot to_destroy){
    mapDestroy(to_destroy->tribe_votes);
    free(to_destroy);
}
