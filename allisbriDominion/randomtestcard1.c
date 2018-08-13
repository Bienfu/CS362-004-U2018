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

void checkSmithyEffect(int p, struct gameState *post, int handPos)
{
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));
    printf("pre created\n");

    // printf("pre handCount %i DeckCount %i DiscardCount %i\n", pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);
    // printf("post handCount %i DeckCount %i DiscardCount %i\n", post->handCount[p], post->deckCount[p], post->discardCount[p]);
    // printf("post deckCount 1 %i deckCount 2 %i deckCount 3 %i\n", post->deck[p][post->deckCount[p] - 1], post->deck[p][post->deckCount[p] - 2], post->deck[p][post->deckCount[p] - 0]);
    int r, i;
    r = smithyEffect(post, handPos, p);
    printf("effect worked\n");

    if (pre.deckCount[p] > 0)
    {
        pre.handCount[p] += 3;
        pre.hand[p][pre.handCount[p] - 3] = pre.deck[p][pre.deckCount[p] - 3];
        pre.hand[p][pre.handCount[p] - 2] = pre.deck[p][pre.deckCount[p] - 2];
        // printf("pre deck 2 %i pre hand 3 %i\n",pre.deck[p][pre.deckCount[p]-4],pre.hand[p][pre.handCount[p]-4]);
        pre.hand[p][pre.handCount[p] - 3] = pre.deck[p][pre.deckCount[p] - 1];
        pre.handCount[p]--;
        pre.deckCount[p] -= 3;
        pre.playedCards[pre.playedCardCount] = pre.hand[p][handPos];

        pre.hand[p][pre.handCount[p] - 0] = -1;
        // pre.discardCount[p]++;
        printf("deck has cards\n");
        // for (i=0; i<post->handCount[p]; i++)
        // {
        //     printf("at pos %i post->hand is %i\n",i,post->hand[p][i]);
        // }
        // printf("pre handCount %i DeckCount %i DiscardCount %i\n",pre.handCount[p],pre.deckCount[p],pre.discardCount[p]);
        // printf("pre handCount 1 %i handCount 2 %i handCount 3 %i\n\n",pre.hand[p][pre.handCount[p]-1],pre.hand[p][pre.handCount[p]-2],pre.hand[p][pre.handCount[p]-3]);
        // printf("post handCount %i DeckCount %i DiscardCount %i\n",post->handCount[p],post->deckCount[p],post->discardCount[p]);
        // printf("post handCount 1 %i handCount 2 %i handCount 3 %i\n\n",post->hand[p][post->handCount[p]-1],post->hand[p][post->handCount[p]-2],post->hand[p][post->handCount[p]-3]);
        // printf("pre discard 2 %i post discard 2 %i\n\n", pre.discard[p][pre.discardCount[p] - 2], post->discard[p][post->discardCount[p] - 2]);
        // printf("post deckCount 0 %i post deckCount 1 %i deckCount 2 %i deckCount 3 %i postdeckcount 4 %i\n", post->deck[p][post->deckCount[p] - 0], post->deck[p][post->deckCount[p] - 1], post->deck[p][post->deckCount[p] - 2], post->deck[p][post->deckCount[p] - 3], post->deck[p][post->deckCount[p] - 4]);
        // printf("pre deckCount 0 %i pre deckCount 1 %i deckCount 2 %i deckCount 3 %i predeckcount 4 %i\n\n", pre.deck[p][pre.deckCount[p] - 0], pre.deck[p][pre.deckCount[p] - 1], pre.deck[p][pre.deckCount[p] - 2], pre.deck[p][pre.deckCount[p] - 3], pre.deck[p][pre.deckCount[p] - 4]);
        // printf("post handCount 0 %i post handCount 1 %i handCount 2 %i handCount 3 %i posthandcount 4 %i\n", post->hand[p][post->handCount[p] - 0], post->hand[p][post->handCount[p] - 1], post->hand[p][post->handCount[p] - 2], post->hand[p][post->handCount[p] - 3], post->hand[p][post->handCount[p] - 4]);
        // printf("pre handCount 0 %i pre handCount 1 %i handCount 2 %i handCount 3 %i prehandcount 4 %i\n\n", pre.hand[p][pre.handCount[p] - 0], pre.hand[p][pre.handCount[p] - 1], pre.hand[p][pre.handCount[p] - 2], pre.hand[p][pre.handCount[p] - 3], pre.hand[p][pre.handCount[p] - 4]);
        // printf("pre hand at handpos: %i , post hand at handpos %i\n\n", pre.discard[p][pre.discardCount[p] - 0],post->discard[p][post->discardCount[p] - 0]);
        pre.hand[p][handPos] = post->hand[p][handPos];
        pre.playedCardCount++;
        // printf("pre cardsplayed %i, post cardsplayed %i\n\n", pre.playedCardCount, post->playedCardCount);
        // for (i = 0; i <= pre.handCount[p]; i++)
        // {
        //     if (pre.hand[p][i] == post->hand[p][i])
        //     {
        //         printf("at pos %i, same\n", i);
        //     }
        //     else
        //     {
        //         printf("at pos %i, diff\n", i);
        //     }
        // }
        // printf("for hand done\n\n");
        // for (i = 0; i <= pre.discardCount[p]; i++)
        // {
        //     if (pre.discard[p][i] == post->discard[p][i])
        //     {
        //         printf("disc at pos %i, same\n", i);
        //     }
        //     else
        //     {
        //         printf("at pos %i, diff\n", i);
        //     }
        // }
        // printf("for discard done\n\n");
        // // pre.playedCards[pre.playedCardCount-1] = post->playedCards[post->playedCardCount-1];
        // // pre.playedCards[pre.playedCardCount-1] = pre.hand[p][handPos];
        // for (i = 0; i <= pre.playedCardCount; i++)
        // {
        //     if (pre.playedCards[i] == post->playedCards[i])
        //     {
        //         printf("playedcards at pos %i, same\n", i);
        //     }
        //     else
        //     {
        //         printf("at pos %i, diff\n", i);
        //     }
        // }
    }
    else if (pre.discardCount[p] > 0)
    {
        memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
        memcpy(pre.discard[p], post->discard[p], sizeof(int) * pre.discardCount[p]);
        pre.hand[p][post->handCount[p] - 3] = post->hand[p][post->handCount[p] - 3];
        pre.hand[p][post->handCount[p] - 2] = post->hand[p][post->handCount[p] - 2];
        pre.hand[p][post->handCount[p] - 1] = post->hand[p][post->handCount[p] - 1];
        pre.handCount[p] += 2;
        pre.hand[p][pre.handCount[p] - 0] = -1;
        pre.deckCount[p] =  pre.discardCount[p]-3;
        pre.discardCount[p] = 0;
        pre.playedCards[pre.playedCardCount] = pre.hand[p][handPos];
        pre.playedCardCount++;
        pre.hand[p][handPos] = post->hand[p][handPos];
        // printf("pre cardsplayed %i, post cardsplayed %i\n\n", pre.playedCardCount, post->playedCardCount);
        // printf("deck has no cards\n");
        // printf("pre handCount %i DeckCount %i DiscardCount %i\n", pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);
        // printf("pre handCount 1 %i handCount 2 %i handCount 3 %i\n", pre.hand[p][pre.handCount[p] - 3], pre.hand[p][pre.handCount[p] - 2], pre.hand[p][pre.handCount[p] - 1]);
        // printf("post handCount %i DeckCount %i DiscardCount %i\n", post->handCount[p], post->deckCount[p], post->discardCount[p]);
        // printf("post handCount 1 %i handCount 2 %i handCount 3 %i\n", post->hand[p][post->handCount[p] - 3], post->hand[p][post->handCount[p] - 2], post->hand[p][post->handCount[p] - 1]);
    }

    myassert(r == 0, "assert 1 failed\n");
    // printf("assert 1 passed\n");
    myassert(memcmp(&pre, post, sizeof(struct gameState)) == 0, "assert 2 failed\n");
}

int main()
{

    int i, n, r, p, deckCount, discardCount, handCount, handPos;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    struct gameState G;

    printf("Testing cardEffectSmithy\n");

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
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * MAX_DECK);
        handPos = 0;
        printf("check started\n");
        checkSmithyEffect(p, &G, handPos);
    }

    printf("ALL TESTS OK\n");
    return 0;
}
