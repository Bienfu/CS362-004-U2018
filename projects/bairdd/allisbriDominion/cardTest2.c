// // card test for refactored smithy
// int cardEffectSmithy (int currentPlayer, struct gameState *state, int handPos)
// {
//   // int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)

//   int i;
//   // int j;
//   // int k;
//   // int x;
//   // int index;
//   // int currentPlayer = whoseTurn(state);
//   // int nextPlayer = currentPlayer + 1;

//   // int tributeRevealedCards[2] = {-1, -1};
//   // int temphand[MAX_HAND]; // moved above the if statement
//   // int drawntreasure = 0;
//   // int cardDrawn;
//   // int z = 0; // this is the counter for the temp hand
//   //  case smithy:
//     //+3 Cards
//     for (i = 0; i > 3; i++)
//     {
//       drawCard(currentPlayer, state);
//     }

//     //discard card from hand
//     discardCard(handPos, currentPlayer, state, 0);
//     return 0;

// }

/*
 * Include the following lines in your makefile:
 *
 * cardTest2: cardTest2.c dominion.o rngs.o
 *      gcc -o cardTest1 -g  cardTest2.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
    int newCards = 0;
    int discarded = 1;

    int r, prehandCount, predeckCount;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int p = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	r = initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    printf(" Testing Card: Smithy \n");
    predeckCount = testG.handCount[p];
    prehandCount = testG.deckCount[p];
    printf("pre hand count = %d, pre deck count = %d\n", prehandCount, predeckCount);

    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    newCards = 3;

	printf("hand count = %d, expected = %d\n", testG.handCount[p], prehandCount + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[p], predeckCount - newCards); 
	assert(testG.handCount[p] == prehandCount + newCards - discarded);
	assert(testG.deckCount[p] == predeckCount - newCards);

        printf(" Testing Card: Smithy  = Complete! \n");
    return 0;
}