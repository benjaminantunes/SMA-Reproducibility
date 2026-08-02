//
// Created by guill on 17/10/2023.
//

#ifndef TP1_ARCHI_WORLD_H
#define TP1_ARCHI_WORLD_H


#include <vector>
#include "Subject.h"
#include "../utils/Random.h"
#include "../utils/RandomMover.h"
#include "../utils/FileWriter.h"

const int gridWidth = 300;
const int gridHeight = 300;
const int nbSubject = 20000;
const int nbInfected = 20;

const int nbDay = 730;

class World {
private:

    std::vector<Subject> subjects;


    int grid[gridWidth][gridHeight];

public:

    RandomMover mover;
    World();

    void Day(int nbDay);

    int checkInfectedNeighbor(Subject s);

    int tabStatus[nbDay+1][4] = {0, 0, 0, 0};

    void launch(int nbSimu);

};

#endif //TP1_ARCHI_WORLD_H
