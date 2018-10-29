/*
Max Moffett 
Unittest4.c getCost
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
	printf("--------- Testing getCost() ---------\n\n");

	printf("Testing curse: \n");
	
	int curse_test = getCost(curse);

	printf("value returned: %d    value expected: 0\n", curse_test);
	if (curse_test != 0)
		{printf("---Test failed! Expected value of 0!---\n");}
	else printf("---Test passed!---\n");


	printf("Testing feast: \n");
	
	int feast_test = getCost(feast);

	printf("value returned: %d    value expected: 4\n", feast_test);
	if (feast_test != 4)
		{printf("---Test failed! Expected value of 4!---\n");}
	else printf("---Test passed!---\n");

	printf("Testing mine: \n");
	
	int mine_test = getCost(mine);

	printf("value returned: %d    value expected: 5\n", mine_test);
	if (mine_test != 5)
		{printf("---Test failed! Expected value of 5!---\n");}
	else printf("---Test passed!---\n");

	printf("Testing outpost: \n");
	
	int outpost_test = getCost(outpost);

	printf("value returned: %d    value expected: 5\n", outpost_test);
	if (outpost_test != 5)
		{printf("---Test failed! Expected value of 5!---\n");}
	else printf("---Test passed!---\n");

	return 0;
}