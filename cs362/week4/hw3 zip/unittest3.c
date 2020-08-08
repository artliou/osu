/***
 * Unit Test 3: Check getCost() Function
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
  printf("Unit Test 3: getCost() Function on various cards.\n");

  if ((getCost(gardens) == 4) && (getCost(village) == 3) && (getCost(smithy) == 4) && (getCost(remodel) == 4)) {
    printf("Unit Test 3: Test Complete - SUCCESS.\n");  
    return 0;
  } else {
    printf("Unit Test 3: Test Complete - FAIL.\n");    
    return 1;
  }

  return 0;
}