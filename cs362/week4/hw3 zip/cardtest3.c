 /* Card Test 3: Village Card
 *  Card test/unit test for the Smithy Card
 *  Card Effect: +1 card, +2 Actions
 * 
 * Include the following lines in your makefile:
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main(int argc, char **argv) {
  int numPlayers = 2;
  int thisPlayer = 0, otherPlayer = 1;
  int seed = 1000;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  struct gameState state, testState;
  int k[10] = {
    adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall
  };

  initializeGame(numPlayers, k, seed, &state);
  state.hand[thisPlayer][0] = village;
	printf("Card Test 3: %s\n", TESTCARD);
	memcpy(&testState, &state, sizeof(struct gameState));
  cardEffect(village, choice1, choice2, choice3, &testState, handpos, &bonus);

  //Testing
	printf("Card Test 3A: +1 Card. hand count = %d, expected = %d\n", testState.handCount[thisPlayer], state.handCount[thisPlayer] + 1);

	printf("Card Test 3B: +2 Actions. action count = %d, expected = %d\n", testState.numActions, state.numActions + 2);

	printf("Card Test 3C: -1 Deck. deck count = %d, expected = %d\n", testState.deckCount[thisPlayer], state.deckCount[thisPlayer] - 1);

	printf("Card Test 3D: No State Change for Other Players = %d\n", state.handCount[otherPlayer] == testState.handCount[otherPlayer]);

  // Check to make sure that Victory and Kingdom Card Piles. If all 13 piles are the same across both states, then test passes.
  int a = (state.supplyCount[estate] = testState.supplyCount[estate]);
  int b = (state.supplyCount[duchy] = testState.supplyCount[duchy]);
  int c = (state.supplyCount[province] = testState.supplyCount[province]);
  int d = (state.supplyCount[adventurer] = testState.supplyCount[adventurer]);
  int e = (state.supplyCount[council_room] = testState.supplyCount[council_room]);
  int f = (state.supplyCount[feast] = testState.supplyCount[feast]);
  int g = (state.supplyCount[gardens] = testState.supplyCount[gardens]);
  int h = (state.supplyCount[mine] = testState.supplyCount[mine]);
  int i = (state.supplyCount[remodel] = testState.supplyCount[remodel]);
  int j = (state.supplyCount[smithy] = testState.supplyCount[smithy]);
  int m = (state.supplyCount[village] = testState.supplyCount[village]);
  int n = (state.supplyCount[baron] = testState.supplyCount[baron]);
  int p = (state.supplyCount[great_hall] = testState.supplyCount[great_hall]);
  int sum = a+b+c+d+e+f+g+h+i+j+m+n+p;
  int piles = (sum == 12);
  printf("Card Test 3F: No State Change for Victory Card Piles and Kingdom Card Piles = %d\n", piles);

	printf("\n >>>>> Card Test 3 Complete - %s <<<<<\n\n", TESTCARD);
  return 0;
}
