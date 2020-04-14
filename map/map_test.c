#include "map.h"

int main(){
    Map new_map=mapCreate();
    mapPut(new_map,"1","one");
    mapPut(new_map,"2","two");
    mapPut(new_map,"2","two");
    mapPut(new_map,"2","two");
    mapPut(new_map,"3","three");

    printMap(new_map);
    Map map2=mapCopy(new_map);
    mapDestroy(new_map);
    printMap(map2);

    return 0;
    
}