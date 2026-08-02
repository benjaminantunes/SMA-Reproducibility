//
// Created by guill on 17/10/2023.
//

#include <algorithm>
#include "Random.h"

int Random::randomIntMT(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}


double Random::randomDoubleMT(int min, int max)
{
    std::uniform_real_distribution<double> dist(min, max);
    return dist(mt);
}

int Random::negExpMT(double mean) {
    return (int) (- mean * log(1 - randomDoubleMT(0, 1)));
}

