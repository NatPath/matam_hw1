#include "map.h"
#include <stdio.h>>
int main(){
    Map new_map=mapCreate();
    mapPut(new_map,"1","one");
    mapPut(new_map,"2","two");

    printMap(new_map);

    mapPut(new_map,"3","three");
    printMap(new_map);

    mapPut(new_map,"2","four");
    mapPut(new_map,"3","thfghfghfree");
    mapPut(new_map,"1","oeeene");
    printMap(new_map);

    printf("%s",mapGetFirst(new_map));
    printf("%s",mapGetNext(new_map));
    printf("%s",mapGetFirst(new_map));
    printf("%s",mapGetNext(new_map));
    printf("%s",mapGetNext(new_map));

    return 0;
    
}