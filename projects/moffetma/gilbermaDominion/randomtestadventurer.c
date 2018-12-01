/*
Max Moffett 
randomtestadventurer - Adventurer 
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
#define TESTCARD "adventurer"

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
	
	int seed=20; 

	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	//test loop for 1000 hands 
	printf("------Testing Adventurer for 1000 hands------\n");
	for (n=0; n<1000;n++)
	{	

		p=0; 
		int successFlag=1; 
		//set up test gamestate 
		struct gameState testG; 
		//randomize number of players 
		int numPlayers=  (rand() % (4 + 1 - 2) + 2);
		//fill our original gamestate struct with random bytes (from lecture)
		for (i=0;i<sizeof(struct gameState);i++){
			((char*)&G)[i] = floor(Random()*256);
			}
		
		//for this test we have to initialize the game to ensure all cards are dealt to player 0 
		initializeGame(numPlayers, k, seed, &G);
		//set treasure count to 0 
		int treasureCount=0; 

		//fill player deck, discard, and hand count with sane random values 
		int l; 
		for (l=0;l<numPlayers;l++)
		{
		G.deckCount[l] = floor(Random() * MAX_DECK);
		G.discardCount[l] = floor(Random() * MAX_DECK);
		G.handCount[l] = floor(Random() * MAX_HAND); 
		}	
		//randomize played card couunt for the game state 
		G.playedCardCount= floor(Random() * MAX_DECK);
		
		//fill current player deck, discard, and hand counts with sane random values 
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		
		//set turn to our randomized current player 
		//G.whoseTurn = p;
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

	
		//loop through player 0's hand to get a count of their treasure cards 
		int j;
		for (j=0; j< G.handCount[p]; j++)
		{
			if(G.hand[p][j]==copper || G.hand[p][j]==silver || G.hand[p][j]==gold)
				treasureCount++; 
		}

		//Display stats for this hand 
		printf("------Hand %d ------\n",n+1);
		printf("Number of players this hand: %d\n", numPlayers);
		printf("Player %d's turn to play Adventurer\n", p);
		//display tracking info for player 0 status 
		printf("Player %d deck count before playing: %d \n", p, G.deckCount[p]); 
		printf("Player %d discard count before playing: %d \n", p, G.discardCount[p]); 
		printf("Player %d treasure count before playing : %d \n",p, treasureCount); 

		//copy gamestate G to test state testG for comparison after calling our card function 
		memcpy(&testG, &G, sizeof(struct gameState));
		
		//reset treasure count to 0 
		treasureCount=0; 

		printf("------Playing Adventurer card------\n"); 
		//get result of cardEffect as an int to check it for some internal issue and call the card function 
		int checkFunction = cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);
		//assert that it returned 0 so there was no internal problem 
		assert(checkFunction == 0); 

		//check treasure count after playing adventurer 
		int m;
		for (m=0; m< G.handCount[p]; m++)
		{
			if(G.hand[p][m]==copper || G.hand[p][m]==silver || G.hand[p][m]==gold)
				treasureCount++; 

		}
		//display tracking info again after playing 
		printf("Player %d deck count after playing: %d \n", p, G.deckCount[p]);
		printf("Player %d discard count after playing: %d \n", p, G.discardCount[p]); 
		printf("Player %d treasure count after playing : %d \n",p, treasureCount); 

		//check that the number of Actions was not affected, if it was display an error and set success flag to 0 
		printf("-----Checking Actions------\n");
		if (G.numActions != testG.numActions)
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

		//check that number of played cards was not affected  
		printf("-----Checking Played Card Count------\n");
		if (G.playedCardCount != testG.playedCardCount)
			{printf("Test failed, incorrected played card count! Actual: %d expected: %d \n", G.playedCardCount, testG.playedCardCount); successFlag=0;}
		else {printf("Test passed!\n");}
		
		//Check Player 0's discard count to make sure it increased 
		printf("------Checking Player 0's discard count------\n");
		if(G.discardCount[0] < testG.discardCount[0] || G.discardCount[0] == testG.discardCount[0])
			{
				printf("Test failed, player 0's discard count is incorrect! \n");
				successFlag=0;
			}
			else {printf("Test passed for player 0, was: %d now: %d \n", testG.discardCount[0], G.discardCount[0]);}

		//loop through other player discards and verify they were not affected 
		printf("------Checking Other Player Discard Counts------\n");
		int y;
		for (y=1;y<numPlayers;y++)
		{
			if(G.discardCount[y] != testG.discardCount[y])
				{printf("Test failed, player %d's discard count changed Actual: %d expected: %d !\n", y, G.discardCount[y], testG.discardCount[y]);}
			else {printf("Test passed for player %d\n", y);} 

		}
		//check to make sure 2 cards were added to player 0's hand 
		printf("------Checking Player 0's hand count------\n");
		if(G.handCount[0] != testG.handCount[0]+2)
			{
				printf("Test failed, player 0's hand count changed! Actual: %d Expected: %d \n", G.handCount[0], testG.handCount[0]);
				successFlag=0;
			}
			else {printf("Test passed for player 0, was: %d now: %d \n", testG.handCount[0], G.handCount[0]);}

		//loop through other player hand counts and verify they were not affected 
		int z;
		printf("------Checking Other Player Hand Counts------\n");
		for (z=1; z<numPlayers;z++)
		{
			if(G.handCount[z] != testG.handCount[z])
			{
				printf("Test failed, player %d's hand count changed! Actual: %d Expected: %d \n", z, G.handCount[z], testG.handCount[z]);
				successFlag=0;
			}
			else {printf("Test passed for player %d\n", z);}
		}

		//check to make sure player 0's deck count decreased from the original 
		printf("------Checking Player 0's deck count------\n");
		if(G.deckCount[0] > testG.deckCount[0] || G.deckCount[0] == testG.deckCount[0])
			{
				printf("Test failed, player 0's deck count has not decreased!\n");
				successFlag=0;
			}
			else {printf("Test passed for player 0, was: %d now: %d \n", testG.deckCount[0], G.deckCount[0]);}

		//loop through other player deck counts and verify they were not affected 
		int x;
		printf("------Checking Other Player Deck Counts------\n");
		for (x=1; x<numPlayers;x++)
		{
			if(G.deckCount[x] != testG.deckCount[x])
			{
				printf("Test failed, player %d's hand count changed! Actual: %d Expected: %d \n", x, G.deckCount[x], testG.deckCount[x]);
				successFlag=0;
			}
			else {printf("Test passed for player %d\n", x);}
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