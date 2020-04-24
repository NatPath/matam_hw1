CC=gcc

EXEC=electionExe
DEBUG_FLAG=-g
COMP_FLAG= -std=c99 -Wall -Werror -pedantic-errors -c -Iinclude
#OBJS=election.o area.o AreaNode.o string_utils.o electionTestsExample.o
#OBJS=election.o area.o AreaNode.o string_utils.o area_test.o
OBJS=election.o area.o AreaNode.o string_utils.o areaNode_test.o
$(EXEC): $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@ -L. -lmap

election.o: election.c include/election.h include/map.h include/AreaNode.h include/area.h include/string_utils.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $*.c

area.o: area/area.c include/area.h include/map.h include/string_utils.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) area/area.c

AreaNode.o: area/AreaNode.c include/AreaNode.h include/area.h include/map.h 
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) area/AreaNode.c

string_utils.o: string_utilities/string_utils.c include/string_utils.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) string_utilities/string_utils.c

electionTestsExample.o: electionTestsExample.c include/election.h include/map.h include/test_utilities.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $*.c
area_test.o: area_test.c include/area.h include/test_utilities.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $*.c
areaNode_test.o: areaNode_test.c area/area.c area/AreaNode.c include/test_utilities.h include/AreaNode.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) area/area.c $*.c
clean:
	rm -f *.o 



