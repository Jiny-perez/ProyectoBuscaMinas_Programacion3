#include "RandomProvider.h"

RandomProvider::RandomProvider() : testMode(false), valuesPos(0)
{
}

RandomProvider::RandomProvider(const std::vector<int> &values)
    : testMode(true), values(values), valuesPos(0)
{
}

int RandomProvider::nextInt(int min, int max)
{
    if(!testMode)
    {
        int range = max - min + 1;
        return min + (rand() % range);
    }

    if(valuesPos >= values.size())
        valuesPos = 0;

    int value = values[valuesPos];
    valuesPos++;
    return value;
}
