CFLAGS= -ggdb -Wall -Wextra -std=c99


all: tests

tests: tests.c debug.o fieldpoly.o rational.o element.o
	gcc $(CFLAGS) -c tests.c
	gcc $(CFLAGS) tests.o fieldpoly.o debug.o rational.o element.o -o tests

fieldpoly.o: fieldpoly.c fieldpoly.h element.h 
	gcc $(CFLAGS) -c fieldpoly.c

rational.o: rational.c rational.h element.h
	gcc $(CFLAGS) -c rational.c

element.o: element.c element.h
	gcc $(CFLAGS) -c element.c

debug.o: debug.c debug.h 
	gcc $(CFLAGS) -c debug.c

clean:
	rm *.o
