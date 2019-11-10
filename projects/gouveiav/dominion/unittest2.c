#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//Unit test for mimion card
void testingMinionCardEffect(int choice1, int choice2, struct gameState *post, int handPos) {
	struct gameState pre;
	int i;
	//make a copy of the gameState to use in comparisons 
	memcpy(&pre, post, sizeof(struct gameState));
	int currentPlayer = whoseTurn(post);
	printf("Testing with choice1: %d  choice2: %d\n", choice1, choice2);

	for (i = 0; i < post->numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			post->handCount[i] = 5;
			
		}
	}
	//calling refactored minion function here
	minionCardEffect(choice1, choice2, post, handPos);
	for (i = 0; i < post->numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			printf("Testing player handCount bug: ");
			myAssert(post->handCount[i], 4); // should FAIL
		}
	}


	printf("Testing numActions: ");
	myAssert(post->numActions, pre.numActions + 1);//should PASS
	
	printf("Testing for init coin bug: ");
	myAssert(post->coins, pre.coins); // should FAIL
	
	if (choice1) {
		printf("Testing for choice1 coin bug: ");
		myAssert(post->coins, pre.coins +2); // should FAIL 
		//due to init bug this will FAIL when in it will pass
		//when init bug is fixed.
	}
	
	for (i = 0; i < post->numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			post->handCount[i] = 7;

		}
	}
	//calling refactored minion function here
	minionCardEffect(choice1, choice2, post, handPos);
	for (i = 0; i < post->numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			printf("Testing player handCount bug: ");
			myAssert(post->handCount[i], 4); // should PASS
		}
	}


}


int main() {
	
	int k[10] = { adventurer, council_room, feast, gardens, mine,
			 remodel, smithy, village, baron, great_hall
	};
	////making a game to test
	struct gameState G;
	printf("Testing minionCardEffect Function\n");
	int handpos, choice1, choice2;
	
	initializeGame(3, k, 22, &G);
	   
	choice1 = 1;
	choice2 = 0;
	handpos = 4;
	testingMinionCardEffect(choice1, choice2, &G, handpos);


	choice1 = 0;
	choice2 = 1;
	handpos = 4;
	
	testingMinionCardEffect(choice1, choice2, &G, handpos);

	printf("Test completed!\n");
	printf("\n");


	return 0;
}

