#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


int main(int argc, char** argv) {


	printf("---\nBegin Testing Bug #4 (isGameOver()):\n---\n");

	struct gameState G;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
		 remodel, smithy, salvager, sea_hag, treasure_map
	};
	initializeGame(3, k, 48, &G);
	G.supplyCount[salvager] = 0;
	G.supplyCount[sea_hag] = 0;
	G.supplyCount[treasure_map] = 0;

	printf("Last 3 supply piles set to 0, testing isGameOver()\n");

	int test = isGameOver(&G);
	printf("isGameOver expected outcome: 1 || Actual outcome: %d\n", test);

	printf("2/3 of the Last 3 supply piles set to 0,testing isGameOver()\n");
	G.supplyCount[adventurer] = 0;
	G.supplyCount[salvager] = 25;
	printf("isGameOver expected outcome: 1 || Actual outcome: %d\n", test);

	printf("1/3 of the Last 3 supply piles set to 0,testing isGameOver()\n");
	test = isGameOver(&G);
	G.supplyCount[council_room] = 0;
	G.supplyCount[sea_hag] = 25;
	printf("isGameOver expected outcome: 1 || Actual outcome: %d\n", test);

	printf("Test Completed!\n");
	printf("\n");
	return 0;
}
