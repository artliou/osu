CFLAGS = -Wall -fpic -coverage -lm -O0

default: prog

prog:
	gcc -Wall -std=c99 -o prog compare.c bst.c main.c $(CFLAGS)

test:
	./prog &> bst.out
	gcov bst.c >> bst.out
	cat bst.c.gcov >> bst.out

clean:
	rm prog

cleanall: 
	rm prog 