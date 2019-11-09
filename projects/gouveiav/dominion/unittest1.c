#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


//Unit test for baron card
int testBaronCardEffect(int choice, struct gameState *post) {
	struct gameState pre;
	//make a copy of the gameState to use in comparisons 
	memcpy(&pre, post, sizeof(struct gameState));

int currentPlayer = whoseTurn(&post);
int currentBuys = post->numBuys;

}



int main() {
	int i, n, r, p,supplyCount, deckCount, discardCount, handCount, choice;

	int k[10] = { adventurer, council_room, feast, gardens, mine,
				 remodel, smithy, village, baron, great_hall
	};
	//making a game to test
	struct gameState G;

	printf("Testing baronCardEffect Function.\n");
	






}

