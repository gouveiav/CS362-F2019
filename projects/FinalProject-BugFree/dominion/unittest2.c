#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


//Unit test for mine Card
void testMineCardEffect(int card, int choice1, int choice2, struct gameState *post, int handPos, int currentPlayer) {
	struct gameState pre;
	int choice3 = 0;
	int *bonus = 0;
	//make a copy of the gameState to use in comparisons
	memcpy(&pre, post, sizeof(struct gameState));

	printf("Testing with choice1: %d  choice2: %d\n", choice1, choice2);

	//calling cardEffect function with 11 = mine card
	cardEffect(card, choice1, choice2, choice3, post, handPos, bonus);

	int j = pre.hand[currentPlayer][choice1];
	//printf("jjjjjjjj:%d\n", j);
	//printf("cost of choice1 +3: %d ", getCost(choice1) + 3);
	//printf("cost of choice1player: %d \n", getCost(j));
	//printf("cost of choice2 %d: \n", getCost(choice2));

	if ( (getCost(j) + 3) > getCost(choice2))
	{
		//trash a treasure card and gain a treasure card costing up to 3 more
		//Treasure cards copper4 value 0, silver5 value 3, gold6 value 6
		printf("Testing Cost Values: ");
		myAssert( (getCost(j)+3), getCost(choice2) );


	}

}

int main() {
	int choice1, choice2;
	int copper = 4; int silver = 5;	int gold = 6;
	int handPos = 3; int card = 11;
	int currentPlayer;

	int k[10] = { adventurer, council_room, feast, gardens, mine,
			 remodel, smithy, village, baron, great_hall
	};
	//making a game to test
	struct gameState G;

	printf("---\nBegin Testing Bug #2:\n---\n");
	//printf("Testing mine Case Getcost\n");

	//trash a treasure and gain a Treasure up to 3
	initializeGame(3, k, 22, &G);

	currentPlayer = whoseTurn(&G);

	//testing mine case w/choice1 between 4 and 6
	//testing mine case w/choice2 between 0 and 26
	choice1 = copper;
	choice2 = copper;
	G.hand[currentPlayer][choice1] = copper;
	testMineCardEffect(card, choice1, choice2, &G, handPos, currentPlayer);

	//choice1 = gold;
	choice2 = gold;
	G.hand[currentPlayer][choice1] = gold;
	testMineCardEffect(card, choice1, choice2, &G, handPos, currentPlayer);
	choice1 = silver;
	choice2 = silver;
	G.hand[currentPlayer][choice1] = silver;
	testMineCardEffect(card, choice1, choice2, &G, handPos, currentPlayer);
	printf("Test completed!\n");
	printf("\n");


	return 0;
}
