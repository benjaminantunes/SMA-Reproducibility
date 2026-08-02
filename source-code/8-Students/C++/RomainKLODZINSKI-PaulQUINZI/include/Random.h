/**
 * @file Random.h
 * @brief implements the Random class
 * */

#ifndef RANDOM_H
#define RANDOM_H

#include <random>

using namespace std;


/**
 * @class Random
 * @brief a wrapper class around a Mersenne Twister RNG instance
 * */
class Random {
private:
    mt19937_64 random;                      ///< the MT RNG instance
    exponential_distribution<> exp3;        ///< negative exponential distribution with mean=3
    exponential_distribution<> exp7;        ///< negative exponential distribution with mean=7
    exponential_distribution<> exp365;      ///< negative exponential distribution with mean=365
    uniform_int_distribution<> uniform_int; ///< uniform integer distribution in [0; GRID_SIZE[
    uniform_real_distribution<> uniform;    ///< uniform real distribution in [0; 1]

public:
	/**
	 * @brief instantiate the generator
	 * @param[in] seed used for MT
	 * */
    explicit Random(int seed);
	
	/**
	 * @brief get an integer in [0; GRID_SIZE[
	 * @return the generated number
	 * */
	int gen_uniform();
	
	/**
	 * @brief determine the exposed status
	 * @param[in] Ni the number of infected humans in the neighbourhood
	 * @return true if the human must be exposed, false otherwise
	 * */
	bool is_exposed(int Ni);
	
	/**
	 * @brief get an integer following a negative exponential distribution with mean=3
	 * @return the generated number
	 * */
	int gen_exp3();
	
	/**
	 * @brief get an integer following a negative exponential distribution with mean=7
	 * @return the generated number
	 * */
	int gen_exp7();
	
	/**
	 * @brief get an integer following a negative exponential distribution with mean=365
	 * @return the generated number
	 * */
	int gen_exp365();
	
	
	/**
	 * @brief shuffle the provided array of pointer of a size of HUMANS_NUMBER
	 * */
    void shuffle(void ** array);
};


#endif // RANDOM_H
