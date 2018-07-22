// unit test for fullDeckCount

// dominion.c code reference

// int fullDeckCount(int player, int card, struct gameState *state)
// {
//   int i;
//   int count = 0;

//   for (i = 0; i < state->deckCount[player]; i++)
//   {
//     if (state->deck[player][i] == card)
//       count++;
//   }

//   for (i = 0; i < state->handCount[player]; i++)
//   {
//     if (state->hand[player][i] == card)
//       count++;
//   }

//   for (i = 0; i < state->discardCount[player]; i++)
//   {
//     if (state->discard[player][i] == card)
//       count++;
//   }

//   return count;
// }

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main()
{
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, deckCount, handCount, discardCount, total;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int maxhandCount = 5;
    int maxdeckCount = 5;
    int maxdiscardCount = 5;
    // arrays of copper cards
    int coppers[MAX_HAND];

    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
    }

    printf("TESTING fullDeckCount():\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    for (p = 0; p < numPlayer; p++)
    {
        for (deckCount = 0; deckCount < maxdeckCount; deckCount++)
        {
            for (handCount = 0; handCount < maxhandCount; handCount++)
            {
                for (discardCount = 0; discardCount < maxdiscardCount; discardCount++)
                {
                    memcpy(&testG, &G, sizeof(struct gameState));
                    testG.handCount[p] = handCount;                          // set the number of cards on hand
                    testG.discardCount[p] = discardCount;                    // set the number of cards in discard
                    testG.deckCount[p] = deckCount;                          // set the number of cards in deck
                    memcpy(testG.hand[p], coppers, sizeof(int) * handCount); // set all the cards in hand to copper
                    total = fullDeckCount(p, 4, &testG);                     //test when deck and discard are empty
                    //assert(total == handCount);

                    memcpy(testG.deck[p], coppers, sizeof(int) * deckCount); // set all the cards in deck to coppers
                    total = fullDeckCount(p, 4, &testG);                     //test when discard is empty
                    //printf("hand+deck total = %d, expected = %d\n", total, handCount + deckCount);
                    //assert(total == handCount + deckCount);

                    memcpy(testG.discard[p], coppers, sizeof(int) * discardCount); // set all the cards in discard to coppers
                    total = fullDeckCount(p, 4, &testG);                           //test when deck, discard, and hand have cards
                    //printf("hand+deck+discard total = %d, expected = %d\n", total, handCount + deckCount + discardCount);
                    //printf("total = %d, hand = %d deck = %d, discard = %d\n", total, handCount,deckCount,discardCount);
                    assert(total == handCount + deckCount + discardCount);
                }
            }
        }
    }
    printf("all tests passed \n");
    return 0;
}