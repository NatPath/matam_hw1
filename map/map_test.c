#include "map.h"

int main(){
    Map new_map=mapCreate();
    mapPut(new_map,"1","one");
    mapPut(new_map,"2","two");
    mapPut(new_map,"2","two");
    mapPut(new_map,"2","two");
    mapPut(new_map,"3","three");

    printMap(new_map);
    return 0;
    
}