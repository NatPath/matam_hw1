#include "BallotNode.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include "../string_utilities/string_utils.h"

//a macro for checking null of a parameter and returning null if so
#define CHECK_NULL(parameter) \
if(!parameter) {\
    return NULL; \
}\
(void)0


struct ballot_t{
    int area_id;
    Map tribe_votes;
    struct ballot_t *next;
}


BallotNode ballotNodeCreate(int area_id){
    BallotNode new_ballot = malloc(sizeof(*new_ballot));
    CHECK_NULL(new_ballot);
    new_ballot->area_id = area_id;
    new_ballot->tribe_votes = mapCreate();
    new_ballot->next=NULL;
    return new_ballot;
}

int ballotNodeGetAreaId(BallotNode ballot){
    return ballot->area_id;
}

Map ballotNodeGetTribeVotes(BallotNode ballot){
    CHECK_NULL(ballot);
    return ballot->tribe_votes;
}

BallotNode ballotNodeGetNext(BallotNode ballot){
    CHECK_NULL(ballot);
    return ballot->next;
}

BallotNode ballotNodeFind(BallotNode ballot,int area_id,BallotNode* previous){
    BattleNode previous_res=NULL;
    while(ballot){
        if(ballot->area_id==area_id){
            if(previous){
                *previous=previous_res;
            }
            return ballot;
        }
        if(previous){
            *previous=ballot;
        }
        ballot=ballot->next;
    }
    return NULL;
}

BallotNodeResult ballotNodeSearchAndDestroy(BallotNode ballot_list,int area_id){
    BallotNode previous;
    BallotNode to_destroy= ballotNodeFind(ballot_list,area_id,&previous);
    if (!to_destroy){
        return BALLOT_DOES_NOT_EXIST;
    }
    previous->next=to_destroy->next;
    ballotNodeDestroySingle(to_destroy);
    return BALLOT_SUCCESS;
    
}

//destroys a single Node
static void ballotNodeDestroySingle(BallotNode to_destroy){
    CHECK_NULL(to_destroy);
    mapDestroy(to_destroy->tribe_votes);
    free(to_destroy);
}

void ballotNodeDestroy(BallotNode to_destroy){
    CHECK_NULL(to_destroy);
    while(to_destroy){
        BallotNode temp=to_destroy->next;
        ballotNodeDestroySingle(to_destroy);
        to_destroy=temp;
    }
}

static MapResult ballotNodeAddTribeSingle(BallotNode ballot,int tribe_id){
    char* id_as_string=intToString(tribe_id);
    assert(!mapContains(ballot->tribe_votes,id_as_string));
    return mapPut(ballot->tribe_votes,id_as_string,"0");
}

MapResult ballotNodeAddTribe(BallotNode ballot_list,int tribe_id){
    while(ballot_list){
        MapResult res=ballotNodeAddTribeSingle(ballot_list,tribe_id);
        if (res!=MAP_SUCCESS){
            return res;
        }
        ballot_list=ballot_list->next;
    }
    return MAP_SUCCESS;
}

//code duplication... should be solved somehow later...
static MapResult ballotNodeAddTribeSingle(BallotNode ballot,int tribe_id){
MapResult ballotNodeRemoveTribe(BallotNode ballot_list,int tribe_id){
    while(ballot_list){
        MapResult res=ballotNodeRemoveTribeSingle(ballot_list,tribe_id);
        if (res!=MAP_SUCCESS){
            return res;
        }
        ballot_list=ballot_list->next;
    }
    return MAP_SUCCESS;
}

MapResult ballotNodeChangeVotesSingle(BallotNode ballot,int tribe_id, int votes_change){
    assert(ballot);
    Map map=ballot->tribe_votes;
    char* tribe_id_string=intToString(ballot->tribe_id);
    char* tribe_votes_string=mapGet(map,tribe_id_string);
    assert(tribe_votes_string);
    int tribe_votes_int=stringToInt(tribe_votes_string);
    int sum=tribe_votes_int+votes_change;
    sum=sum<0?0:sum;//handles removing also
    char* sum=intToString(sum);
    return mapPut(map, area_id_string,sum);
}

BallotNodeResult ballotNodeChangeVotes(BallotNode ballot_list,int area_id,int tribe_id,int votes_change){
    BallotNode ballot_to_change=ballotNodeFind(ballot_list,area_id,NULL);
    if (!ballot_to_change){
        return BALLOT_DOES_NOT_EXIST;
    }
    MapResult res=ballotNodeAddVoteSingle(ballot_to_change,tribe_id,votes_change){
    if (res!=MAP_SUCCESS){
        return BALLOT_MAP_ERROR;
    }
    return BALLOT_SUCCESS;
}

//to_do - make an iterator maybe? idk..
