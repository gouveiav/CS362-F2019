#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char** argv) {

	int i;

	//int expectedScore = 11;
	int testScore;

	struct gameState G;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
	 remodel, smithy, salvager, sea_hag, treasure_map
	};
	initializeGame(3, k, 48, &G);
	G.handCount[0] = 3;
	G.discardCount[0] = 3;
	G.deckCount[0] = 5;

	for (i = 0; i < 3; ++i)
	{
		G.hand[0][i] = estate;
		G.discard[0][i] = estate;
		G.deck[0][i] = estate;
	}

	G.deck[0][3] = estate;
	G.deck[0][4] = estate;
	testScore = scoreFor(0, &G);

	printf("---\nBegin Testing Bug #5 (scoreFor()):\n---\n");

	printf("Expected score for player 0: 11 || Actual score: %d\n", testScore);






	printf("Test Completed!\n");
	printf("\n");
	return 0;
}
