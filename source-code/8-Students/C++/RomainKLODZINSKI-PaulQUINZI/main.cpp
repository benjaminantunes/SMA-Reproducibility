/**
 * @file main.cpp
 * @brief implements the main program
 * */


#include <iostream>
#include <filesystem>

#include "Simulation.h"

namespace fs = std::filesystem;


int main() {
	
	if (!filesystem::is_directory("out")) filesystem::create_directory("out"); // try to create the out/ dirrectory
	
	Random rng(0);
	
    for (int i = 0; i < 100; i++) {
		cout << "run simulation n°" << i << endl;
		
        auto *simu = new Simulation(i, rng);
        simu->Run();
        delete simu;
    }
	
	cout << "exit" << endl;
	
	return 0;
}
