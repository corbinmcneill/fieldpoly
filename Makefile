CFLAGS= -ggdb -Wall -Wextra -std=c99 


all: tests

tests: tests.c debug.o fieldpoly.o rational.o primeField.o element.o ff256.o
	gcc $(CFLAGS) -c tests.c
	gcc $(CFLAGS) tests.o fieldpoly.o primeField.o debug.o rational.o element.o ff256.o -o tests

interpTest: interpTest.c fieldpoly.o primeField.o element.o rational.o ff256.o
	gcc $(CFLAGS) -c interpTest.c
	gcc $(CFLAGS) interpTest.o fieldpoly.o primeField.o element.o rational.o ff256.o -o interpTest

fieldpoly.o: fieldpoly.c fieldpoly.h element.h 
	gcc $(CFLAGS) -c fieldpoly.c

rational.o: rational.c rational.h element.h
	gcc $(CFLAGS) -c rational.c

primeField.o: primeField.c primeField.h element.h
	gcc $(CFLAGS) -c primeField.c

ff256.o: ff256.c ff256.h element.h
	gcc $(CFLAGS) -c ff256.c

element.o: element.c element.h
	gcc $(CFLAGS) -c element.c

debug.o: debug.c debug.h 
	gcc $(CFLAGS) -c debug.c

ff256demo: ff256demo.c ff256.o
	gcc $(CFLAGS) -c ff256demo.c
	gcc $(CFLAGS) ff256demo.o ff256.o -o ff256demo

clean:
	rm -f *.o
	rm -f tests
	rm -f ff256demo
