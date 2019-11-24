#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//Unit test for mimion card
void testingMinionCardEffect(int choice1, int choice2, struct gameState *post, int handPos, int currentPlayer) {
	struct gameState pre;
	int i;
	//make a copy of the gameState to use in comparisons 
	memcpy(&pre, post, sizeof(struct gameState));
	printf("Testing with choice1: %d  choice2: %d\n", choice1, choice2);
	//set pre to players handCount to 5
	
	//calling refactored minion function here
	minionEffect(choice1, choice2, post, handPos, currentPlayer);
	
	printf("Testing numActions: ");
	myAssert(post->numActions, pre.numActions + 1);//should PASS

	if (choice1) {

		printf("Testing for choice1 coin: ");
		myAssert(post->coins, pre.coins +2); 
		printf("Testing choice 1 currentPlayer handCount: ");
		myAssert(post->handCount[currentPlayer], pre.handCount[currentPlayer] - 1);
		for (i = 0; i < pre.numPlayers; i++)
		{
				if (i != currentPlayer)
				{
					printf("Testing choice1 Other players handCount: ");
					myAssert(post->handCount[i], pre.handCount[i]); 
				}
		}
	}
	else if (choice2) {
		printf("Testing for choice2 coin: ");
		myAssert(post->coins, pre.coins); 
		printf("Testing currentPlayer handCount: ");
		myAssert(post->handCount[currentPlayer], 4);
		
		for (i = 0; i < pre.numPlayers; i++)
		{
			if (i != currentPlayer)
			{
				if (pre.handCount[i] > 4) {
					printf("Testing Choice2 Other players handCount >4: ");
					myAssert(post->handCount[i], 4); 
				}
				else {
					printf("Testing Choice2 Other players handCount <4: ");
					myAssert(post->handCount[i], pre.handCount[i]);
				}
			}
			printf("Testing currentPlayer handCount: ");
			myAssert(post->handCount[currentPlayer], pre.handCount[currentPlayer] - 1);
		}
	}
	

	


}


int main() {
	int i;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
			 remodel, smithy, village, baron, great_hall
	};
	////making a game to test
	struct gameState G;
	printf("Testing minionCardEffect Function\n");
	int handpos, choice1, choice2;
	
	initializeGame(3, k, 22, &G);
	int currentPlayer = whoseTurn(&G);

	for (i = 0; i < G.numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			G.handCount[i] = 5;

		}
	}
	choice1 = 1;
	choice2 = 0;
	handpos = 4;
	testingMinionCardEffect(choice1, choice2, &G, handpos, currentPlayer);

	choice1 = 0;
	choice2 = 2;
	handpos = 4;
	
	testingMinionCardEffect(choice1, choice2, &G, handpos, currentPlayer);

	for (i = 0; i < G.numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			G.handCount[i] = 4;

		}
	}

	choice1 = 1;
	choice2 = 0;
	handpos = 4;

	testingMinionCardEffect(choice1, choice2, &G, handpos, currentPlayer);
	testingMinionCardEffect(choice1, choice2, &G, handpos, currentPlayer);

	for (i = 0; i < G.numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			G.handCount[i] = 5;

		}
	}

	choice1 = 0;
	choice2 = 1;
	handpos = 4;

	testingMinionCardEffect(choice1, choice2, &G, handpos, currentPlayer);
	printf("Test completed!\n");
	printf("\n");


	return 0;
}

