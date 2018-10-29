/*
Max Moffett 
Cardtest1.c - smithy 
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 30;
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
	handpos = 4; 

    printf("player 1 deck count before Smithy played: %d \n", testG.deckCount[0]);
	printf("player 2 deck count before Smithy played: %d \n", testG.deckCount[1]);
	printf("played card count before Smithy played: %d \n", testG.playedCardCount);
	
	printf("--------- Playing Smithy card ---------\n");
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	printf("played cards count after smithy played: %d \n", testG.playedCardCount);
	if (testG.playedCardCount != 1)
		{printf("Test failed, Smithy not added to played cards!\n");}
	else 
		printf("Test passed!\n");

	newCards = 3;

	printf("Player 1 hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	if( testG.handCount[thisPlayer] != (G.handCount[thisPlayer] + newCards - discarded))
		{printf("Test failed, incorrect # of cards in hand!\n");}
	else printf("Test passed!\n");

	printf("Player 1 deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	if (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - newCards + shuffledCards)
		{printf("Test failed, incorrect deck count!\n");}
	else printf("Test passed!\n"); 

	printf("Total coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	if (testG.coins != G.coins)
		{printf("Test failed, coin count modified!\n");}
	else printf("Test passed!\n");

	printf("Player 2 hand count =%d, expected = %d \n", testG.handCount[1], G.handCount[1]);
	if (testG.handCount[1] != G.handCount[1])
		{printf("Test failed, Player 2's hand modified!\n");}
	else printf("Test passed!\n");

	printf("Player 2 deck count =%d , expected = %d\n", testG.deckCount[1], G.deckCount[1]);
	if (testG.deckCount[1] != G.deckCount[1])
		{printf("Test failed, Player 2's deck modified!\n");}
	else printf("Test passed!\n");

	printf("estate count= %d,  expected = %d \n", testG.supplyCount[estate], G.supplyCount[estate]);
	printf("duchy count= %d ,  expected = %d \n", testG.supplyCount[duchy], G.supplyCount[duchy]);
	printf("province count= %d,  expected = %d \n", testG.supplyCount[province], G.supplyCount[province]);

	if(testG.supplyCount[estate] != G.supplyCount[estate] || testG.supplyCount[duchy] != G.supplyCount[duchy] || testG.supplyCount[province] != G.supplyCount[province])
		{printf("Test failed, estate cards modified!\n");}
	else 
		printf("Test passed!\n");

	printf("\n --------- %s Testing Complete ---------\n\n", TESTCARD);


	return 0;
}