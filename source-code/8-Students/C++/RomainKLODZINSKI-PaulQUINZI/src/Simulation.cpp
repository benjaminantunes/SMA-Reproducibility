/**
 * @file Simulation.cpp
 * @brief implements the Simulation class
 * */

#include <iostream>
#include "Simulation.h"

/**
* @brief get the number of infected humans
* @param[in] coord the coordinate of a cell
* @return the number of infected humans on the specified cell
* */
int Simulation::GetInfectedAt(Coord coord) {
    int r = 0;
    for (int i = 299; i <= 301; i++)
        for (int u = 299; u <= 301; u++)
            r += grid[(coord.x + i) % 300][(coord.y + u) % 300];
    return r;
}

/**
* @brief instanciate a simulation
* @param[in] nb the id of the simulation (output file named: out/<nb>.csv
* @param[in,out] rng a Random instance used for the simulation
* */
Simulation::Simulation(int nb, Random& rng) : file("out/"+to_string(nb)+".csv"), random(rng) {
	int i = 0;
	
    for (; i < INFECTED_HUMANS; i++) { // infected
        humans[i] = new Human(random, true);
        Coord coord = humans[i]->UpdateCoordinate();
        grid[coord.x][coord.y]++;
    }
	
    for (; i < HUMANS_NUMBER; i++) { // not infected
        humans[i] = new Human(random, false);
    }
}

Simulation::~Simulation() {
    for (auto &human: humans) delete human;
    file.close();
}

/**
* @brief run 1 simulated day
* */
void Simulation::RunDay() {
    int counters[4] = {0, 0, 0, 0}; // count humans in each status

    random.shuffle((void**)humans); // shuffle humans to take them in ramdom order easily

    for (int i = 0; i < HUMANS_NUMBER; i++) {
		Status status = humans[i]->GetStatus();
		
        if (status == Infected) { // if infected, uncount him before moving
            Coord coord = humans[i]->GetCoord();
            grid[coord.x][coord.y]--;
        }

        Coord coord = humans[i]->UpdateCoordinate();
        status = humans[i]->UpdateStatus(status == Susceptible ? GetInfectedAt(coord): 0); // Opti: Ni is only used if status==Susceptible
        counters[status]++;
        if (status == Infected)grid[coord.x][coord.y]++;
    }

    file << counters[0] << ";" << counters[1] << ";" << counters[2] << ";" << counters[3] << endl; // out as csv
}

/**
* @brief run the whole 730 days of simulation
* */
void Simulation::Run() {
    for (int i = 0; i < 730; i++) RunDay();
}
