#pragma once
#include <vector>
#include <cstdlib>

class RandomProvider
{
private:
    bool testMode;

    std::vector<int> values;

    int valuesPos;

public:
    RandomProvider();
    RandomProvider(const std::vector<int>& values);

    int nextInt(int min, int max);

};
