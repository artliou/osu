/***
 * Unit Test 4: Check isGameOver() Function
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
  int s, st;
  int k[10] = {
    adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall
  };

  printf("Unit Test 4: Checking isGameOver().\n");
  initializeGame(2, k, 2, &state);
  
  state.supplyCount[province] = 0;
  //Check Province Count
  s = isGameOver(&state);
  // assert(s == 1);
  printf("isGameOver Test 1 - Province\n");
  if (s == 1) {
    printf("Unit Test 4: Province - Test Complete - SUCCESS.\n");  
  }
  if (s == 0) {
    printf("Unit Test 4: Province - Test Complete - FAIL.\n");    
  }

  // Set up End Game Scenario 0
  state.supplyCount[province] = 1;
  state.supplyCount[5] = 0;
  state.supplyCount[6] = 0;
  state.supplyCount[7] = 0;

  st = isGameOver(&state);

  printf("isGameOver Test 1 - 3 Empty Stacks\n");
  // assert(s == 1);
  if (st == 1) {
    printf("Unit Test 4: 3 Stacks - Test Complete - SUCCESS.\n");
    if (s == 1) {
      return 0;
    } else { //First Test Failed
      return 1;
    }
  }
  if (st == 0) {
    printf("Unit Test 4: 3 Stacks - Test Complete - FAIL.\n");    
    return 1;
  }

  return 0;
}