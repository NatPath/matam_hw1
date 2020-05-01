CC=gcc
EXEC=MapExe
DEBUG_FLAG=-g
COMP_FLAG=-std=c99 -Wall -Werror -pedantic-errors -c 
TESTER=map_test_com
OBJS=map.o pair.o pairnode.o $(TESTER).o

$(EXEC): $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@

map.o: map.c map.h pair.h pairnode.h
	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) $*.c

pair.o: pair.c pair.h
	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) $*.c

pairnode.o: pairnode.c pairnode.h pair.h
	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) $*.c

$(TESTER).o: $(TESTER).c map.h pair.h pairnode.h
	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) $*.c


clean:
	rm -f *.o 
