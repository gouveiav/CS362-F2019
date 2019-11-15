#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


void randomMinionCheck(int choice1, int choice2, struct gameState *post, int handPos) {
	struct gameState pre;
	int i;
	//make a copy of the gameState to use in comparisons 
	memcpy(&pre, post, sizeof(struct gameState));
	int currentPlayer = whoseTurn(post);
	printf("Testing with choice1: %d  choice2: %d\n", choice1, choice2);
	printf("HandPose: %d\n", handPos);
	
	//calling refactored minion function here
	minionCardEffect(choice1, choice2, post, handPos);
	
	printf("Testing numActions: ");
	myAssert(post->numActions, pre.numActions + 1); //should PASS

	if (choice1) {
		printf("Testing for coin bug: ");
		myAssert(post->coins, pre.coins + 2); // should FAIL
	}
	else if (choice2) {
		printf("Testing for coin bug: ");
		myAssert(post->coins, pre.coins); // should FAIL
		
		//currentPlayer discarded hand and drew 4
		printf("Testing currentPlayer handCount: ");
		myAssert(post->handCount[currentPlayer], 4);

		for (i = 0; i < pre.numPlayers; i++)
		{
			if (i != currentPlayer)
			{
				if (pre.handCount[i] > 4) {
					printf("Testing player handCount bug: ");
					myAssert(post->handCount[i], 4); // should Mix FAIL
				}
				else {
					printf("Testing player handCount bug: ");
					myAssert(post->handCount[i], pre.handCount[i]); // should Mix FAIL
				}
			}
			

		}

	}

}

int main() {
	srand(time(NULL));
	int i, j;
	int players;
	int loopAmount = 20;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
				 remodel, smithy, village, baron, great_hall
	};

	struct gameState *G = NULL;
	int handpos, choice1, choice2;
	printf("Random Testing minionCardEffect.\n");
	
	G = calloc(loopAmount, sizeof(struct gameState));


	for (i = 0; i < loopAmount; i++)
	{
		players = (rand() % (MAX_PLAYERS - 2 + 1) + 2);
		handpos = (rand() % (26 - 0 + 1));
		initializeGame(players, k, handpos, &G[i]);//handpos used for seed number
			choice1 = floor(Random() * 2); //0 or 1
			if (choice1 == 0) {
				choice2 = 1;
			}
			else {
				choice2 = 0;
			}

		for (j = 0; j < players; j++) {
			G[i].handCount[j] = floor(Random() * MAX_HAND);

		}
		
		randomMinionCheck(choice1, choice2, &G[i], handpos);
	
	}
	
	free(G);
	printf("ALL TESTS OK\n");
	printf("\n");

	return 0;

}
