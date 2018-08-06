#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdbool.h>

void myassert(bool value1, char *message)
{
    if (value1 == false)
    {
        printf(message);
        // exit(0);
    }
}

void checkAdventurerEffect(int p, struct gameState *post)
{
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));
    printf("pre created\n");

    int r;
    // printf(" pre handCount %i deckCount %i DiscardCount %i\n", pre.handCount[p],pre.deckCount[p],pre.discardCount[p]);
    r = cardEffectAdventurer(post, p);
    // r =     cardEffect(adventurer, choice1, choice2, choice3, post, handpos, &bonus);
    printf("effect worked\n");
    //make pre handcount equal to post handcount expected result
    pre.handCount[p] += 2;

    myassert(r == 0, "assert 1 failed\n");

    myassert(pre.handCount[p] == post->handCount[p], "assert 2 failed\n");
}

int main()
{

    int i, n, r, p, deckCount, discardCount, handCount;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    struct gameState G;

    printf("Testing cardEffectAdventurer\n");

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
        p = floor(Random() * 2);
        G.deckCount[p] = floor(Random() * MAX_DECK/2);
        G.discardCount[p] = floor(Random() * MAX_DECK/2);
        G.handCount[p] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * MAX_DECK);
        printf("check started\n");
        checkAdventurerEffect(p, &G);
        printf("check finished\n");
    }

    printf("ALL TESTS OK\n");
    return 0;
}
