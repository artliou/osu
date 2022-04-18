#ifndef MIN_CHANGE_H
#define MIN_CHANGE_H

#include <vector>

typedef struct
{
    std::vector<int> C;
    int A;
} coinSet_t;

void WriteMinCoins(coinSet_t * coinData, const char * filename);
int minCoins(coinSet_t * coinData, int * finalCoins);
float elapsedTime(struct timespec *start, struct timespec *stop);

#endif // MIN_CHANGE_H