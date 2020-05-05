#include "include/map.h"
#include "include/election.h"
#include "include/AreaNode.h"
#include "include/area.h"
#include "include/string_utils.h"
#include <string.h>
#include <stdlib.h>

#include <stdio.h>

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

/*
#define CHECK_AND_CRASH(election,element,pointers_to_free)\
CHECK_NULL_CRASH(election,element);\
free_pointers(pointers_to_free);\
CRASH(election);\
(void)(0)
*/


struct election_t {
    Map tribe_id_to_name;

    //A list of areas, points to a dummy node holding the list
    AreaNode areas;
};

/**
 * Static functions declerations
 * */
//gets an array of pointers and its size, frees all of them
void free_pointers(void* pointers_to_free[],int size){
    for(int i=0;i<size;i++){
        free(pointers_to_free[i]);
    }
}


Election electionCreate() {
    Election new_election = malloc(sizeof(*new_election));
    CHECK_NULL(new_election);

    new_election->tribe_id_to_name = mapCreate();
    CHECK_NULL(new_election->tribe_id_to_name);

    //intilizing dummy to hold the list of areas
    new_election->areas = areaNodeCreate(-1,"dummy holder");

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
    if (argumentValid != ELECTION_SUCCESS) {
        return argumentValid;
    }

    char *key = intToString(tribe_id);
    CHECK_NULL_CRASH(election, key);

    if (mapContains(election->tribe_id_to_name, key)) {
        free(key);
        return ELECTION_TRIBE_ALREADY_EXIST;
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
    if (argumentValid != ELECTION_SUCCESS) {
        return argumentValid;
    }

    if (areaNodeFindById(election->areas, area_id)) {
        return ELECTION_AREA_ALREADY_EXIST;
    }

    AreaNode new_areas = areaNodeAdd(areaNodeGetNext(election->areas), area_id, area_name);
    CHECK_NULL_CRASH(election, new_areas);
    areaNodeSetNext(election->areas, new_areas);

    return ELECTION_SUCCESS;
}


char* electionGetTribeName(Election election, int tribe_id) {
    if (!election) {
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
    if (argumentValid != ELECTION_SUCCESS) {
        return argumentValid;
    }

    char *key = intToString(tribe_id);
    CHECK_NULL_CRASH(election, key);

    if (!mapContains(election->tribe_id_to_name, key)) {
        free(key);
        return ELECTION_TRIBE_NOT_EXIST;
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
 *      Election error codes according to a mishap
 * 
 * */
static ElectionResult electionAddRemoveVotes(Election election, int area_id, int tribe_id, int num_of_votes) {
    if (!election) {
        return ELECTION_NULL_ARGUMENT;
    }

    if (area_id < 0 || tribe_id < 0) {
        return ELECTION_INVALID_ID;
    }

    char *key = intToString(tribe_id);
    CHECK_NULL_CRASH(election, key);

    if (!mapContains(election->tribe_id_to_name, key)) {
        free(key);
        return ELECTION_TRIBE_NOT_EXIST;
    }

    free(key);

    if (!areaNodeFindById(areaNodeGetNext(election->areas), area_id)) {
        return ELECTION_AREA_NOT_EXIST;
    }

    areaNodeChangeVotes(areaNodeGetNext(election->areas),area_id,tribe_id,num_of_votes);

    return ELECTION_SUCCESS;

}

ElectionResult electionAddVote(Election election, int area_id, int tribe_id, int num_of_votes) {
    if (num_of_votes <= 0) {
        return ELECTION_INVALID_VOTES;
    }

    return electionAddRemoveVotes(election,area_id,tribe_id,num_of_votes);
}

ElectionResult electionRemoveVote(Election election, int area_id, int tribe_id, int num_of_votes){
    if (num_of_votes <= 0) {
        return ELECTION_INVALID_VOTES;
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
//#define MAX_MALLOCED_IN_FUNCTION 5
Map electionComputeAreasToTribesMapping (Election election){
    //void* malloced_items[MAX_MALLOCED_IN_FUNCTION];
    Map result_map = mapCreate();
    //malloced_items[0]=result_map;
    if(election) {
        if(mapGetSize(election->tribe_id_to_name)==0){
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
            
            if(!key){//maybe a macro which gets an array of pointers and frees it?
                mapDestroy(result_map);
                free(winning_tribe);
                free(min_tribe);
                return NULL;
            }
            if(stringToInt(winning_tribe)==-1){//no tribes at the area, putting the tribe with the lowest id(As guided by the FAQ)
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


