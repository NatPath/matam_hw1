#include "AreaNode.h"
#include "area.h"
#include "../../ex1/mtm_map/map.h"
#include <stdlib.h>
#include <stdio.h>
#include "../string_utilities/string_utils.h"

//a macro for checking null of a parameter and returning null if so
#define CHECK_NULL(parameter) \
if(!parameter) {\
    return NULL; \
}\
(void)0


struct AreaNode_t{
    Area area;
    AreaNode next;
};


AreaNode areaNodeCreate(int area_id,char* area_name){
    AreaNode new_node = malloc(sizeof(*new_node));
    CHECK_NULL(new_node);
    new_node->area=areaCreate(area_id,area_name);
    CHECK_NULL(new_node->area);
    new_node->next=NULL;
    return new_node;
}

AreaNode AreaNodeAdd(AreaNode previous,int area_id,char *area_name){
    AreaNode new_node=areaNodeCreate(area_id,area_name);
    new_node->next=previous;
    return new_node;
}


Area areaNodeGetArea(AreaNode node){
    return node->area;
}

AreaNode areaNodeGetNext(AreaNode area){
    CHECK_NULL(area);
    return area->next;
}



//destroys a single Node
static void areaNodeDestroySingle(AreaNode to_destroy){
    areaDestroy(to_destroy->area);
    free(to_destroy);
}

void areaNodeDestroy(AreaNode to_destroy){
    CHECK_NULL(to_destroy);
    while(to_destroy){
        AreaNode temp=to_destroy->next;
        areaNodeDestroySingle(to_destroy);
        to_destroy=temp;
    }
}
AreaNode areaNodeFind(AreaNode node,int area_id,AreaNode* previous){
    AreaNode previous_res=NULL;
    while(node){
        if(areaGetAreaId(areaNodeGetArea(node))==area_id){
            if(previous){
                *previous=previous_res;
            }
            return node;
        }
        if(previous){
            *previous=node;
        }
        node=node->next;
    }
    return NULL;
}

AreaNode areaNodeFindById(AreaNode area_list,int area_id){
    return areaNodeFind(area_list,area_id,NULL);
}

AreaNodeResult areaNodeSearchAndDestroy(AreaNode area_list,int area_id){
    AreaNode previous;
    AreaNode to_destroy= areaNodeFind(area_list,area_id,&previous);
    if (!to_destroy){
        return AREA_DOES_NOT_EXIST;
    }
    previous->next=to_destroy->next;
    areaNodeDestroySingle(to_destroy);
    return AREA_SUCCESS;
}

AreaNodeResult areaNodeChangeVotes(AreaNode Area_list,int area_id,int tribe_id,int votes_change){
    AreaNode area_to_change=areaNodeFindById(Area_list,area_id);
    if (!area_to_change){
        return AREA_DOES_NOT_EXIST;
    }
    MapResult res=areaChangeVote(areaNodeGetArea(area_to_change),tribe_id,votes_change){
    if (res!=MAP_SUCCESS){
        return AREA_MAP_ERROR;
    }
    return AREA_SUCCESS;
}

/*
*********************************************************************
*********************** FUNCTIONS GRAVEYARD *************************
***************************** R I P *********************************
*********************** MAY THEY NEVER RISE *************************
*********************************************************************

******************************************
*** OLD GET FUNCTIONS, BEFORE THE SPLIT***
********* 14/4/2020 - 15/4/2020 **********
******************************************
Area areaNodeGetNext(AreaNode node){
    return node->next;
}

int AreaNodeGetAreaId(AreaNode Area){
    return Area->area_id;
}

Map AreaNodeGetTribeVotes(AreaNode Area){
    CHECK_NULL(Area);
    return Area->tribe_votes;
}


**************************************************
*** OLD FUNCTIONS, FUNCTIONALITY MOVED TO AREA ***
************* 14/4/2020 - 15/4/2020 **************
**************************************************

MapResult areaNodeChangeVotesSingle(AreaNode Area,int tribe_id, int votes_change){
    assert(Area);
    Map map=Area->tribe_votes;
    char* tribe_id_string=intToString(Area->tribe_id);
    char* tribe_votes_string=mapGet(map,tribe_id_string);
    assert(tribe_votes_string);
    int tribe_votes_int=stringToInt(tribe_votes_string);
    int sum=tribe_votes_int+votes_change;
    sum=sum<0?0:sum;//handles removing also
    char* sum=intToString(sum);
    return mapPut(map, area_id_string,sum);
}

*********************************************
*** TRIBE SYNCH FUNCTIONS, NOT NEEDED (?) ***
******** 14/4/2020 - 15/4/2020 **************
*********************************************

static MapResult AreaNodeAddTribeSingle(AreaNode Area,int tribe_id){
    char* id_as_string=intToString(tribe_id);
    assert(!mapContains(Area->tribe_votes,id_as_string));
    return mapPut(Area->tribe_votes,id_as_string,"0");
}

MapResult AreaNodeAddTribe(AreaNode Area_list,int tribe_id){
    while(Area_list){
        MapResult res=AreaNodeAddTribeSingle(Area_list,tribe_id);
        if (res!=MAP_SUCCESS){
            return res;
        }
        Area_list=Area_list->next;
    }
    return MAP_SUCCESS;
}

//code duplication... should be solved somehow later...
static MapResult AreaNodeAddTribeSingle(AreaNode Area,int tribe_id){
MapResult AreaNodeRemoveTribe(AreaNode Area_list,int tribe_id){
    while(Area_list){
        MapResult res=AreaNodeRemoveTribeSingle(Area_list,tribe_id);
        if (res!=MAP_SUCCESS){
            return res;
        }
        Area_list=Area_list->next;
    }
    return MAP_SUCCESS;
}

*/