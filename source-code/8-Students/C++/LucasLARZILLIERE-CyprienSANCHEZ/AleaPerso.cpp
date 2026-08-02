#include "AleaPerso.h"

void AleaPerso::ShuffleOrdre(array<int, nbIndiv> OrdreDep, mt19937& mt)
{
    shuffle(OrdreDep.begin(), OrdreDep.end(), mt);
}

int AleaPerso::RandomMinMax(int min, int max, mt19937& mt)
{ // génère un entier appartenant à [min, max[ par loi uniforme 
    double currRand = mt() * (1.0/4294967296.0); // Divisé par 2³²
    return floor(min + (max - min) * currRand);
}

double AleaPerso::NegExp(double inMean, mt19937& mt)
{
    return -inMean * log(1 - mt() * (1.0/4294967296.0));
}

int AleaPerso::probaInf(int ni, mt19937& mt) // renvoie 1 si l'individu devient exposé
{
    double p = 1 - exp(-0.5 * ni);
    double r = mt() * (1.0/4294967296.0);
    int result = 0;
    if (r < p) // exposé
    {
        result = 1;
    } 
    return result;
} 