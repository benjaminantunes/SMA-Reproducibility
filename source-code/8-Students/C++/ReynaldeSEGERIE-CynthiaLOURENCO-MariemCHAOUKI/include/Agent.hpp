#ifndef __INDIVIDUAL_HPP__
#define __INDIVIDUAL_HPP__

#include <list>

#include "State.hpp"
#include "Position.hpp"

class Agent
{
    private:
        int       id;
        State     state;
        Position  position;
        double    timeInState;
        double    dE;
        double    dI;
        double    dR;
        

    public:
        Agent                               (void);
        Agent                               (int id, State state, Position position, double dE, double dI, double dR);
        void            move                (void);

        
        void            checkState         (void);
        void            infection          (double probabilityToGetInfected);


        int              getId                  (void);
        double           getTimeInState         (void);
        char             getCharState           (void);
        State            getNumState            (void);
        Position         getPosition            (void);
        double           getDE                  (void);
        double           getDI                  (void);
        double           getDR                  (void);

        void             setPosition            (Position newPos);
        void             setState               (State newState);

        void             displayAgent           (void);

        void             increaseTimeInState    (void);

        bool operator==(const Agent& other) const 
        {
            return (id == other.id);
        }
};

#endif
