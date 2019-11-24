#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


void randomTributeCheck(struct gameState *post, int currentPlayer, int nextPlayer) {
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
	myAssert(currentPlayer - 1, nextPlayer);//test should FAIL

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
		else {}
	}

	//getting coverage for the else statement
	else {
		if (pre.deckCount[nextPlayer] == 0) {
			for (i = 0; i < pre.discardCount[nextPlayer]; i++) {
				pre.deck[nextPlayer][i] = pre.discard[nextPlayer][i];
				printf("Testing else deckCount: ");
				myAssert(pre.deckCount[nextPlayer] + 1, post->deckCount[nextPlayer]);//should PASS
				printf("Testing else discardCount: ");
				myAssert(pre.discardCount[nextPlayer] - 1, post->discardCount[nextPlayer]);//should PASS
			}
		}
		tributeRevealedCards[0] = pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1];
		tributeRevealedCards[1] = pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1];
	}
	for (i = 0; i <= 2; i++) {
		if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold) { //Treasure cards
			printf("Testing coins: ");
			myAssert(pre.coins + 2, post->coins);//should PASS
		}
		else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) { //Victory Card Found
			printf("Testing drawCard: ");
			myAssert(pre.handCount[currentPlayer]+2, post->handCount[currentPlayer]);
		}
		else { //Action Card
			printf("Testing numActions bug: ");
			myAssert(pre.numActions + 2, post->numActions); 
			//state->numActions = state->numActions + 3;//bug here was 2
		}

	}

}


int main() {
	srand(time(NULL));
	int players;
	int loopAmount = 200;
	int i, handpos, currentPlayer, nextPlayer, seed;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
				 remodel, smithy, village, baron, great_hall
	};

	struct gameState *G = NULL;

	printf("Random Testing tributeCardEffect.\n");
	G = calloc(loopAmount, sizeof(struct gameState));


	for (i = 0; i < loopAmount; i++)
	{
		players = (rand() % (MAX_PLAYERS - 2 + 1) + 2);
		handpos = (rand() % (26 - 0 + 1));
		seed = (rand() % (26 - 1 + 1) +1);
		initializeGame(players, k, seed, &G[i]);
		
		currentPlayer = whoseTurn(&G[i]);
		nextPlayer = currentPlayer + 1;
		//changed the floor(Random() *max-deck to lower the random pool
		G[i].deck[nextPlayer][G[i].deckCount[nextPlayer] - 1] = handpos;
		G[i].deckCount[nextPlayer] = floor(Random() * 20);
		G[i].discardCount[nextPlayer] = floor(Random() * 20);
		
		randomTributeCheck(&G[i], currentPlayer, nextPlayer);

	}

	free(G);



	printf("ALL TESTS OK\n");
	printf("\n");

	return 0;

}
