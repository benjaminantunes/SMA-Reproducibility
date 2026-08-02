#include <iostream>

#include "Position.hpp"

using namespace std;


/**
 * ---------------------------------------------------------------------------
 * Constructor
 * ---------------------------------------------------------------------------
 */

/**
 * @brief Default constructor that initializes both x and y to 0.
*/

Position::Position() : x(0), y(0) {}


/**
 * @brief Constructor that initializes the position with specified x and y coordinates.
 * @param ix The x-coordinate.
 * @param iy The y-coordinate.
*/

Position::Position(int ix, int iy) : x(ix), y(iy){}

/**
 * ---------------------------------------------------------------------------
*/

/**
 * @brief Get the x-coordinate of the position.
 * 
 * @return The x-coordinate.
*/

int Position::getX()
{
    return x;
}

/**
 * @brief Get the y-coordinate of the position.
 * 
 * @return The y-coordinate.
*/

int Position::getY()
{
    return y;
}


/**
 * @brief Set the x-coordinate of the position.
 * 
 * @param newX The new x-coordinate.
*/

void Position::setX(int newX)
{
    x = newX;
}

/**
 * @brief Set the y-coordinate of the position.
 * 
 * @param newY The new y-coordinate.
*/
void Position::setY(int newY)
{
    y = newY;
}
