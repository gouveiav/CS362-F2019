#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"

#define STR_FAILED "Failed."
#define STR_PASSED "Passed.\n"



void test_bug_9(char* assertMsg, int p2card1, int p2card2, int expectedCoinGain, int expectedActGain, int expectedDrawGain) {

    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, tribute };
    struct gameState G;
    int player = 0, bonus = 0;

    // Init
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, 1, &G); // 2 players

    // Player 1 hand = {tribute}
    G.handCount[player] = 1;
    G.hand[player][0] = tribute;

    // Player 2 deck = {curse, curse}
    G.handCount[player] = 2;
    G.hand[player][0] = p2card1;
    G.hand[player][1] = p2card2;

    // State setup
    G.whoseTurn = player;
    G.coins = 0;
    G.numActions = 1;
    G.deckCount[player] = 0;

    expectedCoinGain += bonus;
    expectedActGain += G.numActions;
    expectedDrawGain += G.deckCount[player];

    cardEffect(tribute, -1, -1, -1, &G, 0, &bonus);

    // Check +0 everything
    printf("%s", assertMsg);
    if(bonus == expectedCoinGain && G.numActions == expectedActGain && G.deckCount[player] == expectedDrawGain) {
        printf("%s\n", STR_PASSED);
    } else {
        printf("%s (coins: %d (%d), numActions: %d (%d), deckCount[player]: %d (%d))\n\n",
            STR_FAILED,
            bonus,
            expectedCoinGain,
            G.numActions,
            expectedActGain,
            G.deckCount[player],
            expectedDrawGain
        );
    }
}

int main(int argc, char** argv) {


	printf("---\nBegin Testing Bug #9:\n---\n");

    // {curse, curse}
    test_bug_9(
        "For curses in player 2's deck, Assert +0 actions, cards, and coins:\n",
        curse, curse,
        0, 0, 0
    );

    // {copper, copper}
    test_bug_9(
        "For duplicate treasures in player 2's deck, Assert +2 coins; +0 cards and actions:\n",
        copper, copper,
        2, 0, 0
    );

    // {baron, baron}
    test_bug_9(
        "For duplicate actions in player 2's deck, Assert +2 actions; +0 cards and coins:\n",
        baron, baron,
        0, 2, 0
    );

    // {estate, estate}
    test_bug_9(
        "For duplicate victories in player 2's deck, Assert +2 cards; +0 coins and actions:\n",
        estate, estate,
        0, 0, 2
    );

    // {baron, mine}
    test_bug_9(
        "For unique actions in player 2's deck, Assert +4 actions; +0 cards and coins:\n",
        baron, mine,
        0, 4, 0
    );


	printf("Test Completed!\n");
	printf("\n");
	return 0;
}
