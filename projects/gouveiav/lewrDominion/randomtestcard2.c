#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


void randomMinionCheck(int choice1, int choice2, struct gameState *post, int handPos, int currentPlayer) {
	struct gameState pre;
	int i;
	//make a copy of the gameState to use in comparisons 
	memcpy(&pre, post, sizeof(struct gameState));
	
	printf("Testing with choice1: %d  choice2: %d\n", choice1, choice2);
	printf("HandPose: %d\n", handPos);
	
	//calling refactored minion function here
	minionEffect(choice1, choice2, post, handPos, currentPlayer);
	
	printf("Testing numActions: ");
	myAssert(post->numActions, pre.numActions + 1); 

	if (choice1) {
		printf("Testing for coin bug: ");
		myAssert(post->coins, pre.coins + 2); // should FAIL
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
		printf("Testing choice 2 coin: ");
		myAssert(post->coins, pre.coins); // should FAIL
		
		//currentPlayer discarded hand and drew 4
		printf("Testing choice 2 currentPlayer handCount: ");
		myAssert(post->handCount[currentPlayer], 4); //should PASS

		for (i = 0; i < pre.numPlayers; i++)
		{
			if (i != currentPlayer)
			{
				if (pre.handCount[i] > 4) {
					printf("Testing choice 2 Other player handCount > 4: ");
					myAssert(post->handCount[i], 4); // should Mix FAIL
				}
				else {
					printf("Testing choice 2 Other player handCount < 4: ");
					myAssert(post->handCount[i], pre.handCount[i]); // should Mix FAIL
				}
			}
			printf("Testing choice 2 currentPlayer handCount: ");
			myAssert(post->handCount[currentPlayer], 4); //should PASS

		}

	}

}

int main() {
	srand(time(NULL));
	int i, j;
	int players, seed;
	int loopAmount = 20;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
				 remodel, smithy, village, baron, great_hall
	};

	struct gameState *G = NULL;
	int handpos, choice1, choice2;
	printf("Random Testing minionCardEffect.\n");
	
	G = calloc(loopAmount, sizeof(struct gameState));
	int currentPlayer;

	for (i = 0; i < loopAmount; i++)
	{
		players = (rand() % (MAX_PLAYERS - 2 + 1) + 2);
		handpos = (rand() % (26 - 0 + 1));
		seed = (rand() % (26 - 1 + 1) +1);
		initializeGame(players, k, seed, &G[i]);
			choice1 = floor(Random() * 2); //0 or 1
			if (choice1 == 0) {
				choice2 = 1;
			}
			else {
				choice2 = 0;
			}

		for (j = 0; j < players; j++) {
			G[i].handCount[j] = floor(Random() * 20);

		}
		currentPlayer = whoseTurn(&G[i]);
		randomMinionCheck(choice1, choice2, &G[i], handpos, currentPlayer);
	
	}
	
	free(G);
	printf("ALL TESTS OK\n");
	printf("\n");

	return 0;

}
