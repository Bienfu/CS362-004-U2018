// //card test for Cutpurse

//  int i;
//   int j;
//   int k;
//   // int x;
//   // int index;
//   // int currentPlayer = whoseTurn(state);
//   // int nextPlayer = currentPlayer + 1;

//   // int tributeRevealedCards[2] = {-1, -1};
//   // int temphand[MAX_HAND]; // moved above the if statement
//   // int drawntreasure = 0;
//   // int cardDrawn;
//   // int z = 0; // this is the counter for the temp hand
//   //   case cutpurse:

//     updateCoins(currentPlayer, state, 2);
//     for (i = 0; i < state->numPlayers; i++)
//     {
//       if (i != currentPlayer)
//       {
//         for (j = 1; j <= state->handCount[i]; j++)
//         {
//           if (state->hand[i][j] == copper)
//           {
//             discardCard(j, i, state, 0);
//             break;
//           }
//           if (j == state->handCount[i])
//           {
//             for (k = 0; k < state->handCount[i]; k++)
//             {
//               if (DEBUG)
//                 printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
//             }
//             break;
//           }
//         }
//       }
//     }

//     //discard played card from hand
//     discardCard(handPos, currentPlayer, state, 0);

//     return 0;


/*
 * Include the following lines in your makefile:
 *
 * cardTest3: cardTest3.c dominion.o rngs.o
 *      gcc -o cardTest1 -g  cardTest3.c dominion.o rngs.o $(CFLAGS)
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

    int i, j, m, r;
    int copperCount = 0;
    int handCount = 5;
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

    int silvers[MAX_HAND];

    for(m = 0; m < MAX_HAND; m++)
    {
        silvers[m] = silver;
    }

	// initialize a game state and player cards
	r = initializeGame(numPlayers, k, seed, &G);

    printf(" Testing Card: Cutpurse \n");
    memcpy(&testG, &G, sizeof(struct gameState));
    handCount = testG.handCount[0];

    for (i = 0; i < numPlayers; i++)
    {
        testG.handCount[i] = handCount;
        memcpy(testG.hand[i], coppers, sizeof(int) * handCount); //fills all players hands with 5 coppers
    }
    printf("player 1 has %d cards\n",testG.handCount[1]);
    for (i = 0 ; i < numPlayers; i++)
    {
        copperCount = 0;
        for (j = 0; j < testG.handCount[i]; j++)
        {
            if (testG.hand[i][j] == copper)
            {
                copperCount++;
            }
        }
        printf("Player %d has %d coppers \n", i, copperCount );
        assert(copperCount == 5);
    }

    printf(" Test 1: all players have 5 coppers \n");
    cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);
    for (i = 1 ; i < numPlayers; i++)
    {
        copperCount = 0;
        for (j = 0; j < testG.handCount[i]; j++)
        {
            if (testG.hand[i][j] == copper)
            {
                copperCount++;
            }
        }
        printf("Player %d has %d coppers \n", i, copperCount );
        assert(copperCount < 5);
    }

    printf(" Test 2: all players have 0 coppers and 5 silvers \n");
    memcpy(&testG, &G, sizeof(struct gameState));
    for (i = 0 ; i < numPlayers; i++)
    {
        memcpy(testG.hand[i], silvers, sizeof(int) * handCount); // set all the cards in hand to silvers
    }
    cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);
    for (i = 1 ; i < numPlayers; i++)
    {
        copperCount = 0;
        for (j = 0; j < testG.handCount[i]; j++)
        {
            if (testG.hand[i][j] == copper)
            {
                copperCount++;
            }
        }
        printf("Player %d has %d coppers \n", i, copperCount );
        assert(copperCount < 5);
    }

    printf(" All tests Passed \n");

    return 0;
}