CC=gcc

EXEC=electionExe
DEBUG_FLAG=-g

TESTER_DIR=./tests/our_tests

GUR_COMPILED= election_testsV1.2_vg.o utilsV1.2_vg.o 
TESTER=election_tests_gur

COMP_FLAG= -std=c99 -Wall -Werror -pedantic-errors -I$(TESTER_DIR) -c 
UTILS=utils

OBJS=election.o area.o AreaNode.o string_utils.o $(TESTER).o $(UTILS).o
## Gur compiled testers, to activate '##' utils.o and tester.o rules
##OBJS=election.o area.o AreaNode.o string_utils.o $(GUR_COMPILED)


$(EXEC): $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@ -L. -lourmap

election.o: election.c election.h map.h AreaNode.h area.h string_utils.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $*.c

area.o: area.c area.h map.h string_utils.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $*.c

AreaNode.o: AreaNode.c AreaNode.h area.h map.h 
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $*.c

string_utils.o: string_utils.c string_utils.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $*.c

$(UTILS).o: $(TESTER_DIR)/$(UTILS).c $(TESTER_DIR)/$(UTILS).h
	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) $(TESTER_DIR)/$*.c

$(TESTER).o: $(TESTER_DIR)/$(TESTER).c $(TESTER_DIR)/utils.h election.h map.h test_utilities.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $(TESTER_DIR)/$(TESTER).c

clean:
	rm *.o 



