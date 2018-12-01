CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: randomtestcard1 randomtestcard2 randomtestadventurer cardtest1 cardtest2 cardtest3 cardtest4
	./randomtestcard1 &> randomtestcard1.out
	gcov randomtestcard1.c >> randomtestcard1.out
	./randomtestcard2 &> randomtestcard2.out
	gcov randomtestcard2.c >> randomtestcard2.out
	./randomtestadventurer &> randomtestadventurer.out
	gcov randomtestadventurer.c >> randomtestadventurer.out
	./cardtest1 &> cardtest1.out 
	gcov cardtest1.c >> cardtest1.out 
	./cardtest2 &> cardtest2.out 
	gcov cardtest2.c >> cardtest2.out
	./cardtest3 &> cardtest3.out 
	gcov cardtest3.c >> cardtest3.out
	./cardtest4 &> cardtest4.out 
	gcov cardtest4.c >> cardtest4.out
	gcov dominion.c &> dominion.out 

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)	

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)	


all: runtests randomtestcard1 randomtestcard2 randomtestadventurer cardtest1 cardtest2 cardtest3 cardtest4

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
