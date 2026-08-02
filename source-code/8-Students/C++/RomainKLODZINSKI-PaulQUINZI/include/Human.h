/**
 * @file Human.h
 * @brief implements the Human class
 * */

#ifndef HUMAN_H
#define HUMAN_H


#include "misc.h"
#include "Random.h"

/**
 * @class Human
 * @brief represent a Human
 * */
class Human {
private:
    Status status;  ///< the human status
    int dI,         ///< duration of the Infected status
	    dE,         ///< duration of the Exposed status
		dR,         ///< duration of the Recovered status
		t;          ///< ellapsed time in the current status
    Coord coord;    ///< current coordinate
    Random& random; ///< the random generator instance

public:
	/**
	 * @brief initialize a human instance
	 * @param[in,out] random the random instance
	 * @param[in] infected initialized as infected if true, susceptible otherwise
	 * */
    Human(Random &random, bool infected);
	
	~Human() = default;
	
	/**
	 * @brief gt the current coordinate of the human
	 * @return the coordinate
	 * */
	Coord GetCoord() const;
	
	/**
	 * @brief gt the current status of the human
	 * @return the status
	 * */
	Status GetStatus() const;
	
	/**
	 * @brief move randomly the human
	 * @return the new coordinate
	 * */
	Coord UpdateCoordinate();
	
	/**
	 * @brief update the status of the human
	 * @param[in] Ni the number of infected human in the neighbourhood
	 * @return the new status
	 * */
	Status UpdateStatus(int Ni);
};


#endif // HUMAN_H
