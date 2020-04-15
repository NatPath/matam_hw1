#include "election.h"
#include "map.h"
#include <string.h>

#define CRASH(election) electionDestroy(election);\
return ELECTION_OUT_OF_MEMORY; (void)0

//checks whether the given element is null and returns null if it is.
#define CHECK_NULL(element) if(!element){return NULL;} (void)0
//checks whether the given element is null. 
//releases resources and return appropriate result if it is.
#define CHECK_NULL_CRASH(election,element) \
if(!element){\
  CRASH(election)\
} (void)(0)

struct election_t{
    Map tribe_id_to_name;
    Map area_id_to_name;
    BallotNode ballots;
};

//signals whether we want to use the tribe or area for their similiar functions
typedef enum TribeOrArea_t {
    USE_TRIBE,
    USE_AREA
}  TribeOrArea;



Election electionCreate(){
    Election new_election= malloc(sizeof(*new_election));
    CHECK_NULL(new_election);
    
    new_election->tribe_id_to_name=mapCreate();
    CHECK_NULL(new_election->tribe_id_to_name);

    new_election->area_id_to_name=mapCreate();
    CHECK_NULL(new_election->area_id_to_name);

    new_election->ballots=ballotNodeCreate();
    CHECK_NULL(new_election->ballots);

    return new_election;
}

void electionDestroy(Election election){
    if(!election){
        return;
    }
    mapDestroy(election->tribe_id_to_name);
    mapDestroy(election->area_id_to_name);
    ballotNodeDestroy(election->ballots);
    free(election);
}

ElectionResult electionAddTribe (Election election, int tribe_id, const char* tribe_name){
     return electionAddToMap(election,tribe_id,tribe_name,USE_TRIBE);
}

ElectionResult electionAddArea(Election election, int area_id, const char* area_name){
    return electionAddToMap(election,area_id,area_name,USE_AREA);
}

static ElectionResult electionAddToMap(Election election, int id, const char* name,TribeOrArea use_case){
    if(!election || !name){
        return ELECTION_NULL_ARGUMENT;
    }
    if(id < 0){
        return ELECTION_INVALID_ID;
    }

    if(!lowerCaseAndSpacesOnly(name))){
        return ELECTION_INVALID_NAME;
    }

    char *key = intToString(id);
    CHECK_NULL_CRASH(election,key);
    MapResult put_result;
    if(use_case == USE_TRIBE){
        if(mapContains(election->tribe_id_to_name,key)){
            return ELECTION_TRIBE_ALREADY_EXIST;
        }
        put_result = mapPut(election->tribe_id_to_name,key,name);
        //update BallotNode is needed
    }
    else
    {
        if(mapContains(election->area_id_to_name,key)){
            return ELECTION_AREA_ALREADY_EXIST;
        }
        put_result = mapPut(election->area_id_to_name,key,name);
        //update BallotNode is needed
    }
    
    if(put_result == MAP_OUT_OF_MEMORY){
        CRASH(election);
    }
    free(key);
    return ELECTION_SUCCESS;
}

const char* electionGetTribeName (Election election, int tribe_id){
    if(!election || !tribe_id){
        return NULL;
    }
    char *key = intToString(id);
    CHECK_NULL_CRASH(election,key);
    const char* name =  mapGet(election->tribe_id_to_name,key);
    free(key);
    return name;
}

ElectionResult electionSetTribeName (Election election, int tribe_id, const char* tribe_name){
     if(!election || !tribe_name){
         return ELECTION_NULL_ARGUMENT;
     } 

     if(tribe_id <0){
         return ELECTION_INVALID_ID;
     }

     if(!mapContains(map,key)){
            return ELECTION_TRIBE_NOT_EXIST;
     }
     
     if(!lowercaseAndSpacesOnly(tribe_name))){
        return ELECTION_INVALID_NAME;
    }
    
    
     char *key = intToString(id);
     CHECK_NULL_CRASH(election,key);
     if(mapPut(election->tribe_id_to_name,key,tribe_name) == MAP_OUT_OF_MEMORY){
         CRASH(election);
     }

     free(key);
     return ELECTION_SUCCESS;
}

ElectionResult electionAddVote (Election election, int area_id, int tribe_id, int num_of_votes){
    if(!election){
        return ELECTION_NULL_ARGUMENT;
    }
    electionGetTribeName(election,tribe_id);
    
}
