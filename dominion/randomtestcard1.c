/*
Max Moffett 
randomtestcard1- Great Hall
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define TESTCARD "great_hall"
//great hall test

int main()
{
	//set up random seeds 
	time_t t; 
	srand((unsigned) time(&t));

	int i, n, p; 
	//create original game state 
	struct gameState G; 
	//variables needed for cardEffect all set to 0 
	int choice1=0, choice2=0, choice3=0, handpos=0, bonus=0; 
	 
	//seeds for Random() function 
	SelectStream(2);
	PutSeed(3);

	//flags for our test loops, set initial success flag to 1, any failures will change it 
	int successCount=0; 
	

	//test loop for 1000 hands 
	printf("------Testing Great Hall for 1000 hands------\n");
	for (n=0; n<1000;n++)
	{	
		int successFlag=1; 
		//set up test gamestate 
		struct gameState testG; 
		//randomize number of players 
		int numPlayers=  (rand() % (4 + 1 - 2) + 2);
		//fill our original gamestate struct with random bytes (from lecture)
		for (i=0;i<sizeof(struct gameState);i++){
			((char*)&G)[i] = floor(Random()*256);
			}
		//pick a random player 
		p = floor(Random()* MAX_PLAYERS);
		//if random player p is greater than our # of players, set the # of players to p+1 
		if (p > numPlayers)
		{
			numPlayers = p+1; 
		}
		//set the number of players for our gamestate 
		G.numPlayers = numPlayers;
		
		//fill player deck, discard, and hand count with sane random values 
		int k; 
		for (k=0;k<numPlayers;k++)
		{
		G.deckCount[k] = floor(Random() * MAX_DECK);
		G.discardCount[k] = floor(Random() * MAX_DECK);
		G.handCount[k] = floor(Random() * MAX_HAND); 
		}	
		//randomize played card couunt for the game state 
		G.playedCardCount= floor(Random() * MAX_DECK);
		
		//fill current player deck, discard, and hand counts with sane random values 
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		
		//set turn to our randomized current player 
		G.whoseTurn = p;
		//set other game state attributes to known values for comparison later 
		G.numActions =0; 
		G.numBuys =1; 
		G.outpostPlayed=0; 

		//randomize values for estate cards, using a balance of values for a 2 to 4 player game
		G.supplyCount[estate]=floor(Random()*10);
		G.supplyCount[duchy]=floor(Random()*10);
		G.supplyCount[province]=floor(Random()*10);

		//randomize values for treasure cards based on standard treasure maxes for a normal game 
		G.supplyCount[copper]=floor(Random()*60);
		G.supplyCount[silver]=floor(Random()*40);
		G.supplyCount[gold]=floor(Random()*30);

		//Display stats for this hand 
		printf("------Hand %d ------\n",n+1);
		printf("Number of players this hand: %d\n", numPlayers);
		printf("Player %d's turn to play Great Hall\n", p);

		//copy gamestate G to test state testG for comparison after calling our card function 
		memcpy(&testG, &G, sizeof(struct gameState));
		
		//get result of cardEffect as an int to check it for some internal issue and call the card function 
		int checkFunction = cardEffect(great_hall, choice1, choice2, choice3, &G, handpos, &bonus);
		
		//assert that it returned 0 so there was no internal problem 
		assert(checkFunction == 0); 

		//check that the number of Actions was increased by 1 when compared to testG which did not play Great Hall 
		//if it was, display error and set successflag to 0 
		printf("-----Checking Actions------\n");
		if (G.numActions != testG.numActions+1)
			{printf("Test failed, incorrect # of actions!\n"); successFlag=0;}
		else {printf("Test passed!\n");}
		// check that the number of Buys was not affected 
		//if it was, display error and set successflag to 0 
		printf("-----Checking Number of Buys------\n");
		if (G.numBuys != testG.numBuys)
			{printf("Test failed, incorrect # of buys!\n"); successFlag=0;}
		else {printf("Test passed!\n");}
		//check that the Outpost Played status was not changed 
		printf("-----Checking Outpost Played Status------\n");
		if (G.outpostPlayed != testG.outpostPlayed)
			{printf("Test failed, incorrect Outpost status!\n"); successFlag=0;}
		else {printf("Test passed!\n");}

		//check that number of played cards was increased by 1 as Great Hall calls discardCard 
		printf("-----Checking Played Card Count------\n");
		if (G.playedCardCount != testG.playedCardCount+1)
			{printf("Test failed, incorrected played card count! Actual: %d expected: %d \n", G.playedCardCount, testG.playedCardCount+1); successFlag=0;}
		else {printf("Test passed!\n");}
		
		//loop through player discards and verify they were not affected 
		printf("------Checking Discard Counts------\n");
		int y;
		for (y=0;y<numPlayers;y++)
		{
			if(G.discardCount[y] != testG.discardCount[y])
				{printf("Test failed, player %d's discard count changed!\n", y);}
			else {printf("Test passed for player %d\n", y);} 

		}

		//loop through player hand counts and verify they were not affected 
		int z;
		printf("------Checking Player Hand Counts------\n");
		for (z=0; z<numPlayers;z++)
		{
			if(G.handCount[z] != testG.handCount[z])
			{
				printf("Test failed, player %d's hand count changed!\n", z);
				successFlag=0;
			}
			else {printf("Test passed for player %d\n", z);}
		}

		//verify that coin counts were not affected 
		printf("------Checking Coin Counts------\n");
		if(testG.supplyCount[copper] != G.supplyCount[copper] || testG.supplyCount[silver] != G.supplyCount[silver] || testG.supplyCount[gold] != G.supplyCount[gold])
			{printf("---Test failed, coin counts modified!---\n"); successFlag=0;}
		else printf("Test passed!\n"); 

		//verify that the # of estate cards was not affected 
		printf("------Checking Estate Card Counts------\n");
		if(testG.supplyCount[estate] != G.supplyCount[estate] || testG.supplyCount[duchy] != G.supplyCount[duchy] || testG.supplyCount[province] != G.supplyCount[province])
			{printf("---Test failed, estate cards modified!---\n");}
		else 
			printf("Test passed!\n");

		//if all tests were successful (no failed test changed the flag to 0), increment success count 
		if(successFlag==1)
			{successCount++;}
		//display successful tests out of total tests n+1 loop counter 
		printf("Successful test count: %d out of %d\n\n", successCount, n+1); 
		
	}

return 0;

}