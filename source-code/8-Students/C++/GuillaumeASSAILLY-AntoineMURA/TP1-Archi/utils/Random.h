//
// Created by guill on 17/10/2023.
//

#ifndef TP1_ARCHI_RANDOM_H
#define TP1_ARCHI_RANDOM_H

#include <random>

//static std::mt19937 mt{std::random_device{}()};


static std::mt19937_64 mt{12345};



class Random {

public:
    //Uniform distribution using a Mersenne Twister
    static int randomIntMT(int min, int max);
    static double randomDoubleMT(int min, int max);

    static int negExpMT(double mean);



};


#endif //TP1_ARCHI_RANDOM_H
