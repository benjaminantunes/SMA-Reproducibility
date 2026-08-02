#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <random>

class RandomGenerator {
public:
    RandomGenerator();

    int generateUniform(int min, int max);
    double genrand_real2(double min, double max);
    double negExp(double mean);
    std::mt19937 getGenerator();

private:
    std::mt19937 generator;
};

#endif