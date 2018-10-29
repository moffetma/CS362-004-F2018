/*
Max Moffett 
Unittest2.c - shuffle
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 50;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing shuffle()----------------\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;

	printf("Player %d deck count: %d \n", thisPlayer, testG.deckCount[thisPlayer]);
    printf("pre-shuffle order:\n"); 

    int p;
    for (p = 0; p < testG.deckCount[thisPlayer]; p++)
    {	
    	printf(" card %d:  %d \n", p+1 , testG.deck[thisPlayer][p]);
    	handpos++;
    }
  	
  	int pre_shuffle_count = testG.deckCount[thisPlayer];
  	
   shuffle(thisPlayer, &testG);

  	int post_shuffle_count = testG.deckCount[thisPlayer]; 

  	printf("Player %d post-shuffle deck count: %d \n", thisPlayer, testG.deckCount[thisPlayer]);
  	printf("post-shuffle order:\n");
	 for (p = 0; p < testG.deckCount[thisPlayer]; p++)
    {	
    	printf(" card %d : %d \n", p+1 , testG.deck[thisPlayer][p]); 
    	handpos++;
    }
    if (post_shuffle_count != pre_shuffle_count)
    	{printf("---Test failed! Deck count has changed!---\n");}
    else printf("--- Test passed! Same deck count verified!---\n"); 

    int q;
    int same_count = 0; 

    for (q =0; q < testG.deckCount[thisPlayer]; q++) 
   	{
   		if(testG.deck[thisPlayer][q] == G.deck[thisPlayer][q])
   			{same_count++;} //if we have more than 4 matches the cards were likely not shuffled 
   	}

   	if (same_count > 4 )
   	{
   		printf("---Test failed! Cards are in the same order as before shuffling!---\n");
   	}
   	else 
   		printf("---Test passed! Cards were shuffled!---\n"); 

	printf("\n ---------Shuffle testing complete---------\n\n");


	return 0;
}