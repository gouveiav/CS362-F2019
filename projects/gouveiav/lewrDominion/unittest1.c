#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


//Unit test for baron card
void testBaronCardEffect(int choice, struct gameState *post, int currentPlayer) {
	struct gameState pre;
	//make a copy of the gameState to use in comparisons 
	memcpy(&pre, post, sizeof(struct gameState));

	printf("Testing with choice: %d\n", choice);
	
	//calling refactored baron function here
	baronEffect(choice, post, currentPlayer);

	printf("Testing numBuys: ");
	myAssert(post->numBuys, pre.numBuys + 1);

	//testing for added bug
	if (pre.hand[currentPlayer][choice] == estate) {
		printf("Testing coin: ");
		myAssert(post->coins, pre.coins + 4); //found bug and failed
		
		printf("Testing handCount bug: ");
		myAssert(post->handCount[currentPlayer]+1, pre.handCount[currentPlayer]);
	}
	else if (choice > pre.handCount[currentPlayer]) {
		if (supplyCount(estate, &pre) > 0) {
			printf("Testing supply[estate]count bug ");
			myAssert(post->supplyCount[estate]+1, pre.supplyCount[estate]);
		}
	
	}
	// verify that your asserts pass, for the bugs your asserts may fail
	
	
	

}

int main() {
	int p;
	//int handCount = 3;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
				 remodel, smithy, village, baron, great_hall
	};
	//making a game to test
	struct gameState G;

	printf("Testing baronCardEffect Function.\n");
	// set the game state ...this causes seg fault so commented out
	//memset(&G, 23, sizeof(struct gameState)); 

	// initialize a new game  //int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed,
	//	struct gameState *state)
	initializeGame(2, k, 24, &G); 
	//assert(r == 0);
	int currentPlayer = whoseTurn(&G);

	// set any other variables
	p = 6;
	
	// call refactored function
	testBaronCardEffect(p, &G, currentPlayer);
	
	// adjust the state of your variables to continue testing the function

	//to increase coverage the baron card effect has one main if/else and 3 nested ifs
	//changed p value to activated different if statements
	p = 0;

	G.hand[currentPlayer][p] = estate;
	testBaronCardEffect(p, &G, currentPlayer);
	
	p = 1;
	testBaronCardEffect(p, &G, currentPlayer);
	
	//increase coverage by activating the "else if"
	p = ((int*)G.handCount[currentPlayer]) + 1;
	testBaronCardEffect(p, &G, currentPlayer);

	printf("Test completed!\n");
	printf("\n");


	return 0;
}

