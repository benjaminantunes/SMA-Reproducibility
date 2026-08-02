//
// Created by guill on 17/10/2023.
//

#include <algorithm>
#include <iostream>
#include "World.h"
#include "../utils/RandomMover.h"



World::World() {


    //initialize the grid with zeroes
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            grid[i][j] = 0;
        }
    }

    for(int i = 0; i < nbInfected; ++i){
        Subject s  = Subject(Random::negExpMT(3),Random::negExpMT(7),Random::negExpMT(365),Infected);
        mover.move(&s, gridWidth, gridHeight);
        grid[s.getX()][s.getY()] += 1;
        subjects.push_back(s);
    }

    for (int i = nbInfected; i < nbSubject; ++i) {
        Subject s =  Subject(Random::negExpMT(3),Random::negExpMT(7),Random::negExpMT(365),Susceptible);
        mover.move(&s, gridWidth, gridHeight);
        subjects.push_back(s);
    }



    tabStatus[0][0] = nbSubject - nbInfected;
    tabStatus[0][2] = nbInfected;

}

void World::Day(int i) {

    //First shuffle the vector
    std::shuffle(subjects.begin(), subjects.end(), mt);

    //foreach subject
    for (Subject &subject: subjects){

        int x = subject.getX();
        int y = subject.getY();

        Status status = subject.getStatus();



        if(status == Infected){
            grid[x][y] -= 1;
            mover.move(&subject, gridWidth, gridHeight);
            x = subject.getX();
            y = subject.getY();
            grid[x][y] += 1;
        }
        else {

            mover.move(&subject, gridWidth, gridHeight);
            //Check surroundings :
            x = subject.getX();
            y = subject.getY();

            if(status == Susceptible){
                int nbNeighborInfected = checkInfectedNeighbor(subject);
                if (Random::randomDoubleMT(0, 1) < (1 - exp(-0.5 * nbNeighborInfected))) {
                    subject.setStatus(Status::Exposed);
                }
            }


        }

        //Increase elapsed Time, and change state if necessary
        //Returns 1 if the subject turned infected, -1 if he turned recovered, 0 otherwise
        grid[x][y] += subject.growOlder();
        status = subject.getStatus();
        tabStatus[i][status] += 1;



    }


}

int World::checkInfectedNeighbor(Subject s) {
    int nbNeighborInfected = 0;
    //Check if there is an infected subject in the 8 surrounding cases and the case he is in
    // The space is toroidal

    int x = s.getX();
    int y = s.getY();
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1 ; ++j) {
            if(grid[(x+i+gridWidth)%gridWidth][(y+j+gridHeight)%gridHeight] >= 1){
                nbNeighborInfected+= grid[(x+i+gridWidth)%gridWidth][(y+j+gridHeight)%gridHeight];
            }
        }
    }
    return nbNeighborInfected;
}

void World::launch(int nbSimu) {
    for(int i = 1; i <= nbDay; ++i){

        Day(i);

    }
    FileWriter::writeCSV(tabStatus, nbDay, nbSimu);
}
