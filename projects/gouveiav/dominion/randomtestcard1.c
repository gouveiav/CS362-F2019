#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


void randomBaronCheck(int choice, int currentPlayer, struct gameState *post) {
	struct gameState pre;
	//make a copy of the gameState to use in comparisons 
	memcpy(&pre, post, sizeof(struct gameState));
	printf("Testing with choice: %d currentPlayer card %d\n", choice, pre.hand[currentPlayer][choice]);

	//calling refactored baron function here
	baronCardEffect(choice, post);

	printf("Testing numBuys: ");
	myAssert(post->numBuys, pre.numBuys + 1); //should PASS
	
	if (choice > 0) {
		int p;


		//testing for added bug
		if (pre.hand[currentPlayer][choice] == estate) {
			printf("Testing for coin bug: ");
			myAssert(post->coins, pre.coins + 4); //Should Fail 

			printf("Testing discardCount: ");
			myAssert(pre.discardCount[currentPlayer] + 1, post->discardCount[currentPlayer]);

			printf("Testing handCount: ");
			myAssert(pre.handCount[currentPlayer] - 1, post->handCount[currentPlayer]);
		}
		else if (p > pre.handCount[currentPlayer]) {
			if (supplyCount(estate, &pre) > 0) {
				printf("Testing supplyCount: ");
				myAssert(post->supplyCount[estate] - 1, pre.supplyCount[estate]);
				if (supplyCount(estate, &pre) == 0) {
					printf("Game supply count == 0");
				}
				else {
					printf("Testing GameOver Bug here");
				}
			}
		}
	}
	else {
		if (supplyCount(estate, &pre) > 0) {
			printf("Testing supplyCount: ");
			myAssert(post->supplyCount[estate] - 1, pre.supplyCount[estate]);
			if (supplyCount(estate, &pre) == 0) {
				printf("Game supplyCount == 0");
			}
			else {
				printf("Testing GameOver Bug here");
			}

		}
	}

}





int main() {

	int i, n, r, p, deckCount, discardCount, handCount;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
				 remodel, smithy, village, baron, great_hall
	};
	struct gameState G;
	int currentPlayer = whoseTurn(&G);

	printf("Random Testing baronCardEffect.\n");

	printf("RANDOM TESTS.\n");
	//SelectStream() from rngs.c sets random number generator
	SelectStream(2);
	//PutSeed() from rngs.c sets state of random number gen
	PutSeed(3);
	//floor is from math.h
	for (n = 0; n < 20; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		//the Random() is from rngs.c return betw 0.0 and 1.0
		p = floor(Random() * 2);
		G.hand[currentPlayer][p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_DECK);
		randomBaronCheck(p, currentPlayer, &G);
	}

	printf("TESTING COMPLETE\n");

	exit(0);

}
