#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"




//Unit test for mine Card
void testMineCardEffect(int card, int choice1, int choice2, struct gameState *post, int handPos, int currentPlayer) {
	struct gameState pre;
	int choice3=0;
	int i;
	int *bonus = 0;
	//make a copy of the gameState to use in comparisons 
	memcpy(&pre, post, sizeof(struct gameState));

	printf("Testing with choice1: %d  choice2: %d\n", choice1, choice2);

	//calling cardEffect function with 11 = mine card
	cardEffect(card, choice1, choice2, choice3, post, handPos, bonus);

	if ((getCost(pre.hand[currentPlayer][choice1]) + 3) > getCost(choice2))
	{
		printf("Third if: return -1\n"); exit(1);
	}
	

	for (i = 0; i < pre.handCount[currentPlayer]; i++)
	{
		if (pre.hand[currentPlayer][i] == pre.hand[currentPlayer][choice1])
		{
			printf("Card trashed check\n");
			myAssert(pre.supplyCount[choice1]+1, post->supplyCount[choice1]);
			break;
		}
	}
	

}

int main() {
	int choice1, choice2;
	int treasureCard = 26;
	int copper = 4;
	int gold = 6;
	int handPos = 3;
	int card = 11; //mine card
	int k[10] = { adventurer, council_room, feast, gardens, mine,
			 remodel, smithy, village, baron, great_hall
	};

	//making a game to test
	struct gameState G;
	printf("Testing Bug 1.\n");
	printf("Testing mine Case in cardEffect Function\n");
	//trash a treasure and gain a T up to 3 more
	initializeGame(3, k, 22, &G);

	int currentPlayer = whoseTurn(&G);

	//testing mine case w/choice1 between 4 and 6 
	//testing mine case w/choice2 between 0 and 26
	choice1 = 3;
	choice2 = gold;
	testMineCardEffect(card, choice1, choice2, &G, handPos, currentPlayer);

	
	

	printf("Test completed!\n");
	printf("\n");


	return 0;
}

