/*
Max Moffett 
Cardtest2.c - adventurer
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 900;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 1;
    printf("Player 1 discard count before: %d\n", testG.discardCount[thisPlayer]);
    
    printf("Player 1 hand:\n");
    int p;
    for (p = 0; p < numHandCards(&G); p++)
    {	
    	printf("card %d: %d", p , testG.hand[thisPlayer][p]);
    	printf(" cost %d \n", getCost(testG.hand[thisPlayer][p]));
    	handpos++;
    }
    handpos=0;

    printf("player 1 deck count = %d \n", testG.deckCount[0]);
	printf("player 2 deck count = %d \n", testG.deckCount[1]);
	printf("played cards before: %d \n", testG.playedCardCount);
    printf("Player 1 discard count before: %d\n", testG.discardCount[thisPlayer]);

	printf("---------Playing %s card ---------\n", TESTCARD);
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("Player 1 discard count after: %d\n", testG.discardCount[thisPlayer]);
	if(testG.discardCount[thisPlayer] >3)
		{printf("---Test failed! Discarded too many cards from starting deck----\n");}
	else printf("---Test passed!---\n");

	//modified check for discard pile, we should have some discards, if we have less than 0 or 0 something is wrong 
	printf("Comparing discard count \n");
	if(testG.discardCount[thisPlayer] < G.discardCount[thisPlayer] || testG.discardCount[thisPlayer] == G.discardCount[thisPlayer])
		{printf("---Test failed! Player 1's discard count is incorrect!----\n");}
	else printf("---Test passed!---\n");


	printf("played cards after: %d \n", testG.playedCardCount);

	printf("Player 1 hand:\n");
	int q;
	 for (q = 0; q < numHandCards(&testG); q++)
    {	
    	printf("card %d: %d ", q, handCard(handpos, &testG));
    	printf(" cost %d \n", getCost(testG.hand[thisPlayer][q]));
    	handpos++;
    }
	
	printf("coins = %d, expected = %d\n", testG.coins, G.coins);
	if (testG.coins != G.coins)
		{printf("---Test failed! Coin count modified!\n");}
	else printf("---Test passed!---\n");

	printf("player 1 hand %d \n", testG.handCount[0]);
	printf("player 2 hand %d \n", testG.handCount[1]);
	printf("player 1 deck %d \n", testG.deckCount[0]);
	printf("player 2 deck %d \n", testG.deckCount[1]);
	
	if (testG.handCount[0]+testG.deckCount[0]+testG.discardCount[thisPlayer] != 10)
	{printf("---Test failed! Player 1's hand, deck, and disard have incorrect total!\n");}
	else printf("---Test passed!---\n");

	printf("estate count= %d,  expected = %d \n", testG.supplyCount[estate], G.supplyCount[estate]);
	printf("duchy count= %d ,  expected = %d \n", testG.supplyCount[duchy], G.supplyCount[duchy]);
	printf("province count= %d,  expected = %d \n", testG.supplyCount[province], G.supplyCount[province]);

	if(testG.supplyCount[estate] != G.supplyCount[estate] || testG.supplyCount[duchy] != G.supplyCount[duchy] || testG.supplyCount[province] != G.supplyCount[province])
		{printf("---Test failed, estate cards modified!---\n");}
	else 
		printf("---Test passed!---\n");
	
	printf("\n--------- %s Testing Complete ---------\n\n", TESTCARD);


	return 0;
}