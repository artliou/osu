/* Card Test Random: Adventurer Card
 *  Card test/random test for the Adventurer Card
 *  Card Effect: Reveal cards from deck until 2 treasure is revealed, add the treasure cards to hand, discard the revealed cards.
 * 
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 * gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TESTCARD "adventurer"

int main() {
    int pass = 1;
    struct gameState G, testState;
    // int k[10] = {
    //     adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall
    // };

    int x = 1000;
    int i, n, r, playedCard;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int thisPlayer;
    int addedCards = 2;
    int coin, expectedCoin;
    int totalCards, expectedCards;

    //initialize game state
    //initializeGame(numbPlayers, k, randSeed, &G);

    //initialize random
    srand(time(NULL));
	printf("Random Testing for Card: Adventurer\n");
    for (i = 0; i < x; i++){
        printf("\nTest Case: %d\n", i);
        for (n = 0; n < sizeof(struct gameState) / sizeof(int); n++) {
            ((int*)&G)[n] = rand() % 128;
        }

        G.numPlayers = (rand() % 3)+2;
        G.whoseTurn = rand() % G.numPlayers;
        thisPlayer = whoseTurn(&G);
        G.handCount[thisPlayer] = (rand() % (MAX_HAND/2))+1;
        G.deckCount[thisPlayer] = (rand() % (MAX_DECK/2))+1;
        G.discardCount[thisPlayer] = (rand() % (MAX_DECK/2))+1;
        handPos = (rand() % G.handCount[thisPlayer]);
        for (n = 0; n < G.handCount[thisPlayer]; n++) {
            r = (rand() % 2);
            if (r == 0) {
                G.hand[thisPlayer][n] = copper;
            } else {
                G.hand[thisPlayer][n] = estate;
            }
        }
        for (n = 0; n < G.deckCount[thisPlayer]; n++) {
            r = (rand() % 2);
            if (r == 0) {
                G.deck[thisPlayer][n] = copper;
            } else {
                G.deck[thisPlayer][n] = estate;
            }
        }
        //Copy game State to Compare
        memcpy(&testState, &G, sizeof(struct gameState));

        playedCard = cardEffect(adventurer, choice1, choice2, choice3, &testState, handPos, &bonus);
        
        //Invalid Return Value        
        if (playedCard != 0) {
            printf("Playing Card Failed");
            pass = 0;
        };
        
        //Incorrect hand count
        if (testState.handCount[thisPlayer] != G.handCount[thisPlayer]+addedCards){
            pass = 0;
            printf("Hand Count: %d, Expected: %d \n\n", testState.handCount[thisPlayer], G.handCount[thisPlayer]+addedCards);
        }

        totalCards = G.deckCount[thisPlayer] + G.discardCount[thisPlayer];
        expectedCards = testState.deckCount[thisPlayer] + testState.discardCount[thisPlayer];
        if (expectedCards != totalCards - addedCards) {
            pass = 0;
            printf("Total Cards: %d, Expected: %d \n\n", expectedCards, totalCards-addedCards);
        };

        coin = 0;
        n = 0;
        while (n < numHandCards(&G)) {
            if (handCard(n, &G) == copper) {
                coin++;
            } else if (handCard(n, &G) == silver) {
                coin += 2;
            } else if (handCard(n, &G) == gold) {
                coin += 3;
            }
            n++;
        }

        expectedCoin = 0;
        n = 0;
        while (n < numHandCards(&testState)) {
            if (handCard(n, &testState) == copper) {
                expectedCoin++;
            } else if (handCard(n, &testState) == silver) {
                expectedCoin += 2;
            } else if (handCard(n, &testState) == gold) {
                expectedCoin += 3;
            }
            n++;
        };
        if (expectedCoin < coin + 2) {
            pass = 0;
            printf("Coin Count: %d, Expected Coin Count: >= %d \n\n", expectedCoin, coin + 2);
        }
    }
    //End For Loop and Return Results
    if (pass) {
        printf(">>>>>TEST SUCCESSFULLY COMPLETED <<<<<\n");
    } else{
        printf(">>>>>TEST FAILED<<<<<\n");
    }
	printf("\n >>>>> Random Card Test Complete - Adventurer <<<<<\n\n");
    return 0;
}