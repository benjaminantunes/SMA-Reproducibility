/**
 * @file Human.cpp
 * @brief implements the Human class
 * */

#include "Human.h"


/**
* @brief initialize a human instance
* @param[in,out] random the random instance
* @param[in] infected initialized as infected if true, susceptible otherwise
* */
Human::Human(Random &random, bool infected) : random(random) {
    dE = random.gen_exp3();
    dI = random.gen_exp7();
    dR = random.gen_exp365();

    status = infected ? Infected: Susceptible;

    coord.x = coord.y = t = 0;
}

/**
* @brief gt the current coordinate of the human
* @return the coordinate
* */
Coord Human::GetCoord() const {
	return coord;
}

/**
* @brief gt the current status of the human
* @return the status
* */
Status Human::GetStatus() const {
	return status;
}

/**
* @brief move randomly the human
* @return the new coordinate
* */
Coord Human::UpdateCoordinate() {
    coord.x = random.gen_uniform();
    coord.y = random.gen_uniform();
	return coord;
}

/**
* @brief update the status of the human
* @param[in] Ni the number of infected human in the neighbourhood
* @return the new status
* */
Status Human::UpdateStatus(int Ni) {
	switch (status) {
		case Susceptible:
			if (random.is_exposed(Ni)) status = Exposed, t = 0;
			break;
		case Exposed:
			if (++t >= dE) status = Infected, t = 0;
			break;
		case Infected:
			if (++t >= dI) status = Recovered, t = 0;
			break;
		case Recovered:
			if (++t >= dR) status = Susceptible;
			break;
	}
	
	return status;
}
