CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c 
	gcc -o testme testme.c 

runtests: testme
	./testme 

all: runtests

clean:
	rm -f *.o 