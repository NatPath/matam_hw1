
CC=gcc
EXEC=election
DEBUG_FLAG=-g
COMP_FLAG= -std=c99 -Wall -Werror -pedantic-errors -c 

TESTER_DIR=tests
TESTER=electionTestsExample
MAP_DIR=mtm_map
MAP=map
INCLUDE_DIR=-I $(TESTER_DIR) -I $(MAP_DIR)

OBJS=election.o area.o AreaNode.o string_utils.o $(TESTER).o 

COMPILE_OS=$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $(INCLUDE_DIR) $*.c
$(EXEC): $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@ -L. -l$(MAP)

election.o: election.c election.h $(MAP_DIR)/map.h AreaNode.h area.h string_utils.h
	$(COMPILE_OS)

area.o: area.c area.h $(MAP_DIR)/map.h string_utils.h
	$(COMPILE_OS)

AreaNode.o: AreaNode.c AreaNode.h area.h $(MAP_DIR)/map.h 
	$(COMPILE_OS)

string_utils.o: string_utils.c string_utils.h
	$(COMPILE_OS)

$(TESTER).o: $(TESTER_DIR)/$(TESTER).c election.h $(MAP_DIR)/map.h test_utilities.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $(INCLUDE_DIR) $(TESTER_DIR)/$(TESTER).c

clean:
	rm -f *.o 