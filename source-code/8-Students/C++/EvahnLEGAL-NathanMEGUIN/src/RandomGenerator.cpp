#include "RandomGenerator.h"

RandomGenerator::RandomGenerator()
{
    //Génération de la graine du générateur
    generator.seed(42);
}


int RandomGenerator::generateUniform(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

double RandomGenerator::genrand_real2(double min, double max)
{
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

double RandomGenerator::negExp(double inMean)
{
    return -inMean * log(1 - genrand_real2(0.0, 1.0));
}

std::mt19937 RandomGenerator::getGenerator()
{
    return generator;
}