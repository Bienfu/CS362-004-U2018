// // Unit Test for gainCard

// int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
// {
//   //Note: supplyPos is enum of choosen card

//   //check if supply pile is empty (0) or card is not used in game (-1)
//   if (supplyCount(supplyPos, state) < 1)
//   {
//     return -1;
//   }

//   //added card for [whoseTurn] current player:
//   // toFlag = 0 : add to discard
//   // toFlag = 1 : add to deck
//   // toFlag = 2 : add to hand

//   if (toFlag == 1)
//   {
//     state->deck[player][state->deckCount[player]] = supplyPos;
//     state->deckCount[player]++;
//   }
//   else if (toFlag == 2)
//   {
//     state->hand[player][state->handCount[player]] = supplyPos;
//     state->handCount[player]++;
//   }
//   else
//   {
//     state->discard[player][state->discardCount[player]] = supplyPos;
//     state->discardCount[player]++;
//   }

//   //decrease number in supply pile
//   state->supplyCount[supplyPos]--;

//   return 0;
// }

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, deckCount, handCount, discardCount, gained;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    handCount = 0;
    deckCount = 0;
    discardCount = 0;
    int maxHand = 30;
    // arrays of all coppers, silvers, and golds
    p = 0;
    printf("testing gainCard \n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[p] = handCount;
    G.deckCount[p] = deckCount;
    G.discardCount[p] = discardCount;
    printf("initialization test: deckCount = %d\n", G.deckCount[p]);
    assert (G.deckCount[p] == 0);

    gainCard(1 , &G, 1, p);
    printf("add deck test: deckCount = %d\n", G.deckCount[p]);
    assert (G.deckCount[p] == 1);

    gainCard(1 , &G, 2, p);
    printf("add hand test: handCount = %d\n", G.handCount[p]);
    assert (G.handCount[p] == 1);

    gainCard(1 , &G, 0, p);
    printf("add discard test: discardCount = %d\n", G.discardCount[p]);
    assert (G.discardCount[p] == 1);

//test for draw from empty supply

    for (i = 0; i < maxHand; i++ )
    {
        gained = gainCard(2 , &G, 2, 0);
        if (gained = -1)
        {
            printf("supply for given pile is 0\n");
            break;
        }
    }

    printf("all tests passed \n");
return 0;
}