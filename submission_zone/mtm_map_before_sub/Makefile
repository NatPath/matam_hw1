CC=gcc
EXEC=MapExe
DEBUG_FLAG=-g
TESTER_PATH=../tests/our_tests
TESTER=map_tests_gur
UTILS=utils
COMP_FLAG=-std=c99 -Wall -Werror -pedantic-errors -I$(TESTER_PATH) -c 
OBJS=map.o pair.o pairnode.o $(TESTER).o $(UTILS).o

$(EXEC): $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@

map.o: map.c map.h pair.h pairnode.h
	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) $*.c

pair.o: pair.c pair.h
	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) $*.c

pairnode.o: pairnode.c pairnode.h pair.h
	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) $*.c

$(UTILS).o: $(TESTER_PATH)/$(UTILS).c $(TESTER_PATH)/$(UTILS).h
	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) $(TESTER_PATH)/$*.c

$(TESTER).o: $(TESTER_PATH)/$(TESTER).c $(TESTER_PATH)/utils.h map.h pair.h pairnode.h
	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) $(TESTER_PATH)/$*.c


clean:
	-rm -f *.o 
