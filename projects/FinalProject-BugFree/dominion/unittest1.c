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
	int countChoice1 = 0;
	int countChoice2 = 0;
	//make a copy of the gameState to use in comparisons 
	memcpy(&pre, post, sizeof(struct gameState));
	
	printf("Testing with choice1: %d  choice2: %d\n", choice1, choice2);
	int j = pre.hand[currentPlayer][choice1];
	printf("pre.hand[currentPlayer][choice1]: %d\n", j);
	printf("pre.supplyCount1 %d\n", pre.supplyCount[choice1]);
	printf("pre.supplyCount2 %d\n", pre.supplyCount[choice2]);//40
	printf("pre.handCount %d\n", pre.handCount[currentPlayer]);
	for (i = 0; i < pre.handCount[currentPlayer]; i++)
	{
		if (pre.hand[currentPlayer][i] == pre.hand[currentPlayer][choice1]) {
			countChoice1++;
			
		}
		if (pre.hand[currentPlayer][i] == pre.hand[currentPlayer][choice2]) {
			countChoice2++;
		}
		
	}
	printf("Pre:choice1 found < %d > times in players hand \n", countChoice1);
	printf("Pre:choice2 found < %d > times in players hand \n", countChoice2);

	//calling cardEffect function with 11 = mine card
	cardEffect(card, choice1, choice2, choice3, post, handPos, bonus);
	countChoice1 = 0;
	countChoice2 = 0;
	printf("post.supplyCount1 %d\n", post->supplyCount[choice1]);
	printf("post.supplyCount2 %d\n", post->supplyCount[choice2]);//39 good
	printf("post.handCount %d\n", post->handCount[currentPlayer]);
	for (i = 0; i < post->handCount[currentPlayer]; i++)
	{
		if (post->hand[currentPlayer][i] == post->hand[currentPlayer][choice1]) {
			countChoice1++;
		}
		if (post->hand[currentPlayer][i] == post->hand[currentPlayer][choice2]) {
			countChoice2++;
		}

	}
	printf("Post:choice1 found < %d > times in players hand \n", countChoice1);
	printf("Post:choice2 found < %d > times in players hand \n", countChoice2);

	for (i = 0; i < pre.handCount[currentPlayer]; i++)
	{
		if (pre.hand[currentPlayer][i] == pre.hand[currentPlayer][choice1])
		{
			printf("Card Trashed Check: ");
			myAssert(pre.supplyCount[choice1], post->supplyCount[choice1]+1);
			break;
		}
	}
	

}

int main() {
	int choice1, choice2;
	int copper = 4;
	int silver = 5;
	int gold = 6;
	int handPos = 4;
	int currentPlayer;
	int card = 11; //mine card
	int k[10] = { adventurer, council_room, feast, gardens, mine,
			 remodel, smithy, village, baron, great_hall
	};

	//making a game to test
	struct gameState G;
	struct gameState G2;
	printf("Testing Bug 1.\n");
	//printf("Testing mine Case in cardEffect Function\n");
	//trash a treasure and gain a T up to 3 more
	initializeGame(3, k, 22, &G);
	currentPlayer = whoseTurn(&G);

	//testing mine case w/choice1 between 4 and 6 
	//testing mine case w/choice2 between 4 and 6
	choice1 = copper;
	choice2 = silver;
	G.hand[currentPlayer][choice1] = copper;
	testMineCardEffect(card, choice1, choice2, &G, handPos, currentPlayer);
	
	initializeGame(2, k, 20, &G2);
	currentPlayer = whoseTurn(&G2);
	choice1 = silver;
	choice2 = gold;
	G.hand[currentPlayer][choice1] = silver;
	testMineCardEffect(card, choice1, choice2, &G2, handPos, currentPlayer);
	
	printf("Test completed!\n");
	printf("\n");


	return 0;
}

