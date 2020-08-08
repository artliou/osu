/* Card Test Random: Villager Card
 *  Card test/random test for the Villager Card
 *  Card Effect: Draw 1 Card, +2 Action
 * 
* randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
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

#define TESTCARD "village"

int main() {
  int pass = 1;
  struct gameState G, testState;
  // int k[10] = {
  //     adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall
  // };
  int x = 1000;
  int i, n, playedCard;
  int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int thisPlayer;
  int addedCards = 1;
  int addedActions = 2;
  int discard = 1;
  int totalCards, expectedCards;

	srand(time(NULL));
	printf("Random Testing for Card: Village\n");
	for (i = 0; i < x; i++){
      printf("\nTest Case: %d\n", i);
      for (n = 0; n < sizeof(struct gameState)/ sizeof(int); n++) {
        ((int*)&G)[n] = rand() % 128;
      }

      G.numPlayers = (rand() % 3)+2;
      G.whoseTurn = rand() % G.numPlayers;
      thisPlayer = whoseTurn(&G);
      G.handCount[thisPlayer] = (rand() % (MAX_HAND/2))+1;
      G.deckCount[thisPlayer] = (rand() % (MAX_DECK/2))+1;
      G.discardCount[thisPlayer] = (rand() % (MAX_DECK/2))+1;
      handPos = (rand() % G.handCount[thisPlayer]);

      memcpy(&testState, &G, sizeof(struct gameState));

      playedCard = cardEffect(village, choice1, choice2, choice3, &testState, handPos, &bonus);
      if (playedCard != 0) {
        printf("Playing Card Failed");
        pass = 0;
      };

      if (testState.numActions != G.numActions+addedActions){
        pass = 0;
        printf("Action Count: %d, Expected: %d \n", testState.numActions, G.numActions+addedActions);
      }

      if (testState.handCount[thisPlayer] != G.handCount[thisPlayer]+addedCards-discard){
        pass = 0;
        printf("Hand Count: %d, Expected: %d \n", testState.handCount[thisPlayer], G.handCount[thisPlayer]+addedCards-discard);
      }

      totalCards = G.deckCount[thisPlayer] + G.discardCount[thisPlayer];
      expectedCards = testState.deckCount[thisPlayer] + testState.discardCount[thisPlayer];
      if (expectedCards != totalCards - addedCards) {
        pass = 0;
        printf("Total Cards: %d, Expected: %d \n", expectedCards, totalCards-addedCards);
      };
    }
    //End For Loop and Return Results
    if (pass) {
        printf(">>>>>TEST SUCCESSFULLY COMPLETED <<<<<\n");
    } else{
        printf(">>>>>TEST FAILED<<<<<\n");
    }
    printf("\n>>>>> Random Card Test Complete - Village <<<<<\n\n");
    return 0;
};