#include "include/map.h"
#include "include/election.h"
#include "include/AreaNode.h"
#include "include/area.h"
#include "include/string_utils.h"
#include <string.h>
#include <stdlib.h>

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

    new_election->areas = NULL;

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
        return ELECTION_TRIBE_ALREADY_EXIST;
    }

    if (mapPut(election->tribe_id_to_name, key, tribe_name) == MAP_OUT_OF_MEMORY) {
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

    AreaNode new_areas = areaNodeAdd(election->areas, area_id, area_name);
    CHECK_NULL_CRASH(election, new_areas);
    election->areas = new_areas;

    return ELECTION_SUCCESS;
}


   char* electionGetTribeName(Election election, int tribe_id) {
    if (!election || !tribe_id) {
        return NULL;
    }
    char *key = intToString(tribe_id);
    CHECK_NULL_CRASH(election, key);
    const char *name = mapGet(election->tribe_id_to_name, key);
    free(key);

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
        return ELECTION_TRIBE_NOT_EXIST;
    }

    if (mapPut(election->tribe_id_to_name, key, tribe_name) == MAP_OUT_OF_MEMORY) {
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
        return ELECTION_TRIBE_NOT_EXIST;
    }

    return ELECTION_SUCCESS;
}

ElectionResult electionRemoveAreas(Election election, AreaConditionFunction should_delete_area) {
    if (!election || !should_delete_area) {
        return ELECTION_NULL_ARGUMENT;
    }

    AreaNode iterator = election->areas;
    Area area;
    int area_id;
    while (iterator) {
        area = areaNodeGetArea(iterator);
        area_id = areaGetAreaId(area);
        if (should_delete_area(area_id)) {
            areaNodeSearchAndDestroy(election->areas,area_id);
        }
        iterator = areaNodeGetNext(iterator);
    }

    return ELECTION_SUCCESS;
}
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
        return ELECTION_TRIBE_NOT_EXIST;
    }
    free(key);

    if (!areaNodeFindById(election->areas, area_id)) {
        return ELECTION_AREA_NOT_EXIST;
    }

    areaNodeChangeVotes(election->areas,area_id,tribe_id,num_of_votes);

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




Map electionComputeAreasToTribesMapping (Election election){
    Map result_map = mapCreate();
    if(election) {
        AreaNode iterator = election->areas;
        int area_id;
        char *winning_tribe;
        Area area;
        MapResult put_result;
        while (iterator) {
            area = areaNodeGetArea(iterator);
            area_id = areaGetAreaId(area);
            winning_tribe = areaGetWinningTribe(area);
            char *key = intToString(area_id);
            CHECK_NULL(key);
            put_result = mapPut(result_map, key, winning_tribe);
            free(key);
            if ( put_result == MAP_OUT_OF_MEMORY) {
                return NULL;
            }
            iterator = areaNodeGetNext(iterator);
        }
    }

    return result_map;
}


