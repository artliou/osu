CC = gcc
CFLAGS = -g -Wall -std=c99

all : tests prog spellChecker

prog : main.o hashMap.o
	$(CC) $(CFLAGS) -o $@ $^
	gcc -g -Wall -std=c99 -o prog main.o hashMap.o

tests : tests.o hashMap.o CuTest.o
	$(CC) $(CFLAGS) -o $@ $^
	gcc -g -Wall -std=c99 -o tests tests.o hashMap.o CuTest.o

spellChecker : spellChecker.o hashMap.o
	$(CC) $(CFLAGS) -o $@ $^
	gcc -g -Wall -std=c99 -o spellChecker spellChecker.o hashMap.o

main.o : main.c hashMap.h
	gcc -g -Wall -std=c99 -c main.c

tests.o : tests.c CuTest.h hashMap.h
	gcc -g -Wall -std=c99 -c tests.c

hashMap.o : hashMap.h hashMap.c
	gcc -g -Wall -std=c99 -c hashMap.c

CuTest.o : CuTest.h CuTest.c
	gcc -g -Wall -std=c99 -c CuTest.c

spellChecker.o : spellChecker.c hashMap.h
	gcc -g -Wall -std=c99 -c spellChecker.c

.PHONY : clean memCheckTests memCheckProg

memCheckTests :
	valgrind --tool=memcheck --leak-check=yes tests

memCheckProg :
	valgrind --tool=memcheck --leak-check=yes prog

memCheckSpellChecker :
	valgrind --tool=memcheck --leak-check=yes spellChecker

clean :
	-rm *.o
	-rm tests
	-rm prog
	-rm spellChecker
