#include "../include/area.h"
#include <string.h>
#include "../include/map.h"
#include "../include/string_utils.h"
#include <assert.h>
#include <stdlib.h>

#include <stdio.h>

#define CHECK_NULL(parameter) \
if(!parameter) {\
    return NULL; \
}\
(void)0

struct area_t{
    int id;
    char* name;
    Map ballot;
};

//debug functions

void areaPrint(Area area){
    printf("Printing area details:\n");
    printf("area name: %s\n", area->name);
    printf("area id is %d\n",area->id);
    //printf("ballot is ",area->ballot);
    
}

//

Area areaCreate(int id,const char *name){
    Area new_area = malloc(sizeof(*new_area));
    CHECK_NULL(new_area);
    new_area->id = id;
    new_area->name=initializeAndCopy(new_area->name,name);
    new_area->ballot=mapCreate();
    CHECK_NULL(new_area->ballot);
    return new_area;
}

void areaDestroy(Area to_destroy){
    mapDestroy(to_destroy->ballot);
    free(to_destroy->name);
    free(to_destroy);
}

int areaGetAreaId(Area area){
    return area->id;
}

char* areaGetName(Area area){
    CHECK_NULL(area);
    return area->name;
}

Map areaGetBallot(Area area){
    CHECK_NULL(area);
    return area->ballot;
}

MapResult areaChangeVotes(Area area,int tribe_id, int votes_change){
    assert(area);

    Map map=area->ballot;
    char* tribe_id_string=intToString(tribe_id);

    char* tribe_votes_string=mapGet(map,tribe_id_string);//NULL is fine
    int tribe_votes_int=stringToInt(tribe_votes_string);

    int sum=tribe_votes_int+votes_change;
    sum=sum<0?0:sum;//handles removing also
    char* sum_string=intToString(sum);

    MapResult result =  mapPut(map, tribe_id_string,sum_string);
    free(tribe_id_string);
    free(sum_string);
    return result; 
}

void areaRemoveTribe(Area area, char *tribe_id){
  mapRemove(areaGetBallot(area),tribe_id);
}

/**
 * findMaxVotes: Returns the number of tribes with the highest number of votes
 * @param map- The map we search in
 * @param winners- An array of strings, already allocated, which will hold the id(as string) of the winning tribes
 * @return
 *      The number of tribes with the highest vote count yet.
 * */
static int findMaxVotes(Map map,char **winners){
    int max=0;
    int winner_count=0;
    MAP_FOREACH(tribe,map){
        char* num_string= mapGet(map,tribe);
        int num=stringToInt(num_string);
        if(num>=max){
            if (num>max){
                winner_count=0;
            }
            winners[winner_count]=tribe;
            winner_count++;
            max=num;
        }
    }
    
    return winner_count;
}

/**
 * areaGetWinningTribe: Returns the id of the tribe with the most votes (and the smallest id) in the area.
 * @param area- The area we search the ballot of
 * @return 
 *      The id of the winning tribe as a string
 * */
char* areaGetWinningTribe(Area area){
    Map map=area->ballot;
    int map_size=mapGetSize(map);

    if (map_size==0){ // if there are no votes to any tribe in the area
        return intToString(-1);
    }
    char** winners=malloc(sizeof(*winners)*map_size);
    CHECK_NULL(winners);
    int winner_count=findMaxVotes(map,winners);

    //checks for lowest id between winners
    int min= stringToInt(winners[0]);

    for(int i=0;i<winner_count;i++){
        int current_id=stringToInt(winners[i]);
        min=current_id<min?current_id:min;
    }
    
    free(winners);
    return intToString(min);

}

/*
DEBUG FUNCTIONS
*/






