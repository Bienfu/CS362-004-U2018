// //unit test for scoreFor

// int scoreFor(int player, struct gameState *state)
// {

//     int i;
//     int score = 0;
//     //score from hand
//     for (i = 0; i < state->handCount[player]; i++)
//     {
//         if (state->hand[player][i] == curse)
//         {
//             score = score - 1;
//         };
//         if (state->hand[player][i] == estate)
//         {
//             score = score + 1;
//         };
//         if (state->hand[player][i] == duchy)
//         {
//             score = score + 3;
//         };
//         if (state->hand[player][i] == province)
//         {
//             score = score + 6;
//         };
//         if (state->hand[player][i] == great_hall)
//         {
//             score = score + 1;
//         };
//         if (state->hand[player][i] == gardens)
//         {
//             score = score + (fullDeckCount(player, 0, state) / 10);
//         };
//     }

//     //score from discard
//     for (i = 0; i < state->discardCount[player]; i++)
//     {
//         if (state->discard[player][i] == curse)
//         {
//             score = score - 1;
//         };
//         if (state->discard[player][i] == estate)
//         {
//             score = score + 1;
//         };
//         if (state->discard[player][i] == duchy)
//         {
//             score = score + 3;
//         };
//         if (state->discard[player][i] == province)
//         {
//             score = score + 6;
//         };
//         if (state->discard[player][i] == great_hall)
//         {
//             score = score + 1;
//         };
//         if (state->discard[player][i] == gardens)
//         {
//             score = score + (fullDeckCount(player, 0, state) / 10);
//         };
//     }

//     //score from deck
//     for (i = 0; i < state->discardCount[player]; i++)
//     {
//         if (state->deck[player][i] == curse)
//         {
//             score = score - 1;
//         };
//         if (state->deck[player][i] == estate)
//         {
//             score = score + 1;
//         };
//         if (state->deck[player][i] == duchy)
//         {
//             score = score + 3;
//         };
//         if (state->deck[player][i] == province)
//         {
//             score = score + 6;
//         };
//         if (state->deck[player][i] == great_hall)
//         {
//             score = score + 1;
//         };
//         if (state->deck[player][i] == gardens)
//         {
//             score = score + (fullDeckCount(player, 0, state) / 10);
//         };
//     }

//     return score;
// }

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdbool.h>

int main()
{
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, score;
    int initialSize = 0;
    int maxHand = 20;
    bool fill = true;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int largeHand[maxHand];
    p = 0;
    
    for (i = 0; i < maxHand; i++) //hand with value of 1. used in garden test.
    {
        if (fill == true)
        {
            largeHand[i] = curse;
        }
        else
        {
            largeHand[i] = estate;
        }
        fill = !fill;
    }

    printf("testing scoreFor \n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[p] = initialSize;
    G.deckCount[p] = initialSize;
    G.discardCount[p] = initialSize;
    score = scoreFor(p, &G);
    printf("initialization test: score = %d and expected = %d \n", score, 0);
    assert(score == 0);

    G.handCount[p] = initialSize + 1;
    G.hand[p][0] = curse;
    score = scoreFor(p, &G);
    printf("curse test: score = %d and expected = %d \n", score, -1);
    assert(score == -1);

    G.hand[p][0] = estate;
    score = scoreFor(p, &G);
    printf("estate test: score = %d and expected = %d \n", score, 1);
    assert(score == 1);

    G.hand[p][0] = duchy;
    score = scoreFor(p, &G);
    printf("duchy test: score = %d and expected = %d \n", score, 3);
    assert(score == 3);

    G.hand[p][0] = province;
    score = scoreFor(p, &G);
    printf("province test: score = %d and expected = %d \n", score, 6);
    assert(score == 6);

    G.hand[p][0] = great_hall;
    score = scoreFor(p, &G);
    printf("great_hall test: score = %d and expected = %d \n", score, 1);
    assert(score == 1);

    G.handCount[p] = maxHand+1;
    memcpy(G.hand[p], largeHand, sizeof(int) * maxHand); // set all the cards in hand to largeHand
    //DISCLAIMER: gardens counts amount of curses in fulldeck as opposed to all cards
    // score = scoreFor(p, &G);
    // printf("gardens test: score = %d and expected = %d \n", score, 2);
    G.hand[p][maxHand] = gardens;
    score = scoreFor(p, &G);
    printf("gardens test: score = %d and expected = %d \n", score, 1);
    assert(score == 1);

    G.deckCount[p] = maxHand;
    memcpy(G.deck[p], largeHand, sizeof(int) * maxHand); // set all the cards in deck to same as garden test
    score = scoreFor(p, &G);
    printf("deck test: score = %d and expected = %d \n", score, 2);
    assert(score == 2);

    G.discardCount[p] = maxHand;
    memcpy(G.discard[p], largeHand, sizeof(int) * maxHand); // set all the cards in discard to same as garden test
    score = scoreFor(p, &G);
    printf("discard test: score = %d and expected = %d \n", score, 3);
    assert(score == 3);

    printf("all tests passed \n");
    return 0;
}