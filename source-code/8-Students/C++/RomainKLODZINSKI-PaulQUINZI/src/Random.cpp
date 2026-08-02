/**
 * @file Random.cpp
 * @brief implements the Random class
 * */

#include <iostream>
#include "Random.h"
#include "misc.h"
#include <algorithm>


/**
 * @brief instantiate the generator
 * @param[in] seed used for MT
 * */
Random::Random(int seed) : random(seed),
                   exp3(1. / 3.),
                   exp7(1. / 7.),
                   exp365(1. / 365.),
                   uniform_int(0, GRID_SIZE - 1),
                   uniform(0., 1.) {}
				   
/**
 * @brief get an integer in [0; GRID_SIZE[
 * @return the generated number
 * */
int Random::gen_uniform() {
    return uniform_int(random);
}

/**
 * @brief determine the exposed status
 * @param[in] Ni the number of infected humans in the neighbourhood
 * @return true if the human must be exposed, false otherwise
 * */
bool Random::is_exposed(int Ni) {
    return uniform(random) < 1. - exp(-(double) Ni / 2.);
}

/**
 * @brief get an integer following a negative exponential distribution with mean=3
 * @return the generated number
 * */
int Random::gen_exp3() {
    return (int) exp3(random);
}

/**
 * @brief get an integer following a negative exponential distribution with mean=7
 * @return the generated number
 * */
int Random::gen_exp7() {
    return (int) exp7(random);
}

/**
 * @brief get an integer following a negative exponential distribution with mean=365
 * @return the generated number
 * */
int Random::gen_exp365() {
    return (int) exp365(random);
}


/**
 * @brief shuffle the provided array of pointer of a size of HUMANS_NUMBER
 * */
void Random::shuffle(void ** array) {
    std::shuffle(array, array + HUMANS_NUMBER, random);
}
