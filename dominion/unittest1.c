/*
Max Moffett 
Unittest1.c whoseturn 
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main()
{
	
	int seed = 20;
	int numPlayers = 2;
	int choice1 = 0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0;
	struct gameState G, testG, F, testF;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	//printf("first test:%d, testG.handCount[testG.whoseTurn])
	printf("--------- Testing whoseTurn ---------\n");
	
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	int test_two = whoseTurn(&testG);
	
	printf("Testing %d player game: \n", numPlayers);
	printf("Player %d should go first...\n", test_two);

	if ( test_two == G.whoseTurn)
	{
		printf("---Test passed!---\n");
	}
	else 
		printf("---Test failed, player one not first in test case!---\n");

	numPlayers=4;

	initializeGame(numPlayers, k, seed, &F);
	memcpy(&testF, &F, sizeof(struct gameState));


	int test_four = whoseTurn(&testF);

	printf("Testing %d player game: \n", numPlayers);
	printf("Player %d should go first...\n", test_four); 
	if ( test_four == F.whoseTurn)
	{
		printf("---Test passed!---\n");
	}
	else 
		printf("---Test failed, player one not first in test case!---\n");
	
	printf("--------- whoseTurn testing complete ---------\n");
	return 0;
}