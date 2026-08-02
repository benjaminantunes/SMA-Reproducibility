//
// Created by guill on 17/10/2023.
//

#include "RandomMover.h"
#include "Random.h"



void RandomMover::move(Subject * s, int maxX, int maxY) const  {
    s->setX(Random::randomIntMT(0, maxX));
    s->setY(Random::randomIntMT(0, maxY));
}
