#include <iostream>
#include <fstream> 
#include <random>
#include <vector>
#include <cstdlib>

#include "Grid.hpp"
#include "Agent.hpp"

using namespace std;


/**
 * ---------------------------------------------------------------------------
 * Constructor
 * ---------------------------------------------------------------------------
 */

/**
 * @brief Constructor for the Grid class.
*/

Grid::Grid()
{
    zone.resize(GRID_WIDTH, std::vector<std::list<Agent>>(GRID_HEIGHT));
}

/**
 * ---------------------------------------------------------------------------
*/

/**
 * @brief Initializes the grid with agents from a specific population.
 * 
 * @param population Population object containing agents.
*/

void Grid::initializeGrid(Population population)
{
    int x, y;

    this->gridPopulation = population;

    vector<Agent> agents = population.getAgents();

    for (Agent& idv : agents) 
    {
        x = idv.getPosition().getX();
        y = idv.getPosition().getY();
        zone[x][y].push_back(idv);
    }
}

/**
 * @brief Moves the population of agents on the grid.
*/

void Grid::movePopulation()
{
    int x, y;

    clearGrid();

    for (Agent& a : gridPopulation.getAgents())
    {
        a.move();
        zone[a.getPosition().getX()][a.getPosition().getY()].push_back(a);
    }
}

/**
 * @brief Clears the grid to update.
*/

void Grid::clearGrid() {
    for (int x = 0; x < width; x++) 
    {
        for (int y = 0; y < height; y++) 
        {
            zone[x][y].clear();
        }
    }
}

/**
 * @brief Clears the states of the grid.
*/

void Grid::clearGridStates()
{
    for (int i = 0; i < NB_STATES; i++)
    {
        states[i] = 0;
    }
}

/**
 * @brief Displays the grid, showing the state of agents in each cell.
*/

void Grid::displayGrid()
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            std::list<Agent> listAgent = zone[x][y];
            for (Agent e : listAgent)
            {
               cout << e.getCharState() << "";
            }
            if (listAgent.size() == 0)
            {
                cout << "0";
            }
        }
        cout << endl;
    }
}

/**
 * @brief Simulates the behavior of agents on the grid over a period.
*/

void Grid::simulate()
{
    clearGridStates();

    movePopulation();
   
    for (Agent& agent : gridPopulation.getAgents()) 
    {
        Agent * a = &agent;
        if (a->getNumState() == State::S)
        {
            a->infection(probabilityToGetInfectedAt(a->getPosition().getX(), a->getPosition().getY()));
        }
        else
        {
            a->checkState();
        }
            a->increaseTimeInState();
                
            State s = a->getNumState();
            switch(s)
            {
                case State::S:
                    states[0]++;
                    break;
                case State::E:
                    states[1]++;
                    break;
                case State::I:
                    states[2]++;
                    break;
                case State::R:
                    states[3]++;
                    break;
                default:
                    break;
            }
    }
                    
}

/**
 * @brief Calculates the probability of an agent getting infected at a specific position.
 * 
 * It considers neighboring cells and counts the number of infectious neighbors.
 * The probability is calculated based on the number of infectious neighbors.
 * 
 * @param x X-coordinate of the agent's position.
 * @param y Y-coordinate of the agent's position.
 * 
 * @return Probability to get infected at this position.
*/

double Grid::probabilityToGetInfectedAt(int x, int y)
{
    int infectiousNeighbors = 0;
    int neighborX, neighborY;

    double probability;

    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            neighborX = (x + dx + width)  % width;
            neighborY = (y + dy + height) % height;

            if (neighborX >= 0 && neighborX < width && neighborY >= 0 && neighborY < height)
            {
                for (Agent& agent : zone[neighborX][neighborY])
                {
                    if (&agent != &zone[x][y].front() && agent.getNumState() == State::I)
                    {
                        infectiousNeighbors++;
                    }
                }
            }
        }
    }

    probability = 1.0 - exp(-0.5 * (double) infectiousNeighbors);

    return probability;
}


// Getter for width
/**
 * @brief Get the width of the grid.
 * @return The width of the grid.
 */

int Grid::getWidth() 
{
    return width;
}

// Getter for height
/**
 * @brief Get the height of the grid.
 * @return The height of the grid.
 */

int Grid::getHeight() 
{
    return height;
}

// Getter for states
/**
 * @brief Get the state at the specified index.
 * @param index The index of the state to retrieve.
 * @return The state at the specified index. If the index is invalid, it returns -1.
 */

int Grid::getState(int index) {
    if (index >= 0 && index < NB_STATES) {
        return states[index];
    } else 
    {
        return -1;
    }
}