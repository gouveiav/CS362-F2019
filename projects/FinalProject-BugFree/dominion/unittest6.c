#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char** argv) {


	printf("---\nBegin Testing Bug #6 (cardEffect() for feast):\n---\n");
	int result;

	struct gameState G;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
	 remodel, smithy, salvager, sea_hag, treasure_map
	};
	initializeGame(3, k, 48, &G);

	G.coins = 1;

	printf("Setting coins to 1, calling cardEffect() for feast\n");
	result = cardEffect(feast, silver, 0, 0, &G, 0, 0);



	printf("Coins after feast expected value 1 || actual coins = %d\n", G.coins);

	printf("Test Completed!\n");
	printf("\n");
	return 0;
}
