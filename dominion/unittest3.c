/*
Max Moffett 
unittest3.c - updateCoins
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
	int bonus = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	
	printf("----------------- Testing updateCoins----------------\n");
	
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("Random copper value in first hand: %d \n", testG.coins);

	if (testG.coins > 1 && testG.coins < 6)
		{printf("----Test passed!----\n");}
	else 
		printf("----Test failed, invalid value for first hand!----\n");
	//testG.coins=0;
	//printf("Set coins to zero : %d \n", testG.coins);

	testG.hand[0][0] = gold; 
	testG.hand[0][1] = gold; 
	testG.hand[0][2] = gold; 
	testG.hand[0][3] = gold; 
	testG.hand[0][4] = gold; 

	updateCoins(0, &testG, bonus);

	printf("5 gold cards value after updateCoins: %d \n", testG.coins);
	if (testG.coins == 15)
		{printf("----Test passed!----\n");}
	else 
		printf("----Test failed, expected 15!----\n");

	testG.hand[0][0] = silver; 
	testG.hand[0][1] = silver; 
	testG.hand[0][2] = silver; 
	testG.hand[0][3] = silver; 
	testG.hand[0][4] = silver; 

	updateCoins(0, &testG, bonus);

	printf("5 silver cards value after updateCoins: %d \n", testG.coins);
	
	if (testG.coins == 10)
		{printf("----Test passed!----\n");}
	else 
		printf("----Test failed, expected 10!----\n");

	testG.hand[0][0] = copper; 
	testG.hand[0][1] = copper; 
	testG.hand[0][2] = copper; 
	testG.hand[0][3] = copper; 
	testG.hand[0][4] = copper; 

	updateCoins(0, &testG, bonus);

	printf("5 copper cards value after updateCoins: %d \n", testG.coins);

	if (testG.coins == 5)
		{printf("----Test passed!----\n");}
	else 
		printf("----Test failed, expected 5!----\n");

	testG.hand[0][0] = smithy; 
	testG.hand[0][1] = smithy; 
	testG.hand[0][2] = smithy; 
	testG.hand[0][3] = smithy; 
	testG.hand[0][4] = smithy; 

	updateCoins(0, &testG, bonus);

	printf("5 smithy cards value after updateCoins: %d \n", testG.coins);

	if (testG.coins == 0)
		{printf("----Test passed!----\n");}
	else 
		printf("----Test failed, expected 0!----\n");

	printf("----------------- Testing updateCoins Complete----------------\n");

	return 0; 
}
