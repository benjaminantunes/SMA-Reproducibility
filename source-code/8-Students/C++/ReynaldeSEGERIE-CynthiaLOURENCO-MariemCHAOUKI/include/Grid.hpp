#ifndef __GRID_HPP__
#define __GRID_HPP__

#define GRID_WIDTH  300
#define GRID_HEIGHT 300

#define NB_STATES 4 // S E I R

class Agent;

#include "Population.hpp"
#include "Agent.hpp"

class Grid
{
    private:
        const int width   = GRID_WIDTH;
        const int height  = GRID_HEIGHT;

        int states[NB_STATES]  = {0};

        Population gridPopulation;

        std::vector<std::vector<std::list<Agent>>> zone;

    public:
        Grid                                    (void);
        void    displayGrid                     (void);
        void    initializeGrid                  (Population population);
        void    movePopulation                  (void);
        void    clearGrid                       (void);
        void    clearGridStates                 (void);
        double  probabilityToGetInfectedAt      (int x, int y);
        void    simulate                        (void);

        int     getHeight                       (void);
        int     getWidth                        (void);
        int     getState                        (int index);
};

#endif