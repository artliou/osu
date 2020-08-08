/***
 * Unit Test 2: Check Initialize Game Function - Detailed
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

  printf("Unit Test 2: initializeGame() function Specifics and Edge Cases.\n");
  
  //Test Case 1 - Invalid Number of Players
  int a = initializeGame(1, k, 2, &state);
 
  if (a == -1) {
    printf("Unit Test 2: Test Complete - SUCCESS - Number of Players Cannot be 1.\n");  
    return 0;
  }
  if (a != -1) {
    printf("Unit Test 2: Test Complete - FAIL - Invalid Number of Players.\n");    
    return 1;
  }

  return 0;
}