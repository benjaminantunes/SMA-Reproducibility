/**
 * @file Simulation.h
 * @brief implements the Simulation class
 * */

#ifndef SIMULATION_H
#define SIMULATION_H


#include "Random.h"
#include "Human.h"
#include <fstream>

/**
 * @class Simulation
 * @brief performs a simulation
 * */
class Simulation {
private:
    Human * humans[HUMANS_NUMBER]{nullptr}; ///< stores humans
    int grid[GRID_SIZE][GRID_SIZE]{{0}};    ///< stores number of infected humans for each cells
	ofstream file;                          ///< output file
    Random& random;                          ///< random generator
	
	/**
	 * @brief get the number of infected humans
	 * @param[in] coord the coordinate of a cell
	 * @return the number of infected humans on the specified cell
	 * */
	int GetInfectedAt(Coord coord);
	
	/**
	 * @brief run 1 simulated day
	 * */
	void RunDay();

public:
	/**
	 * @brief instanciate a simulation
	 * @param[in] nb the id of the simulation (output file named: out/<nb>.csv
	 * @param[in,out] rng a Random instance used for the simulation
	 * */
    explicit Simulation(int nb, Random& rng);
	
	~Simulation();
	
	/**
	 * @brief run the whole 730 days of simulation
	 * */
	void Run();
};



#endif // SIMULATION_H
