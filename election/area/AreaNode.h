#ifndef AREA_NODE_H_
#define AREA_NODE_H_
#include "map.h"
#include "area.h"

typedef struct AreaNode_t *AreaNode ;

typedef enum areaNodeResult_t{
    AREA_SUCCESS,
    AREA_DOES_NOT_EXIST,
    AREA_MAP_ERROR
} AreaNodeResult;

/**
 * areaNodeCreate: Creates a node for an area with given id and name properties 
 * @param area_id - the id we want for the area
 * @param area_name- the name we want for the area
 * 
 * 
 * */
AreaNode areaNodeCreate(int area_id,char* area_name);

/** areaNodeAdd: Creates a new node and connects it in the beginning of the node_list given.
 * @param node_list - The nodes to which we connect the new node
 * @param area_id - Same as areaNodeCreate
 * @param area_name - Same as areaNodeCreate
 * 
 * @return 
 *        The node created
 *        NULL if a memory error has accured somewhere #FISHY
 * */
AreaNode areaNodeAdd(AreaNode node_list,int area_id,char *area_name);

/**
 * areaNodeGetNext: returns the next node in the list
 * @param node - A node
 * @return 
 *    The next node, if NULL so be it
 * */
AreaNode areaNodeGetNext(AreaNode node);

/**
 * areaNodeGetNext: returns area field of a given node  
 * @param node - a node
 * @return 
 *      The area the node represents
 * */
Area areaNodeGetArea(AreaNode node){


/**
 * areaNodeDestroy: gets a list, iterate through it and frees its memory
 * @param to_destroy - The begining of the list we want to destory
**/
void areaNodeDestroy(AreaNode to_destroy);

/**
* areaNodeFind: returns a node with the given id it exists, returns NULL otherwise
* @param areaNode - The first Node in the list
* @param area_id - The id to look for
* @param previous - a pointer of areaNode, which will point to the element before the one we look for if found
*               if not found, will contain NULL
*               if you're not intrested in the previous, send as NULL
* @return 
* if found, The searched areaNode with the given area_id
* NULL, if not found
**/
AreaNode areaNodeFind(AreaNode area_list,int area_id,AreaNode* previous);

/**
 * areaNodeFindById : same as areNodeFind, but doesn't care for the "previous" arguement
 * @param areaNode - The first Node in the list
 * @param area_id - The id to look for
 * @return 
 * if found, The searched areaNode with the given area_id
 * NULL, if not found
 * */
AreaNode areaNodeFindById(AreaNode area_list,int area_id);

/**
 * areaNodeSearchAndDestroy: searches for a node with a given area_id, if it exists, remove it from the List
 * @param area_list- The list we search in for the node
 * @param area_id - The id we are looking for
 * @return
 * If found, return area_FOUND
 * else, area_DOES_NOT_EXIST
 *
 * */
AreaNodeResult areaNodeSearchAndDestroy(AreaNode area_list,int area_id);


/**
 * areNodeChangeVotes: change the vote count in a given area
 * @param area_list- The list we search in for the AreaNode
 * @param area_id- The id indecating which node we want to change
 * @param tribe_id- The tribe which we want to change the votes of
 * @param num_of_votes- The number of votes we want to add(can be negative)
 * */
void areaNodeChangeVotes(AreaNode area_list,int area_id, int tribe_id, int num_of_votes);



#endif AREA_H_
