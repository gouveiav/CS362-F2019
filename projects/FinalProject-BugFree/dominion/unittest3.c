#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"


void testRemodelCardEffect(int card, int choice1, int choice2, struct gameState *post, int handPos, int currentPlayer) {
	struct gameState pre;
	int choice3 = 0; int i; int count = 0;
	int *bonus = 0;
	int j = pre.hand[currentPlayer][choice1];
	
	//make a copy of the gameState to use in comparisons 
	memcpy(&pre, post, sizeof(struct gameState));

	printf("Testing with choice1: %d  choice2: %d\n", choice1, choice2);
	//calling cardEffect function with 12 = remodel card
	cardEffect(card, choice1, choice2, choice3, post, handPos, bonus);
	
	

	for (i = 0; i < pre.handCount[currentPlayer]; i++) {
		if (post->hand[currentPlayer][i] == choice2) {
			count++;
		}
	
	}
	printf("Testing for Added card: ");
	myAssert(count, 1);
	count = 0;

	/*if ((getCost(j) + 2) > getCost(choice2))
	{
		printf("Testing Cost Values: ");
		myAssert((getCost(j) + 1), getCost(choice2));
	}*/

}

int main(int argc, char** argv) {
	int choice1, choice2;
	int currentPlayer;
	int handPos = 4;
	int card = 12;//remodel card
	int k[10] = { adventurer, council_room, feast, gardens, mine,
			 remodel, smithy, village, baron, great_hall
	};
	//making a game to test
	struct gameState G;

	printf("Testing Bug3.\n");
	//when remodel=12 is played if forces you to trash
	//a card from your hand, and Gain a card costing Up to 
	//2 more.
	initializeGame(3, k, 22, &G);
	currentPlayer = whoseTurn(&G);

	choice1 = 13;//smithy cost4
	choice2 = 17;//minion cost5
	G.hand[currentPlayer][choice1] = smithy;
	testRemodelCardEffect(card, choice1, choice2, &G, handPos, currentPlayer);

	choice1 = 13;//smithy cost4
	choice2 = 2;//duchy cost5
	G.hand[currentPlayer][choice1] = smithy;
	testRemodelCardEffect(card, choice1, choice2, &G, handPos, currentPlayer);

	choice1 = 20;//ambass cost3
	choice2 = 15;//duchy cost4
	G.hand[currentPlayer][choice1] = ambassador;
	testRemodelCardEffect(card, choice1, choice2, &G, handPos, currentPlayer);

	printf("Test Completed!\n");
	printf("\n");
	return 0;
}

