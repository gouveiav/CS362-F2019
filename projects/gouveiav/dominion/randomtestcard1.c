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
	printf("CurrentPlayer %d \n", currentPlayer);
	//calling refactored baron function here
	baronCardEffect(choice, post);

	printf("Testing numBuys: ");
	myAssert(post->numBuys, pre.numBuys + 1); //should PASS
	
	if (choice > 0) {
		int p = 0;
		int exitloop = 1;
		
		while (exitloop) {
			
			//testing for added bug
			if (pre.hand[currentPlayer][choice] == estate) {
				printf("Testing for coin bug: ");
				myAssert(post->coins, pre.coins + 4); //Should Fail 

				printf("Testing discardCount: ");
				myAssert(pre.discardCount[currentPlayer] + 1, post->discardCount[currentPlayer]);

				printf("Testing handCount: ");
				myAssert(pre.handCount[currentPlayer] - 1, post->handCount[currentPlayer]);
				exitloop = 0;
			}
			else if (p > pre.handCount[currentPlayer]) {
				if (supplyCount(estate, &pre) > 0) {
					printf("Testing supplyCount: ");
					myAssert(post->supplyCount[estate] - 1, pre.supplyCount[estate]);
					if (supplyCount(estate, &pre) == 0) {
						printf("Testing GameOver supplyCount: ");
						myAssert(supplyCount(estate, &pre), 0);
					}
					else {
						printf("Testing GameOver supplyCount bug: ");
						myAssert(supplyCount(estate, &pre), 0);
					
					}
				}
				exitloop = 0;
			}
			else {
				p++;
			}
		}
	}
	else {
		if (supplyCount(estate, &pre) > 0) {
			printf("Testing supplyCount: ");
			myAssert(post->supplyCount[estate] - 1, pre.supplyCount[estate]);
			
			if (supplyCount(estate, &pre) == 0) {
				printf("Testing GameOver supplyCount: ");
				myAssert(supplyCount(estate, &pre), 0);
			}
			else {
				printf("Testing GameOver supplyCount bug: ");
				myAssert(supplyCount(estate, &pre), 0);
			}

		}
	}

}





int main() {
	srand(time(NULL));
	int players = (rand() % (MAX_PLAYERS - 2 + 1) + 2);
	int card;
	int i, p;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
				 remodel, smithy, village, baron, great_hall
	};
	struct gameState G;
	printf("Random Testing baronCardEffect.\n");
	initializeGame(players, k, 24, &G);
	
	int currentPlayer = whoseTurn(&G);
	
	printf("RANDOM TESTS.\n");
	
	//floor is from math.h
	for (i = 0; i < 80; i++) {
		//(rand() % (MAX -MIN +1) +MIN));
		card = (rand() % (26 - 0 + 1));
		p = floor(Random() * 2);
		G.hand[currentPlayer][p] = card;
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		randomBaronCheck(p, currentPlayer, &G);
	}

	printf("TESTING COMPLETE\n");

	exit(0);

}
