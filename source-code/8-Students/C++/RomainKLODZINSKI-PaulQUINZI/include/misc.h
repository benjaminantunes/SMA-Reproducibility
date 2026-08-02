/**
 * @file misc.h
 * @brief defines miscellaneous macros & structs
 * */

#ifndef MISC_H
#define MISC_H


#define GRID_SIZE 300
#define INFECTED_HUMANS 20
#define HUMANS_NUMBER 20000


/**
 * @enum Status
 * @brief represent an infection status
 * */
typedef enum {
    Susceptible = 0, // usable to index a counter
    Exposed,
    Infected,
    Recovered
} Status;

/**
 * @enum Coord
 * @brief represent a coordinate
 * */
typedef struct {
	int x, y;
} Coord;


#endif // MISC_H
