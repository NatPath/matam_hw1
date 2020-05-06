#include "AreaNode.h"
#include "area.h"
#include "map.h"
#include <stdlib.h>

#include <assert.h>

#include <stdio.h>


//a macro for checking null of a parameter and returning null if so
#define CHECK_NULL(parameter) \
if(!parameter) {\
    return NULL; \
}\
(void)0

struct AreaNode_t{
    Area area;
    struct AreaNode_t *next;
};



AreaNode areaNodeCreate(int area_id,const char* area_name){
    AreaNode new_node = malloc(sizeof(*new_node));
    CHECK_NULL(new_node);
    new_node->area=areaCreate(area_id,area_name);
    CHECK_NULL(new_node->area);
    new_node->next=NULL;
    return new_node;
}

AreaNode areaNodeAdd(AreaNode previous,int area_id,const char *area_name){
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
void areaNodeSetNext(AreaNode node,AreaNode next){
    node->next=next;
}



//destroys a single Node
static void areaNodeDestroySingle(AreaNode to_destroy){
    assert(to_destroy->area);
    areaDestroy(to_destroy->area);
    free(to_destroy);
}

void areaNodeDestroy(AreaNode to_destroy){
    while(to_destroy){
        AreaNode temp=to_destroy->next;
        areaNodeDestroySingle(to_destroy);
        to_destroy=temp;
    }
}

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
static AreaNode areaNodeFind(AreaNode node,int area_id,AreaNode* previous){
    AreaNode previous_res=NULL;
    while(node){
        if(areaGetAreaId(areaNodeGetArea(node))==area_id){
            if(previous){
                *previous=previous_res;
            }
            return node;
        }
        previous_res=node;
        node=node->next;
    }
    return NULL;
}

AreaNode areaNodeFindById(AreaNode area_list,int area_id){
    return areaNodeFind(area_list,area_id,NULL);
}

AreaNodeResult areaNodeSearchAndDestroy(AreaNode area_list,int area_id){
    AreaNode previous;//will hold the value of the previous node to the one found
    AreaNode to_destroy= areaNodeFind(area_list->next,area_id,&previous);
    if (!to_destroy){
        return AREA_DOES_NOT_EXIST;
    }
    if (previous){
        previous->next=to_destroy->next;
    }
    else{//previous can be NULL if the node searched is the first in the list(without the dummy)
        area_list->next=to_destroy->next;
    }
    areaNodeDestroySingle(to_destroy);
    return AREA_NODE_SUCCESS;
}