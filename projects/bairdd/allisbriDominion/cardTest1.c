// Card test for Adventurer refactored function
// int cardEffectAdventurer ( struct gameState *currentPlayer, int state)
// {
//   // int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)

//   // int i;
//   // int j;
//   // int k;
//   // int x;
//   // int index;
//   // int currentPlayer = whoseTurn(state);
//   // int nextPlayer = currentPlayer + 1;

//   // int tributeRevealedCards[2] = {-1, -1};
//   // int temphand[MAX_HAND]; // moved above the if statement
//   int drawntreasure = 0;
//   int cardDrawn;
//   int z = 0; // this is the counter for the temp hand
//   // case adventurer:
//   int temphand[MAX_HAND];
//     while (drawntreasure < 2)
//     {
//       if (state->deckCount[currentPlayer] < 1)
//       { //if the deck is empty we need to shuffle discard and add to deck
//         shuffle(currentPlayer, state);
//       }
//       drawCard(currentPlayer, state);
//       cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1]; //top card of hand is most recently drawn card.
//       if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
//         drawntreasure++;
//       else
//       {
//         temphand[z] = cardDrawn;
//         state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
//         z++;
//       }
//     }
//     while (z - 1 >= 0)
//     {
//       state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z - 1]; // discard all cards in play that have been drawn
//       z = z - 1;
//     }
//     return 0;
// }

/*
 * Include the following lines in your makefile:
 *
 * cardTest1: cardTest1.c dominion.o rngs.o
 *      gcc -o cardTest1 -g  cardTest1.c dominion.o rngs.o $(CFLAGS)
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
    int prehandCount, predeckCount , prediscardCount;
    int i, j, m, r;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int coppers[MAX_HAND];

    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
    }

	// initialize a game state and player cards
	r = initializeGame(numPlayers, k, seed, &G);

    printf(" Testing Card: Adventurer \n");
    memcpy(&testG, &G, sizeof(struct gameState));
    prehandCount = testG.handCount[thisPlayer];
    predeckCount = testG.deckCount[thisPlayer];
    prediscardCount = testG.discardCount[thisPlayer];
    printf("Initialization: hand count = %d and deck count= %d and discard count: %d\n",  testG.handCount[thisPlayer], testG.deckCount[thisPlayer],testG.discardCount[thisPlayer]);
    //test when deck contains no treasures
    cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

    //Test for Hand count
    printf("Cards in Hand = %d , expected cards = %d\n", testG.handCount[thisPlayer], prehandCount + 0);
    printf("Top two cards are %d and %d which can be any value\n", testG.hand[thisPlayer][testG.handCount[thisPlayer]-1,testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2]]);
    assert(testG.handCount[thisPlayer] == (prehandCount + 0));

    //test for deck and discard
    printf("Difference in cards in deck: %d, Number of cards in discard: %d\n", predeckCount - testG.deckCount[thisPlayer], testG.discardCount[thisPlayer]);
    assert( (predeckCount - testG.deckCount[thisPlayer]) == (testG.discardCount[thisPlayer]));

    //discard check for correct cards
    for (i = thisPlayer; i < testG.discardCount[thisPlayer]; i++)
    {
        if (testG.discard[thisPlayer][i] != 4 || testG.discard[thisPlayer][i] != 5 || testG.discard[thisPlayer][i] != 6)
        {
            printf("invalid discard for adventurer at index %d\n", i);
        }
    }
//test when deck is only treasures
    memcpy(&testG, &G, sizeof(struct gameState));
    memcpy(G.deck[thisPlayer], coppers, sizeof(int) * predeckCount); // set all the cards in deck to coppers
    cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

    //Test for Hand count
    printf("Cards in Hand = %d , expected cards = %d\n", testG.handCount[thisPlayer], prehandCount + 2 );
    printf("Top two cards are %d and %d which should be a 4,5, or 6\n", testG.hand[thisPlayer][testG.handCount[thisPlayer]-1,testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2]]);
    assert(testG.handCount[thisPlayer] == (prehandCount + 2));

    //test for deck and discard
    printf("Difference in cards in deck: %d, Number of cards in discard: %d\n", predeckCount - testG.deckCount[thisPlayer], testG.discardCount[thisPlayer]);
    assert( (predeckCount - testG.deckCount[thisPlayer]) == 2);
    assert(testG.discardCount[thisPlayer] == 0);

    //discard check for correct cards
    for (i = thisPlayer; i < testG.discardCount[thisPlayer]; i++)
    {
        if (testG.discard[thisPlayer][i] != 4 || testG.discard[thisPlayer][i] != 5 || testG.discard[thisPlayer][i] != 6)
        {
            printf("invalid discard for adventurer at index %d\n", i);
        }
    }
    printf("All tests passed\n");

return 0;
}