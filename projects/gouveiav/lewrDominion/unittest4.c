#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//Unit test for tribute Card
void testTributeCardEffect(struct gameState *post, int currentPlayer, int nextPlayer) {
	struct gameState pre;
	int i;
	//make a copy of the gameState to use in comparisons 
	memcpy(&pre, post, sizeof(struct gameState));
	int tributeRevealedCards[2] = { -1, -1 };
	
	int sum = (post->discardCount[nextPlayer] + post->deckCount[nextPlayer]);
	printf("Before with deckCount[nextPlayer]: %d\n", post->deckCount[nextPlayer]);
	printf("Before with discardCount[nextPlayer]: %d\n", post->discardCount[nextPlayer]);
	printf("sum Before: %d\n", sum);

	//calling refactored minion function here
	tributeEffect(post, currentPlayer, nextPlayer);
		
	//test nextplayer
	printf("Testing nextplayer bug: ");
	myAssert(currentPlayer + 1, nextPlayer);//test should FAIL
	
	if ((pre.discardCount[nextPlayer] + pre.deckCount[nextPlayer]) <= 1) {
		
		if (pre.deckCount[nextPlayer] > 0) {
			tributeRevealedCards[0] = pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1];
			printf("Testing first \"if\" deckCount: ");
			myAssert(pre.deckCount[nextPlayer], post->deckCount[nextPlayer] + 1);//should PASS

		}
		else if (pre.discardCount[nextPlayer] > 0) {
			tributeRevealedCards[0] = pre.discard[nextPlayer][pre.discardCount[nextPlayer] - 1];
			printf("Testing first \"else if\" discardCount: ");
			myAssert(pre.discardCount[nextPlayer], post->discardCount[nextPlayer] + 1);//should PASS
		}
		else{}
	}

	//getting coverage for the else statement
	else {
		if (pre.deckCount[nextPlayer] == 0) {
			for (i = 0; i < pre.discardCount[nextPlayer]; i++) {
				pre.deck[nextPlayer][i] = pre.discard[nextPlayer][i];
				printf("Testing else deckCount: ");
				myAssert(pre.deckCount[nextPlayer] + 1, post->deckCount[nextPlayer]);//should PASS
				printf("Testing else discardCount: ");
				myAssert(pre.discardCount[nextPlayer] -1, post->discardCount[nextPlayer]);//should PASS
			}
		}
		tributeRevealedCards[0] = pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1];
		tributeRevealedCards[1] = pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1];
	}
	for (i = 0; i <= 2; i++) {
		if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold) { //Treasure cards
			printf("Testing coins: ");
			myAssert(pre.coins, post->coins + 2);//should PASS
		}
		else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) { //Victory Card Found
			printf("Testing drawCard: ");
			myAssert(pre.handCount[currentPlayer], post->handCount[currentPlayer] + 2);
		}
		else { //Action Card
			printf("Testing numActions bug: ");
			myAssert(pre.numActions, post->numActions + 2);
			//state->numActions = state->numActions + 3;//bug here was 2
		}
	
	
	
	}

}

int main() {
	int k[10] = { adventurer, council_room, feast, gardens, mine,
			 remodel, smithy, village, baron, great_hall
	};
	//making a game to test
	struct gameState G;
	initializeGame(3, k, 22, &G);

	printf("Testing tributeCardEffect Function\n");
	
	int currentPlayer = whoseTurn(&G);
	int nextPlayer = currentPlayer + 1;

	//should trigger first if statement then nested if
	G.deckCount[nextPlayer] = 1;
	G.discardCount[nextPlayer] = 0;
	testTributeCardEffect(&G, currentPlayer, nextPlayer);	
	
	//should trigger first if statement then nested else/if
	G.deckCount[nextPlayer] = 0;
	G.discardCount[nextPlayer] = 1;
	testTributeCardEffect(&G, currentPlayer, nextPlayer);
	

	//should trigger first else but no if
	G.deckCount[nextPlayer] = 1;
	G.discardCount[nextPlayer] = 1;
	testTributeCardEffect(&G, currentPlayer, nextPlayer);
	
	//should trigger first else and if
	G.deck[nextPlayer][G.deckCount[nextPlayer] - 1] = 6;
	G.deckCount[nextPlayer] = 0;
	G.discardCount[nextPlayer] = 4;
	testTributeCardEffect(&G, currentPlayer, nextPlayer);

	//adding to test for more coverage
	G.deck[nextPlayer][G.deckCount[nextPlayer] - 1] = 5;
	G.deckCount[nextPlayer] = 5;
	G.discardCount[nextPlayer] = 10;
	testTributeCardEffect(&G, currentPlayer, nextPlayer);

	//adding to test for more coverage trigger main else
	G.deck[nextPlayer][G.deckCount[nextPlayer] - 1] = 4;
	G.deckCount[nextPlayer] = 0;
	G.discardCount[nextPlayer] = 10;
	testTributeCardEffect(&G, currentPlayer, nextPlayer);
	printf("Test completed!\n");
	printf("\n");


	return 0;
}

