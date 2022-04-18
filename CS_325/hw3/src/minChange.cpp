#include "minChange.h"
#include "limits.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

void WriteMinCoins(coinSet_t * coinData, const char * filename)
{
    int finalCoins[coinData->C.size()];
    int numCoins = minCoins(coinData, finalCoins);

    // Calculate the coin combination based on the min number of coins required
    coinData->C.size();

    std::ofstream f;
    f.open (filename, std::ofstream::out | std::ofstream::app | std::ofstream::ate);
    for(int index = 0; index < coinData->C.size(); index++)
    {
        f << coinData->C[index] << " ";
    }
    f << "\n";

    f << coinData->A << "\n";

    for(int index = 0; index < coinData->C.size(); index++)
    {
        f << finalCoins[index] << " ";
    }
    f << "\n";

    f << numCoins << "\n";
}

int minCoins(coinSet_t * coinData, int * finalCoins)
{
    printf ("Using # coins: %d, Amount: %d", coinData->C.size(), coinData->A);
    int tempTable[coinData->A + 1];
    tempTable[0] = 0;
    int coinSet[coinData->A];
    int tempCoin;
    memset (coinSet, 0, sizeof (int) * coinData->A);
    memset (finalCoins, 0, sizeof (int) * coinData->C.size());
 
    for (int index=1; index <= coinData->A; index++)
    {
        tempTable[index] = INT_MAX;
    }
 
    for (int index = 1; index <= coinData->A; index++)
    {
        for (int testCoin = 0; testCoin < coinData->C.size(); testCoin++)
        {
            if (coinData->C[testCoin] <= index)
            {
                int testResult = tempTable[index - coinData->C[testCoin]];
                if ((testResult != INT_MAX) && (testResult + 1 < tempTable[index]))
                {
                    tempTable[index] = testResult + 1;
                    tempCoin = testCoin;
                }
            }
        }
        coinSet[index] = tempCoin;
    }
    printf ("\tMinCoins: %d Coins: ", tempTable[coinData->A]);

    int index = coinData->A;
    while (index > 0)
    {
        finalCoins[coinSet[index]]++;
        index -= coinData->C[coinSet[index]];
    }
 
    for (int index = 0; index < coinData->C.size(); index++)
    {
//        printf ("%d ", finalCoins[index]);
    }
  //  printf ("\n");

    return tempTable[coinData->A];
}

float elapsedTime(struct timespec *start, struct timespec *stop)
{
    struct timespec result;
    if ((stop->tv_nsec - start->tv_nsec) < 0) {
        result.tv_sec = stop->tv_sec - start->tv_sec - 1;
        result.tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
    } else {
        result.tv_sec = stop->tv_sec - start->tv_sec;
        result.tv_nsec = stop->tv_nsec - start->tv_nsec;
    }

    float timeRes = result.tv_sec;
    timeRes += (result.tv_nsec / (1000000000.0f));

    return timeRes;
}