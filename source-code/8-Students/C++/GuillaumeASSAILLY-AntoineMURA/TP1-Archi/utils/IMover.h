//
// Created by guill on 17/10/2023.
//

#ifndef TP1_ARCHI_IMOVER_H
#define TP1_ARCHI_IMOVER_H

#include "../objects/Subject.h"

class IMover {
public:
    virtual void move(Subject * s, int maxX, int maxY) const = 0;
};

#endif //TP1_ARCHI_IMOVER_H
