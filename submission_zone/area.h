#ifndef AREA_H_
#define AREA_H_
#include "map.h"

typedef struct area_t *Area;

/**
 * areaCreate: Creates an area with given parameters and returns it
 * @param area_id
 * @param area_name
 * @return
 *      The area created
 *      NULL if an error accured
 * 
 * */
Area areaCreate(int area_id,const char* area_name);

/**
 * areaDestroy: Free all allocated memory of given Area
 * @param to_destroy - The Area we want to destroy
 * 
 * */
void areaDestroy(Area to_destroy);

/**
 * areaGetAreaId: returns area_id field
 * @param area - The area to get the id of
 * @return 
 *      The id of the area given
 * 
 * */
int areaGetAreaId(Area area);
 
/**
 * areaGetAreaName: returns area_name field
 * @param area - Get name of this given area 
 * @return 
 *      The name of an area as a string(an actual reference to it, not a copy)
 * */
char* areaGetName(Area area);

/**
 * areaGetAreaName: returns the map of the votes in the area,  
 * @param area - Get the ballot from this area
 * @return 
 *      a Map which details how many votes in the area each tribe has
 * */
Map areaGetBallot(Area area);

/**
 * areaChangeVote: change number of votes of a given tribe in the area
 * @param area- The area to change the vote count in
 * @param tribe_id- id of the tribe we want to change the votes of
 * @param vote_change- how many votes to add(negative number is possible)
 * */
MapResult areaChangeVotes(Area area,int tribe_id,int vote_change);


/**
 * areaGetWinningTribe: return the tribe with the most votes according to ballot
 * @param area - Return winning tribe of this area
 * @return 
 *      The id of the tribe with most votes as a string.
 *      If the area has no tribes, returns -1 as a string,\
 *      indicating there are no votes to any tribe in the area.
 * */
char* areaGetWinningTribe(Area area);
/**
 * areaRemoveTribe: removes tribe with given id from the ballot of area
 * @param area - The area we update the ballot of
 * @param tribe_id- the id of the tribe we are removing from the ballot
 * 
 * */

void areaRemoveTribe(Area area, char *tribe_id);






#endif