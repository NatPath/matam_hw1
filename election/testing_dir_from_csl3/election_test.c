#include "election.h"

int main(){
    Election new_election=electionCreate();
    electionDestroy(new_election);
    return 0;
}