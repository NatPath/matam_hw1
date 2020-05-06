#include <stdlib.h>
#include "../../election.h"
#include "../../test_utilities.h"
#include "../../map.h"


/*The number of tests*/
#define NUMBER_TESTS 8

bool deleteOnlyFirstArea (int area_id) {
	return area_id == 1;
}

bool testElectionCreate(){
    Election election = electionCreate();
    ASSERT_TEST(election);

    electionDestroy(election);
	return true;

}


bool testElectionAddTribeAndGetName(){
    Election election = electionCreate();

    //test null arguments
    ASSERT_TEST(electionAddTribe(NULL,1,"tribe a") == ELECTION_NULL_ARGUMENT);
    ASSERT_TEST(electionAddTribe(election,1,NULL) == ELECTION_NULL_ARGUMENT);

    
    // test basic functionality 
    ASSERT_TEST(electionAddTribe(election,1,"tribe a") == ELECTION_SUCCESS);
     const char* name = electionGetTribeName(election,1);
    ASSERT_TEST(!strcmp(name,"tribe a")); 
    free((char*)name);
     
    ASSERT_TEST(electionAddTribe(election,2,"tribe b") == ELECTION_SUCCESS);
    name = electionGetTribeName(election,2);
    ASSERT_TEST(!strcmp(name,"tribe b")); 
    free((char*)name);

    // test adding an existing tribe
    ASSERT_TEST(electionAddTribe(election,1,"tribe aa") == ELECTION_TRIBE_ALREADY_EXIST);
    name = electionGetTribeName(election,1);
    ASSERT_TEST(!strcmp(name,"tribe a")); 
    free((char*)name);

    //test adding new tribe with existing name
    ASSERT_TEST(electionAddTribe(election,10,"tribe a") == ELECTION_SUCCESS);

    // test illegal id
    ASSERT_TEST(electionAddTribe(election,-1,"tribe invalid") == ELECTION_INVALID_ID);

    // test illegal name
    ASSERT_TEST(electionAddTribe(election,3,"tribe &&") == ELECTION_INVALID_NAME);
    ASSERT_TEST(electionAddTribe(election,3,"TRibe") == ELECTION_INVALID_NAME);


    // test getting name of unadded tribe
    ASSERT_TEST(!electionGetTribeName(election,3));

    electionDestroy(election);
	return true;
}

bool testElectionAddArea(){
    Election election = electionCreate();

    //test null arguments
    ASSERT_TEST(electionAddArea(NULL,1,"area a") == ELECTION_NULL_ARGUMENT);
    ASSERT_TEST(electionAddArea(election,1,NULL) == ELECTION_NULL_ARGUMENT);

    // test illegal id
    ASSERT_TEST(electionAddArea(election,-1,"area invalid") == ELECTION_INVALID_ID);
    
    // test basic functionality 
    ASSERT_TEST(electionAddArea(election,1,"area a") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election,2,"area b") == ELECTION_SUCCESS);

    // test adding an existing area
    ASSERT_TEST(electionAddArea(election,1,"area aa") == ELECTION_AREA_ALREADY_EXIST);
    
    // test illegal name
    ASSERT_TEST(electionAddArea(election,3,"area &&") == ELECTION_INVALID_NAME);
    ASSERT_TEST(electionAddArea(election,3,"ArEa") == ELECTION_INVALID_NAME);

    //test adding new tribe with existing name
    ASSERT_TEST(electionAddArea(election,10,"area a") == ELECTION_SUCCESS);

    electionDestroy(election);
	return true;
}

bool testElectionSetTribeName(){
    Election election = electionCreate();
    electionAddTribe(election,1,"tribe a");
    electionAddTribe(election,2,"tribe b");

    const char *name = electionGetTribeName(election,1);
    ASSERT_TEST(!strcmp(name,"tribe a"));
    free((char*)name);
    name = electionGetTribeName(election,2);
    ASSERT_TEST(!strcmp(name,"tribe b"));
    free((char*)name);
    // test null arguments
    ASSERT_TEST(electionSetTribeName(election,1,NULL) == ELECTION_NULL_ARGUMENT);
    ASSERT_TEST(electionSetTribeName(NULL,1,"new tribe a") == ELECTION_NULL_ARGUMENT);

    // test basic functionality 
    ASSERT_TEST(electionSetTribeName(election,1,"new tribe a") == ELECTION_SUCCESS);
    ASSERT_TEST(electionSetTribeName(election,2,"new tribe b") == ELECTION_SUCCESS);
    
    name = electionGetTribeName(election,1);
    ASSERT_TEST(!strcmp(name,"new tribe a"));
    free((char*)name);
    name = electionGetTribeName(election,2);
    ASSERT_TEST(!strcmp(name,"new tribe b"));
    free((char*)name);

    // test illegal id
    ASSERT_TEST(electionSetTribeName(election,-1,"area invalid") == ELECTION_INVALID_ID);

    // test adding a nonexistent tribe
    ASSERT_TEST(electionSetTribeName(election,10,"new tribe aa") == ELECTION_TRIBE_NOT_EXIST);
    
    // test illegal name
    ASSERT_TEST(electionSetTribeName(election,1,"new tribe @@") == ELECTION_INVALID_NAME);
    ASSERT_TEST(electionSetTribeName(election,1,"nEw trIbe") == ELECTION_INVALID_NAME);

    electionDestroy(election);
	return true;
}

bool testElectionRemoveTribe(){
    Election election = electionCreate();
    electionAddTribe(election,1,"tribe a");
    electionAddTribe(election,2,"tribe b");

    // test null arguments
    ASSERT_TEST(electionRemoveTribe(NULL,1) == ELECTION_NULL_ARGUMENT);

    // test illegal id
    ASSERT_TEST(electionRemoveTribe(election,-1) == ELECTION_INVALID_ID);

    // test removing nonexistent tribe
    ASSERT_TEST(electionRemoveTribe(election,3) == ELECTION_TRIBE_NOT_EXIST);

    // test basic functionality
    ASSERT_TEST(electionRemoveTribe(election,1) == ELECTION_SUCCESS);
    ASSERT_TEST(electionRemoveTribe(election,2) == ELECTION_SUCCESS);

    ASSERT_TEST(electionRemoveTribe(election,1) == ELECTION_TRIBE_NOT_EXIST);
    ASSERT_TEST(electionRemoveTribe(election,2) == ELECTION_TRIBE_NOT_EXIST);

    electionDestroy(election);
	return true;

}

bool testElectionAddRemoveVote(){
    Election election = electionCreate();

    electionAddTribe(election,1,"tribe");
    electionAddArea(election,1,"area");

    // test null arguments
    ASSERT_TEST(electionAddVote(NULL,1,1,1) == ELECTION_NULL_ARGUMENT);
    ASSERT_TEST(electionRemoveVote(NULL,1,1,1) == ELECTION_NULL_ARGUMENT);

    // test illegal id
    ASSERT_TEST(electionAddVote(election,-1,1,1) == ELECTION_INVALID_ID);
    ASSERT_TEST(electionRemoveVote(election,-1,1,1) == ELECTION_INVALID_ID);

    // test invalid votes
    ASSERT_TEST(electionAddVote(election,1,1,-1) == ELECTION_INVALID_VOTES);
    ASSERT_TEST(electionAddVote(election,1,1,0) == ELECTION_INVALID_VOTES);

    ASSERT_TEST(electionRemoveVote(election,1,1,-1) == ELECTION_INVALID_VOTES);
    ASSERT_TEST(electionRemoveVote(election,1,1,0) == ELECTION_INVALID_VOTES);

    //test nonexistent area or tribe
    ASSERT_TEST(electionAddVote(election,1,2,1) == ELECTION_TRIBE_NOT_EXIST);
    ASSERT_TEST(electionAddVote(election,2,1,1) == ELECTION_AREA_NOT_EXIST);

    ASSERT_TEST(electionRemoveVote(election,1,2,1) == ELECTION_TRIBE_NOT_EXIST);
    ASSERT_TEST(electionRemoveVote(election,2,1,1) == ELECTION_AREA_NOT_EXIST);

    // test basic functionality
    ASSERT_TEST(electionAddVote(election,1,1,1) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election,1,1,10) == ELECTION_SUCCESS);

    ASSERT_TEST(electionRemoveVote(election,1,1,1) == ELECTION_SUCCESS);
    ASSERT_TEST(electionRemoveVote(election,1,1,15) == ELECTION_SUCCESS);

    electionDestroy(election);
	return true;

}

bool testElectionRemoveAreas() {
	Election election = electionCreate();

    // test null arguments
    ASSERT_TEST(electionRemoveAreas(NULL,deleteOnlyFirstArea) == ELECTION_NULL_ARGUMENT);
    ASSERT_TEST(electionRemoveAreas(election,NULL) == ELECTION_NULL_ARGUMENT);


	ASSERT_TEST(electionAddArea(election, 1, "area a") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 2, "area b") == ELECTION_SUCCESS);

	ASSERT_TEST(electionRemoveAreas(election, deleteOnlyFirstArea) == ELECTION_SUCCESS);

    // make sure the area was really removed
    ASSERT_TEST(electionAddArea(election,1,"area a") == ELECTION_SUCCESS);
    // make sure the other area wasn't removed
    ASSERT_TEST(electionAddArea(election,2,"area b") == ELECTION_AREA_ALREADY_EXIST);

	electionDestroy(election);
	return true;
}

bool testElectionnComputeAreasToTribesMapping(){
    Election election = electionCreate();
    // check empty election, should return an empty map
    Map result = electionComputeAreasToTribesMapping(election);
    ASSERT_TEST(result);
    ASSERT_TEST(!mapGetFirst(result));
    mapDestroy(result);

    electionAddArea(election,1,"area a");

    electionAddTribe(election,1,"tribe a");
    electionAddTribe(election,2,"tribe b");
    electionAddTribe(election,3,"tribe c");

    // test election with no ties
    electionAddVote(election,1,1,1);
    electionAddVote(election,1,2,5);
    electionAddVote(election,1,3,10);

    
    result = electionComputeAreasToTribesMapping(election);
    ASSERT_TEST(!strcmp(mapGet(result,"1"),"3"));
    mapDestroy(result);

    // test tie breaking
    electionRemoveVote(election,1,3,5);

    result = electionComputeAreasToTribesMapping(election);
    ASSERT_TEST(!strcmp(mapGet(result,"1"),"2"));
    mapDestroy(result);

    electionAddVote(election,1,1,4);
    result = electionComputeAreasToTribesMapping(election);
    ASSERT_TEST(!strcmp(mapGet(result,"1"),"1"));
    mapDestroy(result);

    electionDestroy(election);
	return true;

}

/*The functions for the tests should be added here*/
bool (*tests[]) (void) = {
                      testElectionCreate,
                      testElectionRemoveAreas,
                      testElectionAddTribeAndGetName,
                      testElectionAddArea,
                      testElectionSetTribeName,    
                      testElectionRemoveTribe,
                      testElectionAddRemoveVote,
                      testElectionnComputeAreasToTribesMapping
};

/*The names of the test functions should be added here*/
const char* testNames[] = {
                           "testElectionCreate",
                           "testElectionRemoveAreas",
                           "testElectionAddTribeAndGetName",
                           "testElectionAddArea",
                           "testElectionSetTribeName",
                           "testElectionRemoveTribe",
                           "testElectionAddRemoveVote",
                           "testElectionnComputeAreasToTribesMapping"
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