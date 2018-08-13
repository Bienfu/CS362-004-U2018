//test for Sea hag

// int cardEffectSea_Hag (struct gameState *state, int currentPlayer)
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
//   //   case sea_hag:
//     for (i = 0; i < state->numPlayers; i++)
//     {
//       if (i != currentPlayer)
//       {
//         state->discard[i][state->discardCount[i]] = state->deck[i][state->deckCount[i]--];
//         state->deckCount[i]--;
//         state->discardCount[i]--;
//         state->deck[i][state->deckCount[i]--] = curse; //Top card now a curse
//       }
//     }
//     return 0;
// }


/*
 * Include the following lines in your makefile:
 *
 * cardTest4: cardTest4.c dominion.o rngs.o
 *      gcc -o cardTest1 -g  cardTest4.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main()
{
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m, r, copperCount;
    int predeckCount , prediscardCount;
    int deckCount = 5;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 3;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int coppers[MAX_HAND];

    for(m = 0; m < MAX_HAND; m++)
    {
        coppers[m] = copper;
    }

	// initialize a game state and player cards
	r = initializeGame(numPlayers, k, seed, &G);

    printf(" Testing Card: Sea Hag \n");

    memcpy(&testG, &G, sizeof(struct gameState));
    for (i = 0; i < numPlayers; i++)
    {
        testG.deckCount[i] = deckCount;
        memcpy(testG.deck[i], coppers, sizeof(int) * deckCount); //fills all players decks with 5 coppers
    }
    predeckCount = testG.deckCount[0];
    prediscardCount = testG.discardCount[0];
    printf("Initialization: Deck Count = %d and Discard Count= %d\n",  testG.deckCount[0], testG.discardCount[0]);

    cardEffect(sea_hag, choice1, choice2, choice3, &testG, handpos, &bonus);
    //player 1 deck and discard checks

    printf(" player 1 post deck and discard test \n");
    printf("Deck Count = %d and Expected: %d\n",testG.deckCount[0], predeckCount);
    assert(testG.deckCount[0] == predeckCount);
    printf("Discard Count = %d and Expected: %d\n",testG.discardCount[0], prediscardCount);
    assert(testG.discardCount[0] == prediscardCount);

    //player 2 deck and discard checks

    printf(" player 2 post deck and discard test \n");
    printf("Deck Count = %d and Expected: %d\n",testG.deckCount[1], predeckCount);
    assert(testG.deckCount[1] == predeckCount);
    printf("Discard Count = %d and Expected: %d\n",testG.discardCount[1], prediscardCount+1);
    assert(testG.discardCount[1] == prediscardCount+1);
    // testG.deck[1][testG.deckCount[1]] = curse;
    // printf("%d top card planted\n", testG.deck[1][testG.deckCount[1]]);
    printf("top card of deck is %d , next card %d which is supposed to be a curse = 0\n", testG.deck[1][testG.deckCount[1]],testG.deck[1][testG.deckCount[1]-1]);
    assert(testG.deck[1][testG.deckCount[1]-1] == 0);

    //player 3 deck and discard checks (same as 2)

    printf(" player 3 post deck and discard test \n");
    printf("Deck Count = %d and Expected: %d\n",testG.deckCount[2], predeckCount);
    assert(testG.deckCount[2] == predeckCount);
    printf("Discard Count = %d and Expected: %d\n",testG.discardCount[2], prediscardCount+1);
    assert(testG.discardCount[2] == prediscardCount+1);
    printf("top card of deck is %d which is supposed to be a curse = 0\n", testG.deck[2][testG.deckCount[2]-1]);
    assert(testG.deck[2][testG.deckCount[2]-1] == 0);

    printf("all tests complete\n");
return 0;
}