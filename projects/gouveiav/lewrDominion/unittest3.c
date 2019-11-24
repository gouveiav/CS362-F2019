#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//Unit test for ambassador card
void testAmbassadorCardEffect(int choice1, int choice2, struct gameState *post, int handPos, int currentPlayer) {
	struct gameState pre;
	int i, j;
	//make a copy of the gameState to use in comparisons 
	memcpy(&pre, post, sizeof(struct gameState));

	printf("Testing with choice1: %d  choice2: %d\n", choice1, choice2);

	//calling refactored minion function here
	ambassadorEffect(choice1, choice2, post, handPos, currentPlayer);
	
	//test that supply count for choosen card was increase by amount being discarded
	int supplyCount = post->supplyCount[post->hand[currentPlayer][choice1]] + choice2;
	printf("Testing supplyCount bug: ");
	myAssert(post->supplyCount[post->hand[currentPlayer][choice1]], supplyCount);//should FAIL
	
	//test that each other player gained the revealed card
	for (i = 0; i < post->numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			printf("Testing player handCount: ");
			myAssert(post->handCount[i], pre.handCount[i] + 1); // should PASS
		}
	}
	//test trashed copies returned to supply
	for (j = 0; j < choice2; j++)
	{
		for (i = 0; i < post->handCount[currentPlayer]; i++)
		{
			if (post->hand[currentPlayer][i] == post->hand[currentPlayer][choice1])
			{
				printf("Testing discard bug: ");
				myAssert(post->handCount[currentPlayer], pre.handCount[currentPlayer] - 1); // should FAIL
			
				break;
			}
		}
	}


}

int main() {
	int k[10] = { adventurer, council_room, feast, gardens, mine,
			 remodel, smithy, village, baron, great_hall
	};
	//making a game to test
	struct gameState G;
	int handpos, choice1, choice2;
	
	printf("Testing ambassadorCardEffect Function\n");


	initializeGame(3, k, 22, &G);
	
	int currentPlayer = whoseTurn(&G);
	choice1 = 1;
	choice2 = 18;
	handpos = 4;
	testAmbassadorCardEffect(choice1, choice2, &G, handpos, currentPlayer);


	printf("Test completed!\n");
	printf("\n");


	return 0;
}

