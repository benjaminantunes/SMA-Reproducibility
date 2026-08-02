#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "Grid.h"
#include "Human.h"
#include "RandomGenerator.h"

using namespace std;

class Simulation
{
public:
    Simulation(int gridLength, int gridHeight, int numHumans, int numInfected, RandomGenerator& gen);
    ~Simulation();

    void simulateNdays(int numDays, string str);

private:
    int numHumans;
    int initNumInfected;
    int data[4];
    int simulatedDays;
    Grid grid;
    Human* humans[20000];
    RandomGenerator& randomGenerator;

    void simulateAday();
    void followStatistics(ofstream& file);
    void shuffleHumans();
};

#endif
