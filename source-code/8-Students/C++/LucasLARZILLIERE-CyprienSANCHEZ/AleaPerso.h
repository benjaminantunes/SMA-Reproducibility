#include <iostream>
#include <algorithm>
#include <array>
#include <random> // Pour Mersene Twister
#include <math.h>  // Pour log (NegExp)
#include <cmath> // Pour exp()

#define debug { printf("function %s() : %s:%i\n", __func__, __FILE__, (int)__LINE__); }

using namespace std;

const int nbIndiv = 20000;

class AleaPerso{
    public:
        
        void ShuffleOrdre(array<int, nbIndiv> OrdreDep, mt19937& mt);
        int RandomMinMax(int min, int max, mt19937& mt);
        double NegExp(double inMean, mt19937& mt);
        int probaInf(int ni, mt19937& mt);
};
