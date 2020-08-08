/***
 * UnitTest1: Check Initialize Game Function
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 */

#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {
  struct gameState state;

  int k[10] = {
    adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall
  };

  printf("Unit Test 1: Starting a game of Dominion.\n");
  
  int g = initializeGame(2, k, 2, &state);

  if (g == 0) {
    printf("Unit Test 1: Test Complete - SUCCESS.\n");  
    return 0;
  }
  if (g == 1) {
    printf("Unit Test 1: Test Complete - FAIL.\n");    
    return 1;
  }

  printf("Unit Test 1: Test Failure - Did Not Return a 0 or 1.\n");
  assert(g == 0);
  return 0;
}