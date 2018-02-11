CC=gcc
CFLAGS=-Wall -std=c99

all: prog

prog: circularList.o circularList.o
	gcc -g -Wall -std=c99 -o prog circularList.o circularListMain.o
circularList.o: circularList.c circularList.h
	gcc -g -Wall -std=c99 -c circularList.c
circularListMain.o: circularListMain.c circularListMain.h
	gcc -g -Wall -std=c99 -c circularListMain.c

clean:
	-rm *.o

cleanall: clean
	-rm prog
