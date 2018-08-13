#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdbool.h>

void myassert(bool value1, char* message){
    if (value1 == false){
        printf(message);
         exit(0);
    }
}


void checkSeaHagEffect(struct gameState *post,  int p, int * errorCount)
{
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));

    int r, i;
    int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0;
    int player = p;
    printf("player: %i p: %i\n",player,p);

    for (i = 0; i < pre.numPlayers; i++)
    {
        printf("%i's pre handCount %i deckCount %i DiscardCount %i\n",i, pre.handCount[i],pre.deckCount[i],pre.discardCount[i]);
        printf("deck top card = %i\n", pre.deck[i][pre.deckCount[i]-1]);
        printf("deck top card = %i\n\n", post->deck[i][post->deckCount[i]-1]);
    }

    r = cardEffect(sea_hag, choice1, choice2, choice3, post, handPos, &bonus);
    printf("effect worked\n");
    //
    // printf("player: %i p: %i\n\n",player,p);
    if(player == 0){
        player = pre.numPlayers-1;
    }
    else {
        player--;
    }
    // printf("player: %i p: %i\n\n",player,p);
    while (player != p)
    {
        // printf("inside wild %i\n", player);
                // printf("deck top card = %i\n", pre.deck[player][pre.deckCount[player]-1]);
        pre.discard[player][pre.discardCount[player]] = pre.deck[player][pre.deckCount[player]-1];
        // printf("inwhilen discard top card = %i\n\n", pre.discard[player][pre.discardCount[player]]);
        pre.discardCount[player]++;
        // printf("inwhilen aft discard top card = %i\n\n", pre.discard[player][pre.discardCount[player]-1]);
        pre.deck[player][pre.deckCount[player]-1] = 0;
        if(player == 0)
        {
            player = pre.numPlayers-1;
        }
        else 
        {
            player--;
        }

    }
    //    for (i = 0; i < pre.numPlayers; i++)
    // {
    //     printf("%i's pre handCount %i deckCount %i DiscardCount %i\n",i, pre.handCount[i],pre.deckCount[i],pre.discardCount[i]);
    //     printf("%i's deck top %i, discard top %i \n",i, pre.deck[i][pre.deckCount[i]-1],pre.discard[i][pre.discardCount[i]-1]);
    //     printf("%i's post handCount %i deckCount %i DiscardCount %i\n",i, post->handCount[i],post->deckCount[i],post->discardCount[i]);
    //     printf("%i's deck top %i, discard top %i \n\n",i, post->deck[i][post->deckCount[i]-1],post->discard[i][post->discardCount[i]-1]);
    // }

    myassert(r == 0, "assert 1 failed\n");

    myassert(memcmp(&pre, post, sizeof(struct gameState)) == 0, "assert 2 failed\n");
}

int main()
{

    int i, n, r, p, deckCount, discardCount, handCount;
    int errorCount = 0;
    int seed = 1000;
    int numPlayers = 4;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    struct gameState G;

    printf("Testing cardEffectSea_Hag\n");

    printf("RANDOM TESTS.\n");

    SelectStream(2);
    PutSeed(3);
    r = initializeGame(numPlayers, k, seed, &G);
    for (n = 0; n < 2000; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char *)&G)[i] = floor(Random() * 256);
        }
        printf("struct created \n");
        p = floor(Random() * 3);
        G.numPlayers = 4;
        for (i=0; i < numPlayers; i++){

        G.deckCount[i] = floor(Random() * MAX_DECK);
        G.discardCount[i] = floor(Random() * MAX_DECK);
        G.handCount[i] = floor(Random() * MAX_HAND);
        }
        G.playedCardCount = floor(Random() * MAX_DECK);
        printf("check started\n");
        checkSeaHagEffect(&G, p, &errorCount);
    }

    printf("ALL TESTS OK\n");

  return 0;
}
