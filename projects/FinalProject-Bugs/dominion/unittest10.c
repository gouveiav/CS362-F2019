#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"

#define STR_FAILED "Failed."
#define STR_PASSED "Passed.\n"


void test_bug_10() {
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, ambassador };
    struct gameState G;
    int player = 0, bonus = 0, ret = 0;

    // Init
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, 1, &G); // 2 players

    // Discard 2 scenario
    G.handCount[player] = 4;
    G.hand[player][0] = ambassador;
    G.hand[player][1] = estate; // choice1
    G.hand[player][2] = estate; // Discarded
    G.hand[player][3] = estate; // Discarded
    G.whoseTurn = player;

    // choice1 = index of selected card
    // choice2 = amount of selected to discard
    ret = cardEffect(ambassador, 1, 2, -1, &G, 0, &bonus);

    // Check buys
    printf("Ambassador, Assert return value not -1, for 2 discards:\n");
    if(ret != -1) {
        printf("%s\n", STR_PASSED);
    } else {
        printf("%s (returned: %d)\n\n", STR_FAILED, ret);
    }

    // Discard 1 scenario
    G.handCount[player] = 3;
    G.hand[player][0] = ambassador;
    G.hand[player][1] = estate; // choice1
    G.hand[player][2] = estate; // Discarded
    G.whoseTurn = player;
    ret = cardEffect(ambassador, 1, 1, -1, &G, 0, &bonus);

    printf("Ambassador, Assert return value not -1, for 1 discard:\n");
    if(ret != -1) {
        printf("%s\n", STR_PASSED);
    } else {
        printf("%s (returned: %d)\n\n", STR_FAILED, ret);
    }
}

int main(int argc, char** argv) {

	printf("---\nBegin Testing Bug #10:\n");
	test_bug_10();

	printf("Test Completed!\n");
	printf("\n");
	return 0;
}
