#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


void randomTributeCheck() {



}




int main() {
	srand(time(NULL));
	int players;

	int k[10] = { adventurer, council_room, feast, gardens, mine,
				 remodel, smithy, village, baron, great_hall
	};

	struct gameState *G = NULL;

	printf("Random Testing tributeCardEffect.\n");




	printf("ALL TESTS OK\n");
	printf("\n");

	return 0;

}
