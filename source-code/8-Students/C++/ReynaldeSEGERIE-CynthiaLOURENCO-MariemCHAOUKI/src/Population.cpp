#include <iostream>

#include <algorithm>
#include <cstdlib>
#include <vector>
#include <random>
#include <ctime>
#include <list>

#include "RandomConfig.hpp"
#include "Population.hpp"
#include "Position.hpp"

#include "Agent.hpp"
#include "State.hpp"

#include "Grid.hpp"

using namespace std;


/**
 * @brief Calculates a negative exponential random value.
 * 
 * Generates a random values with a negative exponential distribution
 * based on the mean provided.
 * 
 * @param inMean Mean value for the exponential distribution.
 * 
 * @return A negative exponential random value.
*/

double negExp(double inMean) 
{
    double u = rand() / (double)RAND_MAX;
    return -inMean * log(1.0 - u);
}


/**
 * @brief Initializes the populations of agents.
 * 
 * This function initializes the population of agents bu generating
 * with random positions and state (S or I) on the grid.
 * It uses a random number generator (Mersenne Twister) to determine
 * the positions and sets initial values for exposed (dE), infectious (dI)
 * and recovery (dR) durations.
*/

void Population::initializePopulation()
{
    // Mersenne Twister
    mt19937& rg = RandomGenerator::getInstance();

    // LCG
    //linear_congruential_engine<uint32_t, 1664525, 1013904223, 0>& rg = RandomGenerator::getInstanceLCG();
    
    uniform_int_distribution<int> rdXPos(0, GRID_WIDTH  - 1);
    uniform_int_distribution<int> rdYPos(0, GRID_HEIGHT - 1);

    // Middle Square
    // RandomGenerator& randomGenerator = RandomGenerator::getInstanceMS();

    

    for (int i = 0; i < NUM_AGENTS; i++)
    {
        
        double dE = negExp(3.);
        double dI = negExp(7.);
        double dR = negExp(365.);
        
        State  s;
        if (i < NUM_AGENTS - NUM_INFECTED){
            // Agent S
            s = State::S;
        }else
        {
            // Agent I
            s = State::I;
            
        }

        // MT & LCG
        Agent idv(i, s, Position(rdXPos(rg), rdYPos(rg)), dE, dI, dR);
       
        // Middle Square 
    
        /* int xPos = randomGenerator.generateRandom() % GRID_WIDTH;
        int yPos = randomGenerator.generateRandom() % GRID_HEIGHT;

        Agent idv(i, s, Position(xPos, yPos), dE, dI, dR); */

        addAgent(idv);
    }
}

/**
 * @brief Adds an agent to the population.
 * 
 * @param id Agent to add to the population.
*/

void Population::addAgent(Agent idv)
{
    agents.push_back(idv);
}


/**
 * @brief Displays information about the population.
*/

void Population::displayPopulation()
{
    cout << "Population information:" << std::endl;
    for (Agent& agent : agents) 
    {
        agent.displayAgent();
    }
}

/**
 * @brief Returns a reference to the vector of agents in the population.
 *
 * This function provides access to the vector containing the agents in the population.
 *
 * @return A reference to the vector of agents.
 */
vector<Agent>& Population::getAgents()
{
    return agents;
}


/**
 * @brief Retrieves an agent by its unique identifier (ID).
 *
 * This function searches for an agent in the population based on its unique identifier (ID).
 * If found, it returns a pointer to the agent; otherwise, it returns nullptr.
 *
 * @param id The unique identifier of the agent to retrieve.
 * @return A pointer to the agent with the specified ID or nullptr if not found.
 */

Agent * Population::getAgentById(int id) 
{
    for (Agent& agent : agents) 
    {
        if (agent.getId() == id) 
        {
            return &agent; // Retourne un pointeur vers l'agent avec l'ID spécifié
        }
    }
    return nullptr; // Retourne nullptr si l'agent n'est pas trouvé
}

