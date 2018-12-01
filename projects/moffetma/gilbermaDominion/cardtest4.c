/*
Max Moffett 
Cardtest4.c - outpost
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "outpost"

int main()
{
	
	int seed = 20;
	int numPlayers = 2;
	int choice1 = 0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	//printf("first test:%d, testG.handCount[testG.whoseTurn])
	printf("--------- Testing Card: %s ---------\n", TESTCARD);
	
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("Player 1 hand count before playing Outpost = %d, expected = %d\n", testG.handCount[testG.whoseTurn], G.handCount[G.whoseTurn]);

	printf("Played cards before playing Outpost = %d \n", testG.playedCardCount);

	printf("Outpost played count before playing Outpost = %d \n", testG.outpostPlayed);
	
	printf("--------- Playing Outpost card ---------\n"); 

	cardEffect(outpost, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("Played cards after: %d , expected = %d \n", testG.playedCardCount, (G.playedCardCount +1));
	if (testG.playedCardCount != G.playedCardCount+1)
		{printf("---Test failed! Wrong # of cards in played pile!---\n");}
	else printf("---Test passed!---\n"); 

	printf("Player 1 hand count = %d, expected = %d\n", testG.handCount[testG.whoseTurn],  G.handCount[G.whoseTurn] -1);
	if (testG.handCount[testG.whoseTurn] != G.handCount[G.whoseTurn] -1)
		{printf("---Test failed! Player 1's hand count incorrect!---\n");}

	printf("Player 2 hand count =%d, expected = %d \n", testG.handCount[1], G.handCount[1]);
	if (testG.handCount[1] != G.handCount[1])
		{printf("Test failed, Player 2's hand modified!\n");}
	else printf("Test passed!\n");

	printf("Game state Outpost played count = %d, expected = %d\n", testG.outpostPlayed, G.outpostPlayed + 1);
	if (testG.outpostPlayed != G.outpostPlayed + 1)
	{printf("---Test failed! Incorrect Outpost counter!---\n");}
	else printf("---Test passed!---\n");

	printf("--------- %s Testing Complete ---------\n\n", TESTCARD);
	
	return 0;
}