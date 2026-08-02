#ifndef __POPULATION_HPP__
#define __POPULATION_HPP__

#include <list>
#include <random>

class Agent;


#define NUM_AGENTS      20000
#define NUM_INFECTED    20
#define NUM_DAYS        730
#define NUM_SIMULATIONS 100
class Population
{
    private:
        std::vector<Agent>      agents;
        int                   durationTime;

    public:
        void initializePopulation           (void);
        void addAgent                       (Agent idv);
        void displayPopulation              (void);

        std::vector<Agent>&  getAgents      (void);
        Agent *              getAgentById   (int id);
};

#endif