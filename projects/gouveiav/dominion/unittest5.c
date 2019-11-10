#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//Unit test for mine Card
void testMineCardEffect(int choice1, int choice2, struct gameState *post, int handPos) {
	struct gameState pre;
	int i;
	//make a copy of the gameState to use in comparisons 
	memcpy(&pre, post, sizeof(struct gameState));
	int currentPlayer = whoseTurn(post);
	printf("Testing with choice1: %d  choice2: %d\n", choice1, choice2);

	//calling refactored function
	mineCardEffect(choice1, choice2, post, handPos);
	if (pre.hand[currentPlayer][choice1] < copper || pre.hand[currentPlayer][choice1] > gold)
	{
		printf("First if: return -1\n");
	}
	//card player wants
	if (choice2 > treasure_map || choice2 < curse) //bugs here//fixed for coverage
	{
		printf("Second if: return -1\n");
	}

	if ((getCost(pre.hand[currentPlayer][choice1]) + 3) > getCost(choice2))
	{
		printf("Third if: return -1\n");
	}
	
	for (i = 0; i < post->handCount[currentPlayer]; i++)
	{
		if (post->hand[currentPlayer][i] == choice2)
		{
			printf("Card added to hand\n");
			break;
		}
	}
	printf("Testing handCount bug: ");
	myAssert(post->handCount[currentPlayer], pre.handCount[currentPlayer]);

}

int main() {
	int choice1, choice2;
	int treasureCard =26;
	int copper = 4;
	int gold = 6;
	int handPos = 3;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
			 remodel, smithy, village, baron, great_hall
	};
	
	//making a game to test
	struct gameState G;
	printf("Testing mineCardEffect Function\n");
	//trash a treasure and gain a T up to 3 more
	initializeGame(3, k, 22, &G);

	int currentPlayer = whoseTurn(&G);

	//testing first if, for valid treasure choice1 4-6
	choice1 = 3;
	G.hand[currentPlayer][choice1] = 3;
	choice2 = gold;
	testMineCardEffect(choice1, choice2, &G, handPos);

	//testing second if, for valid choice2 25-1. bug here will
	//trigger the statement but shouldn't
	choice1 = copper;
	choice2 = gold;
	testMineCardEffect(choice1, choice2, &G, handPos);

	//testing second if, for valid choice2 25-1. bug here will
	//will always return -1 without fix...now should trigger
	choice1 = treasureCard;
	choice2 = gold;
	testMineCardEffect(choice1, choice2, &G, handPos);
	
	//should trigger third if statement to getCost. But wont unless above is fixed
	choice1 = 4;
	G.hand[currentPlayer][choice1] = copper;
	choice2 = 19;
	testMineCardEffect(choice1, choice2, &G, handPos);


	printf("Test completed!\n");
	printf("\n");


	return 0;
}

