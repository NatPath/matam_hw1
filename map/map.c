#include "map.h"
#include "pairnode.h"
#include <string.h>
#include <stdlib.h>

struct Map_t{
    PairNode head;
    PairNode iterator;
};
PairNode mapFind(Map map,const char* key,PairNode *previous);
void printMap(Map map);

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
bool mapContains(Map map, const char* key)
{
    return mapGet(map,key) != NULL;
}
MapResult mapPut(Map map, const char* key,const char* data){
    
    if(!map || !key || !data)
    {
        return MAP_NULL_ARGUMENT;
    }
    PairNode existing_entry = mapFind(map,key,NULL);
    if (!existing_entry){
        PairNode new_head=createPairNode(key,data);
        if (!new_head){
            return MAP_OUT_OF_MEMORY;
        }
        setNextPairNode(new_head,map->head);
        map->head=new_head; 
    }
    else
    {
      setDataPairNode(existing_entry,data);
    }

    return MAP_SUCCESS;
}
char* mapGet(Map map,const char* key){
    PairNode res=mapFind(map,key,NULL);
    if (res){
        return getDataPairNode(res);
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
    freePairNode(res);
    setNextPairNode(previous,next_node);
    return MAP_SUCCESS;
}

char* mapGetFirst(Map map)
{
    if(!map || mapGetSize(map) == 0){
        return NULL;
    }

    map->iterator = map->head;
    return getKeyPairNode(map->iterator);
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
    return getKeyPairNode(val_holder);
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

//Gets a map and a key and a pointer to a PairNode. returns the Node which contains the key if it exists.
//if the key doesn't exist in the map,returns NULL.
//the pointer "previous" will contain the Node before the searched Node if found.
//if the node which contains the key is first, previous will be NULL
PairNode mapFind(Map map,const char* key,PairNode *previous){
    PairNode *pointer=&(map->head);
    PairNode *previous_res=NULL;
    PairNode next_node;
    while(*pointer){
        if (strcmp(getKeyPairNode(*pointer),key) == 0){
           if (previous){
                *previous=*previous_res;
            }
            return *pointer;         
        }
        previous_res=pointer;
        next_node = getNextPairNode(*pointer);
        pointer=&(next_node);

    }
    return NULL;

}

void printMap(Map map){
    printPairNode(map->head);
}


