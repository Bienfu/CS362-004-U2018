// unit test for isGameOver

// int isGameOver(struct gameState *state)
// {
//   int i;
//   int j;

//   //if stack of Province cards is empty, the game ends
//   if (state->supplyCount[province] == 0)
//   {
//     return 1;
//   }

//   //if three supply pile are at 0, the game ends
//   j = 0;
//   for (i = 0; i < 25; i++)
//   {
//     if (state->supplyCount[i] == 0)
//     {
//       j++;
//     }
//   }
//   if (j >= 3)
//   {
//     return 1;
//   }

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
    int r, completionValue;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf("testing isGameOver \n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    completionValue = isGameOver(&G); //all supplies are full
    assert (completionValue == 0);
    printf("initialization test \n");

    G.supplyCount[province] = 1;//province has cards left
    completionValue = isGameOver(&G);
    assert (completionValue == 0);
    printf("province has cards test passed\n");

    G.supplyCount[0] = 0; //one supply pile is 0
    completionValue = isGameOver(&G);
    assert (completionValue == 0);
    printf("one supply is 0 test passed\n");

    G.supplyCount[1] = 0; //two supply pile is 0
    completionValue = isGameOver(&G);
    assert (completionValue == 0);
    printf("two supply is 0 test passed \n");

    G.supplyCount[4] = 0; //three supply pile is 0
    completionValue = isGameOver(&G);
    assert (completionValue == 1);
    printf("three supply is 0 test passed \n");

    //2nd batch reset values
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    printf("reset \n");

    
    G.supplyCount[province] = 0;//province has no cards left
    completionValue = isGameOver(&G);
    assert (completionValue == 1);
    printf("province has no cards test passed\n");

    G.supplyCount[0] = 0; //one supply pile is 0
    completionValue = isGameOver(&G);
    assert (completionValue == 1);
    printf("one supply is 0 test passed \n");

    G.supplyCount[1] = 0; //two supply pile is 0
    completionValue = isGameOver(&G);
    assert (completionValue == 1);
    printf("two supply is 0 test passed \n");

    G.supplyCount[4] = 0; //three supply pile is 0
    completionValue = isGameOver(&G);
    assert (completionValue == 1);
    printf("three supply is 0 test passed \n");

    printf("all tests passed \n");
    return 0;
}