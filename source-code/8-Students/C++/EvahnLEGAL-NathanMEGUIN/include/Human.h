#ifndef HUMAN_H
#define HUMAN_H

#include "Grid.h"
#include "RandomGenerator.h"

enum class Status
{
    Susceptible,
    Exposed,
    Infected,
    Recovered
};

class Human
{
private:

    Status status;
    int statusTime;
    int posX;
    int posY;
    int dE;
    int dI;
    int dR;
    RandomGenerator randomGenerator;


    void updateStatus(Grid& grid);
    int numInfectedAround(Grid& grid) const;

public:
    Status getStatus();
    int getStatusIndex();
    int getPosX() const;
    int getPosY() const;
    void placeOnGrid(Grid& grid, int x, int y);
    void moveOnGrid(Grid& grid);

    Human(int posX, int posY, Status status, RandomGenerator randomGenerator);
};
#endif
