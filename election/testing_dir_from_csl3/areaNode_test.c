#include <stdlib.h>
#include "include/area.h"
#include "include/AreaNode.h"
#include "include/test_utilities.h"
#include "include/map.h"

/*The number of tests*/
#define NUMBER_TESTS 5

bool testAreaNodeCreateAndGet(){
    AreaNode node = areaNodeCreate(1,"area1");
    ASSERT_TEST(node);
    Area area = areaNodeGetArea(node);
    ASSERT_TEST(area);
    ASSERT_TEST(1 == areaGetAreaId(area));
    ASSERT_TEST(!strcmp("area1",areaGetName(area)));
    areaNodeDestroy(node);
    

    return true;
}

bool testAreaNodeAddAndGetNext(){
    AreaNode node = areaNodeCreate(1,"1");
    AreaNode node2 = areaNodeAdd(node,2,"2");

    AreaNode next = areaNodeGetNext(node2);
    ASSERT_TEST(next == node);

    AreaNode node3 = areaNodeAdd(node2,3,"3");
    next =  areaNodeGetNext(node3);
    ASSERT_TEST(next==node2);
    next = areaNodeGetNext(next);
    ASSERT_TEST(next == node);


    areaNodeDestroy(node3);

    return true;


}

bool testAreaNodeFind(){
    AreaNode node = areaNodeCreate(1,"1");
    AreaNode node2 = areaNodeAdd(node,2,"2");
    AreaNode node3 = areaNodeAdd(node2,3,"3");
    AreaNode node4 = areaNodeAdd(node3,4,"4");

    ASSERT_TEST(!areaNodeFind(node2,3,NULL));
    ASSERT_TEST(areaNodeFind(node4,3,NULL)== node3);
    ASSERT_TEST(areaNodeFind(node4,4,NULL)== node4);
   
    AreaNode prev;
    ASSERT_TEST(areaNodeFind(node4,1,&prev) == node);
    ASSERT_TEST(prev == node2);
    areaNodeFind(node4,4,&prev);
    ASSERT_TEST(!prev);

    areaNodeDestroy(node4);
    return true;
}

bool testAreaNodeSearchAndDestroy(){
    AreaNode node = areaNodeCreate(1,"1");
    AreaNode node2 = areaNodeAdd(node,2,"2");
    AreaNode node3 = areaNodeAdd(node2,3,"3");
    AreaNode node4 = areaNodeAdd(node3,4,"4");

    ASSERT_TEST(areaNodeSearchAndDestroy(node4,2) == AREA_NODE_SUCCESS);
    ASSERT_TEST(areaNodeSearchAndDestroy(node4,6) == AREA_DOES_NOT_EXIST);

    ASSERT_TEST(areaNodeGetNext(node4) == node3);
    ASSERT_TEST(areaNodeGetNext(node3) == node);
    ASSERT_TEST(!areaNodeGetNext(node));

    ASSERT_TEST(areaNodeSearchAndDestroy(node4,4) == AREA_NODE_SUCCESS);
    ASSERT_TEST(areaNodeGetNext(node4) == node);
    areaNodeDestroy(node4);

    return true;
}

bool testAreaNodeChangeVotes(){
    
    AreaNode node = areaNodeCreate(1,"1");
    AreaNode node2 = areaNodeAdd(node,2,"2");
    AreaNode node3 = areaNodeAdd(node2,3,"3");

    ASSERT_TEST(areaNodeChangeVotes(node3,2,2,12) == AREA_NODE_SUCCESS);
    ASSERT_TEST(areaNodeChangeVotes(node3,1,1,-12) == AREA_NODE_SUCCESS);
    ASSERT_TEST(areaNodeChangeVotes(node3,2,2,-2) == AREA_NODE_SUCCESS);
    ASSERT_TEST(areaNodeChangeVotes(node3,2,1,2) == AREA_NODE_SUCCESS);
    Area area1 = areaNodeGetArea(node);
    Area area2 = areaNodeGetArea(node2);

    ASSERT_TEST(!strcmp(mapGet(areaGetBallot(area1),"1"),"0"));
    ASSERT_TEST(!strcmp(mapGet(areaGetBallot(area2),"1"),"2"));
    ASSERT_TEST(!strcmp(mapGet(areaGetBallot(area2),"2"),"10"));

    ASSERT_TEST(areaNodeChangeVotes(node3,5,5,5) == AREA_DOES_NOT_EXIST);

    areaNodeDestroy(node3);

    return true;
}


/*The functions for the tests should be added here*/
bool (*tests[]) (void) = {
                     testAreaNodeCreateAndGet,
                     testAreaNodeAddAndGetNext,
                     testAreaNodeFind,
                     testAreaNodeSearchAndDestroy,
                     testAreaNodeChangeVotes
};

/*The names of the test functions should be added here*/
const char* testNames[] = {
    "testAreaNodeCreateAndGet",
    "testAreaNodeAddAndGetNext",
    "testAreaNodeFind",
    "testAreaNodeSearchAndDestroy",
    "testAreaNodeChangeVotes"
                           
};

int main(int argc, char *argv[]) {
    if (argc == 1) {

        for (int test_idx = 0; test_idx < NUMBER_TESTS; test_idx++) {
              RUN_TEST(tests[test_idx], testNames[test_idx]);
        }
        return 0;
    }
    if (argc != 2) {
      fprintf(stdout, "Usage: election <test index>\n");
      return 0;
  }

  int test_idx = strtol(argv[1], NULL, 10);
  if (test_idx < 1 || test_idx > NUMBER_TESTS) {
      fprintf(stderr, "Invalid test index %d\n", test_idx);
      return 0;
  }

  RUN_TEST(tests[test_idx - 1], testNames[test_idx - 1]);
  return 0;
}