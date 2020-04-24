#include <stdlib.h>
#include "include/area.h"
#include "include/test_utilities.h"
#include "include/map.h"

/*The number of tests*/
#define NUMBER_TESTS 3

bool testAreaCreateAndGet(){
    Area area = areaCreate(1,"area1");
    ASSERT_TEST(area);
    ASSERT_TEST(areaGetAreaId(area) == 1);
    ASSERT_TEST(strcmp(areaGetName(area),"area1") == 0);
    areaDestroy(area);

    return true;
}

bool testAreaChangeVotes(){
    Area area = areaCreate(1,"area1");
    areaChangeVotes(area,1,10);
    Map ballot = areaGetBallot(area);
    ASSERT_TEST(!strcmp(mapGet(ballot,"1"),"10"));
    areaChangeVotes(area,1,-1);
    ASSERT_TEST(!strcmp(mapGet(ballot,"1"),"9"));
    areaChangeVotes(area,1,-20);
    ASSERT_TEST(!strcmp(mapGet(ballot,"1"),"0"));
    areaChangeVotes(area,1,39);
    ASSERT_TEST(!strcmp(mapGet(ballot,"1"),"39"));
    areaDestroy(area);
    return true;
}

bool testAreaGetWinningTribe(){
    Area area = areaCreate(1,"area1");
    areaChangeVotes(area,1,10);
    areaChangeVotes(area,1,100);
    ASSERT_TEST(!strcmp(areaGetWinningTribe(area),"1"));

    areaChangeVotes(area,2,100);
    ASSERT_TEST(!strcmp(areaGetWinningTribe(area),"1"));

    areaChangeVotes(area,2,100);
    ASSERT_TEST(!strcmp(areaGetWinningTribe(area),"2"));

    areaChangeVotes(area,3,400);
    ASSERT_TEST(!strcmp(areaGetWinningTribe(area),"3"));

    areaChangeVotes(area,3,-420);
    ASSERT_TEST(!strcmp(areaGetWinningTribe(area),"2"));

    areaChangeVotes(area,2,-220);
    ASSERT_TEST(!strcmp(areaGetWinningTribe(area),"1"));

    //check tie breaking
    
    areaChangeVotes(area,3,500);
    ASSERT_TEST(!strcmp(areaGetWinningTribe(area),"3"));

    areaChangeVotes(area,4,500);
    ASSERT_TEST(!strcmp(areaGetWinningTribe(area),"3"));

    
    areaChangeVotes(area,4,-500);
    areaChangeVotes(area,3,-500);
    areaChangeVotes(area,2,110);
    ASSERT_TEST(!strcmp(areaGetWinningTribe(area),"1"));

    areaDestroy(area);
    return true;
}

/*The functions for the tests should be added here*/
bool (*tests[]) (void) = {
                      testAreaCreateAndGet,
                      testAreaChangeVotes,
                      testAreaGetWinningTribe
};

/*The names of the test functions should be added here*/
const char* testNames[] = {
                           "testAreaCreateAndGet",
                           "testAreaChangeVotes",
                           "testAreaGetWinningTribe"
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