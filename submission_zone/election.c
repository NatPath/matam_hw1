#include "mtm_map/map.h"
#include "election.h"
#include "AreaNode.h"
#include "area.h"
#include "string_utils.h"
#include <string.h>
#include <stdlib.h>

#include <stdio.h>

#define DUMMY_HEAD -1
#define CRASH(election) electionDestroy(election);\
return ELECTION_OUT_OF_MEMORY; (void)0

//checks whether the given element is null and returns null if it is.
#define CHECK_NULL(element) if(!element){return NULL;} (void)0

//checks whether the given element is null. 
//releases resources and return appropriate result if it is.
#define CHECK_NULL_CRASH(election, element) \
if(!element){\
  CRASH(election);\
} (void)(0)



struct election_t {
    Map tribe_id_to_name;
    AreaNode areas;
};

Election electionCreate() {
    Election new_election = malloc(sizeof(*new_election));
    CHECK_NULL(new_election);

    new_election->tribe_id_to_name = mapCreate();
    CHECK_NULL(new_election->tribe_id_to_name);

    //intilizing dummy to hold the list of areas
    new_election->areas = areaNodeCreate(DUMMY_HEAD,"dummy head");

    return new_election;
}

void electionDestroy(Election election) {
    if (!election) {
        return;
    }
    mapDestroy(election->tribe_id_to_name);
    areaNodeDestroy(election->areas);
    free(election);
}

//checks for validity of arguments, legal id and name of a new tribe and that election is not NULL
static ElectionResult electionCheckIdentifierArgs(Election election, int id, const char *name) {

    if (!election || !name) {
        return ELECTION_NULL_ARGUMENT;
    }
    if (id < 0) {
        return ELECTION_INVALID_ID;
    }

    if (!lowerCaseAndSpacesOnly(name)){
        return ELECTION_INVALID_NAME;
    }

    return ELECTION_SUCCESS;
}

ElectionResult electionAddTribe(Election election, int tribe_id, const char *tribe_name) {
    ElectionResult argumentValid = electionCheckIdentifierArgs(election, tribe_id, tribe_name);


    if (argumentValid != ELECTION_SUCCESS && argumentValid != ELECTION_INVALID_NAME) {
        return argumentValid;
    }

    char *key = intToString(tribe_id);
    CHECK_NULL_CRASH(election, key);

    if (mapContains(election->tribe_id_to_name,key)) {// Reordered return values in case of failures 
        free(key);
        return ELECTION_TRIBE_ALREADY_EXIST;
    }

    if(argumentValid==ELECTION_INVALID_NAME){
        free(key);
        return argumentValid;
    }

    if (mapPut(election->tribe_id_to_name, key, tribe_name) == MAP_OUT_OF_MEMORY) {
        free(key);
        CRASH(election);
    }
    free(key);
    return ELECTION_SUCCESS;
}

ElectionResult electionAddArea(Election election, int area_id, const char *area_name) {
    ElectionResult argumentValid = electionCheckIdentifierArgs(election, area_id, area_name);
    if (argumentValid != ELECTION_SUCCESS && argumentValid != ELECTION_INVALID_NAME) {
        return argumentValid;
    }

    if (areaNodeFindById(election->areas, area_id)) {
        return ELECTION_AREA_ALREADY_EXIST;
    }

    if (argumentValid == ELECTION_INVALID_NAME){// Reordered return values in case of failures 
        return argumentValid;
    }

    AreaNode new_areas = areaNodeAdd(areaNodeGetNext(election->areas), area_id, area_name);
    CHECK_NULL_CRASH(election, new_areas);
    areaNodeSetNext(election->areas, new_areas);

    return ELECTION_SUCCESS;
}


char* electionGetTribeName(Election election, int tribe_id) {
    if (!election || tribe_id<0) {
        return NULL;
    }
    char *key = intToString(tribe_id);

    CHECK_NULL_CRASH(election, key);
    const char *name = mapGet(election->tribe_id_to_name, key);

    free(key);
    CHECK_NULL(name);

    char* name_copy= "temp";
    name_copy = initializeAndCopy(name_copy,name);
    CHECK_NULL_CRASH(election,name_copy);
    return name_copy;
}

ElectionResult electionSetTribeName(Election election, int tribe_id, const char *tribe_name) {
    ElectionResult argumentValid = electionCheckIdentifierArgs(election, tribe_id, tribe_name);
    if (argumentValid != ELECTION_SUCCESS && argumentValid != ELECTION_INVALID_NAME) {
        return argumentValid;
    }

    char *key = intToString(tribe_id);
    CHECK_NULL_CRASH(election, key);

    if (!mapContains(election->tribe_id_to_name, key)) {
        free(key);
        return ELECTION_TRIBE_NOT_EXIST;
    }

    if (argumentValid == ELECTION_INVALID_NAME){ // Reordered return values in case of failures 
        free(key);
        return argumentValid;
    }

    if (mapPut(election->tribe_id_to_name, key, tribe_name) == MAP_OUT_OF_MEMORY) {
        free(key);
        CRASH(election);
    }

    free(key);
    return ELECTION_SUCCESS;
}

ElectionResult electionRemoveTribe(Election election, int tribe_id) {
    if (!election) {
        return ELECTION_NULL_ARGUMENT;
    }
    if (tribe_id < 0) {
        return ELECTION_INVALID_ID;
    }

    char *key = intToString(tribe_id);
    CHECK_NULL_CRASH(election, key);

    if (mapRemove(election->tribe_id_to_name, key) == MAP_ITEM_DOES_NOT_EXIST) {
        free(key);
        return ELECTION_TRIBE_NOT_EXIST;
    }

    AreaNode iterator = areaNodeGetNext(election->areas);
    Area area;
    while(iterator){
        area = areaNodeGetArea(iterator);
        areaRemoveTribe(area,key);
        iterator = areaNodeGetNext(iterator);
    }

    free(key);
    return ELECTION_SUCCESS;
}

ElectionResult electionRemoveAreas(Election election, AreaConditionFunction should_delete_area) {
    if (!election || !should_delete_area) {
        return ELECTION_NULL_ARGUMENT;
    }

    AreaNode iterator = areaNodeGetNext(election->areas);
    Area area;
    int area_id;
    while (iterator) {
        area = areaNodeGetArea(iterator);
        area_id = areaGetAreaId(area);
        iterator = areaNodeGetNext(iterator);
        if (should_delete_area(area_id)) {
            areaNodeSearchAndDestroy(election->areas,area_id);
        }
        
    }

    return ELECTION_SUCCESS;
}
/**
 * electionAddRemoveVotes: Changes the vote count of some tribe in a some area
 * @param election - The election
 * @param area_id - The area of the vote 
 * @param tribe_id - The tribe we change the votes of
 * @param num_of_votes - The difference in votes to be made ( can be either negative or positive)
 * @return 
 *      ELECTION_SUCCESS if vote is valid and went well
 *      Election error codes according to a mishap in memory allocation or area/tribe does not exists
 * 
 * */
static ElectionResult electionAddRemoveVotes(Election election, int area_id, int tribe_id, int num_of_votes) {

    char *key = intToString(tribe_id);
    CHECK_NULL_CRASH(election, key);

    AreaNode area_to_change=areaNodeFindById(election->areas,area_id);

    if (!area_to_change) {
        free(key);
        return ELECTION_AREA_NOT_EXIST;
    }

    if (!mapContains(election->tribe_id_to_name, key)) {
        free(key);
        return ELECTION_TRIBE_NOT_EXIST;
    }

    free(key);


    MapResult change_result=areaChangeVotes(areaNodeGetArea(area_to_change),tribe_id,num_of_votes);
    if(change_result!=MAP_SUCCESS){
        free(key);
        return ELECTION_OUT_OF_MEMORY;
    }

    return ELECTION_SUCCESS;

}

/**
 * electionAddRemoveVotesArgCheck: Check for invalid arguments to Add/Remove votes function
 * @param election - The election
 * @param area_id - The area of the vote 
 * @param tribe_id - The tribe we change the votes of
 * @param num_of_votes - The difference in votes to be made 
 * @return 
 *      Election error codes according to a mishap in argument values
 * 
 * */
static ElectionResult electionAddRemoveVoteArgCheck(Election election,int area_id,int tribe_id,int num_of_votes){
    if(election==NULL){
        return ELECTION_NULL_ARGUMENT;
    }
    if (area_id < 0 || tribe_id < 0) {
        return ELECTION_INVALID_ID;
    }
    if (num_of_votes <= 0) {
        return ELECTION_INVALID_VOTES;
    }
    return ELECTION_SUCCESS;

}
ElectionResult electionAddVote(Election election, int area_id, int tribe_id, int num_of_votes) {
    ElectionResult argCheck=electionAddRemoveVoteArgCheck(election,area_id,tribe_id,num_of_votes);
    if (argCheck != ELECTION_SUCCESS){
        return argCheck;
    }

    return electionAddRemoveVotes(election,area_id,tribe_id,num_of_votes);
}

ElectionResult electionRemoveVote(Election election, int area_id, int tribe_id, int num_of_votes){
    ElectionResult argCheck=electionAddRemoveVoteArgCheck(election,area_id,tribe_id,num_of_votes);
    if (argCheck != ELECTION_SUCCESS){
        return argCheck;
    }

    return electionAddRemoveVotes(election,area_id,tribe_id,num_of_votes * (-1));
}


/**
 * minTribe: return the id of the tribe with the lowest id
 * 
 * */
static int minTribe(Map tribes){
    int min=stringToInt(mapGetFirst(tribes));
    MAP_FOREACH(i,tribes){
        int iterator_id=stringToInt(i);
        min=min>iterator_id?iterator_id:min;
    }
    return min;
}

Map electionComputeAreasToTribesMapping (Election election){
    Map result_map = mapCreate();
    if(election) {
        if(mapGetSize(election->tribe_id_to_name)==0){//No tribes, the map should be empty
            return result_map;   
        }
        char *min_tribe=intToString(minTribe(election->tribe_id_to_name));

        AreaNode iterator = areaNodeGetNext(election->areas);
        int area_id;
        char *winning_tribe;
        Area area;
        MapResult put_result;
        while (iterator) {
            area = areaNodeGetArea(iterator);
            area_id = areaGetAreaId(area);
            winning_tribe = areaGetWinningTribe(area);
            char *key = intToString(area_id);
            
            if(!key){
                mapDestroy(result_map);
                free(winning_tribe);
                free(min_tribe);
                return NULL;
            }
            if(!winning_tribe){
                put_result =mapPut(result_map,key,min_tribe);
            }
            else{
                put_result = mapPut(result_map, key, winning_tribe);
            }
            free(key);
            free(winning_tribe);

            if ( put_result == MAP_OUT_OF_MEMORY) {
                mapDestroy(result_map);
                free(min_tribe);
                return NULL;
            }
            iterator = areaNodeGetNext(iterator);
        }
        free(min_tribe);
    }

    return result_map;
}


