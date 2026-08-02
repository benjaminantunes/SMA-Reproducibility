//
// Created by guill on 19/10/2023.
//
#include "Subject.h"

int Subject::growOlder() {
    int result = 0;
    elapsedTime++;
    switch(status){
        case Status::Exposed:
            if (elapsedTime>dE){
                status = Status::Infected;
                elapsedTime = 0;
                result = 1;
            }
            break;
        case Status::Infected:
            if (elapsedTime>dI){
                status = Status::Recovered;
                elapsedTime = 0;
                result = -1;
            }
            break;
        case Status::Recovered:
            if (elapsedTime>dR){
                status = Status::Susceptible;
                elapsedTime = 0;
            }
            break;
        case Status::Susceptible:
            break;
    }
    return result;
}

Subject::Subject(int dE, int dI, int dR, Status status) {
    this->dE = dE;
    this->dI = dI;
    this->dR = dR;
    this->status = status;
    this->posX = 0;
    this->posY = 0;
    this->elapsedTime = 0;
}
