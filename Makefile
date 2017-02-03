CFLAGS= -ggdb -Wall -Wextra -std=c99


all: tests

tests: tests.c debug.o fieldpoly.o 
	gcc $(CFLAGS) -c tests.c
	gcc $(CFLAGS) tests.o psmt.o fieldpoly.o debug.o -o tests

fieldpoly.o: fieldpoly.c fieldpoly.h 
	gcc $(CFLAGS) -c fieldpoly.c

debug.o: debug.c debug.h 
	gcc $(CFLAGS) -c debug.c
