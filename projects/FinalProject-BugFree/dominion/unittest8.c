#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"

#define STR_FAILED "Failed."
#define STR_PASSED "Passed.\n"

void test_bug_8(char* cardName, int choice1, int choice2, int choice3, int p1card1, int p1card2, int expectedCoins) {
    int k[10] = { adventurer, council_room, salvager, gardens, mine, minion, steward, embargo, baron, tribute };
    struct gameState G;
    int player = 0, bonus = 0;

    // Init
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, 1, &G); // 2 players

    G.handCount[player] = 2;
    G.hand[player][0] = p1card1;
    G.hand[player][1] = p1card2;
    G.whoseTurn = player;
    G.coins = 0;

    cardEffect(p1card1, choice1, choice2, choice3, &G, 0, &bonus);

    printf("%s, Assert bonus coins return %d, gameState->coins unchanged:\n", cardName, expectedCoins);
    if(bonus == expectedCoins && G.coins == 0) {
        printf("%s\n", STR_PASSED);
    } else {
        printf("%s (bonus: %d (%d), G.coins: %d (%d))\n\n", STR_FAILED, bonus, expectedCoins, G.coins, 0);
    }
}

void test_bug_8_tribute() {
    int k[10] = { adventurer, council_room, salvager, gardens, mine, minion, steward, embargo, baron, tribute };
    struct gameState G;
    int player = 0, bonus = 0, nextPlayer = 1;

    // Init
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, 1, &G); // 2 players

    G.handCount[player] = 1;
    G.hand[player][0] = tribute;
    G.whoseTurn = player;
    G.coins = 0;

    // Player 2 deck {copper, curse, curse}
    G.deckCount[nextPlayer] = 3;
    G.deck[nextPlayer][0] = copper;
    G.deck[nextPlayer][1] = curse;
    G.deck[nextPlayer][2] = curse;


    cardEffect(tribute, -1, -1, -1, &G, 0, &bonus);

    int expectedCoins = 2;
    printf("Tribute, Assert bonus coins return %d, gameState->coins unchanged:\n", expectedCoins);
    if(bonus == expectedCoins && G.coins == 0) {
        printf("%s\n", STR_PASSED);
    } else {
        printf("%s (bonus: %d (%d), G.coins: %d (%d))\n\n", STR_FAILED, bonus, expectedCoins, G.coins, 0);
    }
}

int main(int argc, char** argv) {
	printf("---\nBegin Testing Bug #8:\n");
    test_bug_8("Embargo",
        -1, -1, -1,
        embargo, curse,
        2
    );

    test_bug_8("Baron",
        1, -1, -1,
        baron, estate,
        4
    );

    test_bug_8("Minion",
        1, 0, -1,
        minion, curse,
        2
    );

    test_bug_8("Steward",
        2, -1, -1,
        steward, curse,
        2
    );

    test_bug_8("Salvager",
        estate, -1, -1,
        salvager, estate,
        2
    );

    test_bug_8_tribute();

	printf("Test Completed!\n");
	printf("\n");
	return 0;
}
