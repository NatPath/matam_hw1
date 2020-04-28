#include "map.h"
#include <stdio.h>
int main(){
    Map new_map=mapCreate();
    mapPut(new_map,"1","one");
    mapPut(new_map,"2","two");
    mapPut(new_map,"2","two");
    mapPut(new_map,"3","two");
    mapPut(new_map,"4","three");

    printMap(new_map);
    puts("Copying map:\n");
    Map map2=mapCopy(new_map);
    mapDestroy(new_map);
    printMap(map2);

    puts("Testing if mapContains works:\n");
    MAP_FOREACH(i,map2){
        printf("%d \n",mapContains(map2,i));
        printf("%s\n", mapGet(map2,i));

   }
 
   printf("%s", mapGet(map2,"999"));
   mapDestroy(map2);
   return 0;
    
}