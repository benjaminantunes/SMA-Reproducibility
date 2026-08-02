#include <iostream>
#include <random>

#include "RandomConfig.hpp"

#include "Agent.hpp"
#include "Grid.hpp"

using namespace std;

/**
 * ---------------------------------------------------------------------------
 * Constructor
 * ---------------------------------------------------------------------------
 */

/**
 * @brief Constructor for the Agent class.
 * 
 * @param id ID of the agent
 * @param state Initial state of the agent
 * @param position Initial position of the agent
 * @param dE Duration of the exposed state.
 * @param dI Duration of the infected state.
 * @param dR Duration of the recovered state.
 * 
 */

Agent::Agent(int id, State state, Position position, double dE, double dI, double dR)
{
    this->id          = id;
    this->state       = state;
    this->position    = position;
    this->timeInState = 0.;
    this->dE          = dE;
    this->dI          = dI;
    this->dR          = dR;
}

/**
 * @brief Default constructor for the Agent class.
*/

Agent::Agent() { 
    this->id          = 0;
    this->state       = State::S;
    this->position    = Position(0,0);
    this->timeInState = 0.0;
    this->dE          = 0;
    this->dI          = 0;
    this->dR          = 0;

}

/**
 * ---------------------------------------------------------------------------
*/

/**
 * @brief Simulate the infection process for the agent in state S.
 * 
 * @param probabilityToGetInfected Probability of getting infected.
*/

void Agent::infection(double probabilityToGetInfected)
{ 
    double randomUniformNumber = (double) rand() / (double) RAND_MAX;

    if (randomUniformNumber < probabilityToGetInfected)
    {
        this->state = State::E;
        this->timeInState = 0.;
    }

}

/**
 * @brief Check the current state of the agent and update it if needed.
 * The state is update only if timeInState is greater than the duration
 * time in this state.
*/

void Agent::checkState()
{
    switch(state)
    {
        case State::E:
            if (timeInState > dE)
            {
                state = State::I;
                timeInState = 0.;
            }
            break;
        case State::I:
            if (timeInState > dI)
            {
                state = State::R;
                timeInState = 0.;
            }
            break;
        case State::R:
            if (timeInState > dR)
            {
                state = State::S;
                timeInState = 0;
            }
            break;
        default:
            break;
    }
}

/**
 * @brief Move the agent to a new random position on the grid.
*/

void Agent::move()
{
    // Mersenne Twister
    mt19937& rg = RandomGenerator::getInstance();

    // LCG
    //linear_congruential_engine<uint32_t, 1664525, 1013904223, 0>& rg = RandomGenerator::getInstanceLCG();

    // Middle Square 
    /* RandomGenerator& randomGenerator =  RandomGenerator::getInstanceMS();

    int newX = randomGenerator.generateRandom() % GRID_WIDTH;
    int newY = randomGenerator.generateRandom() % GRID_HEIGHT;

    Position newPos = Position(newX, newY); 

    */

    uniform_int_distribution<int> distX(0, GRID_WIDTH - 1);
    uniform_int_distribution<int> distY(0, GRID_HEIGHT - 1);

    // MT & LCG
    Position newPos = Position(distX(rg), distY(rg));
    
    this->setPosition(newPos);
}


/**
 * @brief Increase the time spent in the current state by 1.
 */

void Agent::increaseTimeInState()
{
    timeInState = timeInState + 1;
}

/**
 * @brief Display information about the agent.
 */

void Agent::displayAgent()
{
    cout << "Agent ID: " << getId() << endl;
    cout << "State: " << getCharState() << endl;
    cout << "Position (x, y): " << getPosition().getX() << ", " << getPosition().getY() << endl;
    cout << "Time in State: " << getTimeInState() << endl;
    cout << "dE: " << getDE() << ", dI: " << getDI() << ", dR: " << getDR() << endl;

    cout << endl;
}


/**
 * ---------------------------------------------------------------------------
 * Getter Function
 * ---------------------------------------------------------------------------
 */

/**
 * @brief Get the ID of the agent.
 * 
 * @return ID of the agent.
*/
int Agent::getId() 
{
    return id;
}

/**
 * @brief Get the time spent in the current state.
 * 
 * @return Time spent in the current state.
*/

double Agent::getTimeInState()
{
    return timeInState;
}


/**
 * @brief Get the character representation of the agent's state.
 * 
 * @return The character representation ('S', 'E', 'I', 'R') of the agent's state.
*/

char Agent::getCharState() 
{
    switch (state) {
        case State::S:
            return 'S';
        case State::E:
            return 'E';
        case State::I:
            return 'I';
        case State::R:
            return 'R';
        default:
            return '?'; 
    }
}


/**
 * @brief Get the numeric representation of the agent's state.
 * 
 * @return Numeric representation of the state (S = 0, E = 1, I = 2, R = 3)
*/

State Agent::getNumState()
{
    return state;
}

/**
 * @brief Get the current position of the agent.
 * 
 * @return Current position of the agent.
 */

Position Agent::getPosition()
{
    return position;
}


/**
 * @brief Get the duration time for state E.
 *
 * @return Duration time for state E.
 * 
 */

double Agent::getDE()
{
    return dE;
}


/**
 * @brief Get the duration time for state I.
 *
 * @return Duration time for state I.
 * 
 */

double Agent::getDI()
{
    return dI;
}


/**
 * @brief Get the duration time for state R.
 *
 * @return Duration time for state R.
 * 
 */

double Agent::getDR()
{
    return dR;
}

/**
 * ---------------------------------------------------------------------------
 * Setter Function
 * ---------------------------------------------------------------------------
 */

/**
 * @brief Set the position of the agent to a new position.
 * 
 * @param newPos New position to set for the agent.
 */

void Agent::setPosition(Position newPos)
{
    this->position = newPos;
}

/**
 * @brief Set the state of the agent to a new state and reset the time in the state.
 * @param newState New state to set for the agent.
 * 
 */

void Agent::setState(State newState)
{
    this->state       = newState;
    this->timeInState = 0.;
}



