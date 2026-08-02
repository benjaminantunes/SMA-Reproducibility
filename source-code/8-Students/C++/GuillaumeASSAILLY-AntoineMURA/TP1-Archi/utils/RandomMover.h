//
// Created by guill on 17/10/2023.
//

#ifndef TP1_ARCHI_RANDOMMOVER_H
#define TP1_ARCHI_RANDOMMOVER_H


#include "IMover.h"

class RandomMover : IMover{
public:
      void move(Subject * s, int maxX, int maxY) const override;
};


#endif //TP1_ARCHI_RANDOMMOVER_H
