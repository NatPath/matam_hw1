#include "map.h"
#include "pairnode.h"
#include "pair.h"
#include <string.h>
#include <stdlib.h>

#include <stdio.h>

#include <assert.h>

struct Map_t{
    PairNode head;
    PairNode iterator;
};

/**
 * Static Functions decleration
 * 
 * */
/**
 * mapFind: find the PairNode which holds the key given, 
 * 
 * @param map- The map we search in
 * @param key- The key we search for
 * @param previous-if sent an actual address and not "NULL" the pointer "previous" 
 *  will contain the Node before the searched Node if found.
 *  if the node found has no node before him (the head of the list), previous will be set to NULL.
 * 
 * @return
 *      The PairNode if found, NULL otherwise
 *  
 * */
static PairNode mapFind(Map map,const char* key,PairNode *previous);

//


Map mapCreate(){
    Map new_map=malloc(sizeof(*new_map));
    if(!new_map){
        return NULL;
    }
    new_map->head=NULL;
    new_map->iterator=NULL;
    return new_map;
}
void mapDestroy(Map map){
    mapClear(map);
    free(map);
}


Map mapCopy(Map map){
    if(!map){
        return NULL;
    }
    Map new_map=mapCreate();
    if(!new_map){
        return NULL;
    }
    PairNode head=copyPairNode(map->head);
    if (!head){
        return NULL;
    }
    new_map->head=head;
    return new_map;
}

int mapGetSize(Map map){
    if(!map){
        return -1;
    }
      
    int size = 0;
    PairNode *pointer=&(map->head);
    PairNode nextNode; 
    while(*pointer){
        size++;
        nextNode = getNextPairNode(*pointer);
        pointer = &nextNode;
    }
    return size;
}

bool mapContains(Map map, const char* key){
    return mapGet(map,key) != NULL;
}

//NEW
MapResult mapPut(Map map, const char* key,const char* data){
    
    if(!map || !key || !data)
    {
        return MAP_NULL_ARGUMENT;
    }
    PairNode existing_entry = mapFind(map,key,NULL);
    if (!existing_entry){
        Pair new_pair=createPair(key,data);
        PairNode new_head=createPairNode(new_pair);
        if (!new_head){
            return MAP_OUT_OF_MEMORY;
        }
        setNextPairNode(new_head,map->head);
        map->head=new_head; 
    }
    else
    {
      setDataPair(getPairPairNode(existing_entry),data);
    }

    return MAP_SUCCESS;
}

//NEW
char* mapGet(Map map,const char* key){
    if(!map||!key){
        return NULL;
    }
    PairNode res=mapFind(map,key,NULL);
    if (res){
        return getDataPair(getPairPairNode(res));
    }
    return NULL;
    
}

MapResult mapRemove(Map map, const char* key){
    if(!map || !key){
        return MAP_NULL_ARGUMENT;
    }
    PairNode previous;
    PairNode res=mapFind(map,key,&previous);
    if (!res){
        return MAP_ITEM_DOES_NOT_EXIST;
    }
    PairNode next_node=getNextPairNode(res);

    if (previous==NULL){// meaning that res is the first PairNode in the list
        map->head=next_node;
    }
    else{
        setNextPairNode(previous,next_node);
    }
    freePairNode(res);
    return MAP_SUCCESS;
}

//NEW
char* mapGetFirst(Map map){
    if(!map || mapGetSize(map) == 0){
        return NULL;
    }

    map->iterator = map->head;
    return getKeyPair(getPairPairNode(map->iterator));
}

char* mapGetNext(Map map){
    if(!map || !map->iterator){
        return NULL;
    }

    PairNode val_holder=getNextPairNode(map->iterator);
    if(!val_holder){
        return NULL;
    }

    map->iterator=val_holder;
    return getKeyPair(getPairPairNode(val_holder));
}

MapResult mapClear(Map map){
    if(map == NULL){
        return MAP_NULL_ARGUMENT;
    }

    destroyPairNode(map->head);
    map->iterator = NULL;
    map->head= NULL;
    return MAP_SUCCESS;
}

static PairNode mapFind(Map map,const char* key,PairNode *previous){
    if(!mapGetSize(map)){
        if(previous){
            *previous=NULL;
        }
        return NULL;
    }
    PairNode *pointer=&(map->head);
    PairNode previous_res=NULL;
    PairNode next_node;
    while(*pointer){
        Pair current_pair=getPairPairNode(*pointer);
        char* current_key=getKeyPair(current_pair);
        if (strcmp(current_key,key) == 0){
           if (previous){
                *previous=previous_res;
            }
            return *pointer;         
        }
        previous_res=*pointer;
        next_node = getNextPairNode(*pointer);
        pointer=&(next_node);

    }
    return NULL;
}

// debug functions 

void printMap(Map map){
    printPairNode(map->head);
}


/*****************************************
 ******************OLD FUNCTIONS**********
 *****************************************
 * 
 * */
/*
//bugs: copies in reverse, does a segmentation fault
Map mapCopy_old(Map map){
    if(!map){
        return NULL;
    }
    Map new_map = mapCreate();
    if(!new_map){
        return NULL;
    }
    char* key = mapGetFirst(map);
    mapPut(new_map,key,mapGet(map,key));
    while(key){
        key = mapGetNext(map);
        if(mapPut(new_map,key,mapGet(map,key)) == MAP_OUT_OF_MEMORY){
            return NULL;
        }
         
    }
    return new_map;
}
*/