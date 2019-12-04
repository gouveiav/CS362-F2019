#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"


#define STR_FAILED "Failed."
#define STR_PASSED "Passed.\n"


void test_bug_7(char* assertStr, int card1, int card2, int card3, int coins, int actions, int drawn) {
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, tribute };
    struct gameState G;
    int player = 0, bonus = 0, ret = 0, nextPlayer = 1;

    // Init
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, 1, &G); // 2 players

    G.handCount[player] = 1;
    G.hand[player][0] = tribute;
    G.whoseTurn = player;

    G.deckCount[nextPlayer] = 3;
    G.deck[nextPlayer][0] = card1;
    G.deck[nextPlayer][1] = card2;
    G.deck[nextPlayer][2] = card3;

    G.coins = 0;
    G.numActions = 1;
    G.deckCount[player] = 0;

    drawn += G.deckCount[player];
    actions += G.numActions;
    coins += bonus;

    ret = cardEffect(tribute, -1, -1, -1, &G, 0, &bonus);

    printf("%s", assertStr);
    if(bonus == coins && G.numActions == actions && G.deckCount[player] == drawn) {
        printf("%s\n", STR_PASSED);
    } else {
        printf("%s (coins: %d (%d), numActions: %d (%d), deckCount[player]: %d (%d))\n\n",
            STR_FAILED,
            bonus,
            coins,
            G.numActions,
            actions,
            G.deckCount[player],
            drawn
        );
    }
}

int main(int argc, char** argv) {
	printf("---\nBegin Testing Bug #7:\n");
    test_bug_7(
        "Tribute, Player 2 deck = {copper, copper, silver}, Assert +4 coins; +0 actions and cards:\n",
        copper, copper, silver,
        4, 0, 0
    );

    test_bug_7(
        "Tribute, Player 2 deck = {mine, baron, remodel}, Assert +4 actions; +0 coins and cards:\n",
        mine, baron, remodel,
        0, 4, 0
    );

    test_bug_7(
        "Tribute, Player 2 deck = {estate, estate, duchy}, Assert +4 cards; +0 coins and actions:\n",
        estate, estate, duchy,
        0, 0, 4
    );

	printf("Test Completed!\n");
	printf("\n");
	return 0;
}
