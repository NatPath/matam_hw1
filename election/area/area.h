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
Area areaCreate(int area_id,char* area_name);

/**
 * areaDestroy: free all allocated memory of given Area
 * @param to_destroy
 * 
 * */
void areaDestroy(Area to_destroy);

/**
 * areaGetAreaId: returns area_id field
 * @param area
 * 
 * */
int areaGetAreaId(Area area);
 
/**
 * areaGetAreaName: returns area_name field
 * @param area
 * */
char* areaGetName(Area area);

/**
 * areaGetAreaName: returns area_field
 * @param area
 * */
Map areaGetBallot(Area area);

/**
 * areaChangeVote: change number of votes of a given tribe in the area
 * @param area- The area we work on
 * @param tribe_id- id of the tribe we want to change the votes of
 * @param vote_change- how many votes to add(negative number is possible)
 * */
MapResult areaChangeVote(Area area,int tribe_id,int vote_change);


/**
 * areaGetWinningTribe: return the tribe with the most votes according to ballot
 * @param area
 * @return 
 *      The id of the tribe with most votes as string
 * */
char* areaGetWinningTribe(Area area);






#endif