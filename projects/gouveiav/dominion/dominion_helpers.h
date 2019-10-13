#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state,
                int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3,
               struct gameState *state, int handPos, int *bonus);

int baronCardEffect(int choice1, struct gameState *state);
int minonCardEffect(int choice1, int choice2, struct gameState *state, int handPos);
int ambassadorCardEffect(int choice1, int choice2, struct gameState *state, int handPos);
int tributeCardEffect(struct gameState *state);
int mineCardEffect(int choice1, int choice2, struct gameState *state, int handPos);
#endif
