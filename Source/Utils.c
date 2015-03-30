#include "Utils.h"
#include <stdlib.h>

/*
 * Evenly distributed random number generator. Divides 0 - RAND_MAX into even buckets
 */
int getRandomNumber(int max)
{
    if(max == 0)
        return 0;

    unsigned long numBins = (unsigned long) max;
    unsigned long numRand = (unsigned long) RAND_MAX + 1;
    unsigned long binSize = numRand / numBins;
    unsigned long defect = numRand % numBins;

    long x;
    do {
        x = random();
    }
    while (numRand - defect <= (unsigned long)x);

    return x/binSize;
}

int roundUpDivision(int dividend, int divisor)
{
    return (dividend + divisor - 1) / divisor;
}
