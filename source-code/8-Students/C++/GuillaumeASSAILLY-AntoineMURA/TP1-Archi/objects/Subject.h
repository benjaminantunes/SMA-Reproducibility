//
// Created by guill on 17/10/2023.
//

#ifndef TP1_ARCHI_SUBJECT_H
#define TP1_ARCHI_SUBJECT_H

enum Status{
    Susceptible,
    Exposed,
    Infected,
    Recovered
};

class Subject {
private:
    int elapsedTime;
    int dE;
    int dI;
    int dR;
    Status status;
    int posX;
    int posY;

public:
    Subject(int dE, int dI, int dR, Status status);
    void setX(int x) { posX = x; }
    void setY(int y) { posY = y; }
    int getX() { return posX; }
    int getY() { return posY; }
    void setStatus(Status s) { status = s; }
    Status getStatus() { return status; }

    int growOlder();

};

#endif //TP1_ARCHI_SUBJECT_H
