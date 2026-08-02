#include <iostream>
#include <fstream> 
#include <vector>
#include <random>
#include <ctime>

#include "Grid.hpp"
#include "Agent.hpp"
#include "Population.hpp"

using namespace std;


void simulateAnEpidemic()
{
    // Initialisation des populations pour chaque simulation
    Population populations[NUM_SIMULATIONS];

    // Initialisation des grilles pour chaque simulation
    // Pour une population donnée, il y aura une grille.
    // EX. : Pour la population n°0, on initialisera la grille n°0 avec la population n°0

    Grid grids[NUM_SIMULATIONS];

    string filename;
    ofstream csvFiles[NUM_SIMULATIONS];

    for (int sim = 0; sim < NUM_SIMULATIONS; sim++)
    {
        populations[sim].initializePopulation();
        grids[sim].initializeGrid(populations[sim]);
    
        filename ="simulation/simulation_data" + to_string(sim) + ".csv";
        csvFiles[sim].open(filename);

        csvFiles[sim] << "day, susceptibleCount, exposedCount, infectedCount, recoveredCount" << endl;

        if (!csvFiles[sim].is_open())
        {
            cerr << "Error opening file : " << filename << endl;
            return;
        }
         
    }

    cout << "Populations and grids successfully initialized for " << NUM_SIMULATIONS << " simulations." << endl;
    // Simulation 
    // Pour chaque jour, il faut simuler l'épidémie dans chaque grille (il y a NUM_SIMULATIONS grille)
    int day; int sim;

    int numS, numE, numI, numR;

    cout << "Computing simulation ..." << endl;

    for (day = 0; day < NUM_DAYS; day++)
    {
        cout << "Day " << day + 1 << " simulating..." << endl;
        for (sim = 0; sim < NUM_SIMULATIONS; sim++)
        {
            //Faire une simulation pour la grille (appel à la méthode simulate())
            grids[sim].simulate();

            //grids[sim].displayGrid();
            // Récupérer le nombre d'agents en état S, E, I, R et l'écrire dans un fichier csv correspondant
            // NB : chaque fichier corresponds à une simulation. Si la simulation est faite sur la grille n°5, 
            // alors on doit écrire dans le fichier de simulation n°5 : simulation_data5.csv.

            numS = grids[sim].getState(0);
            numE = grids[sim].getState(1);
            numI = grids[sim].getState(2);
            numR = grids[sim].getState(3);

            csvFiles[sim] << day << "," << numS << "," << numE << "," << numI << "," << numR << endl;

        }
        
    }

}

int main()
{
    simulateAnEpidemic();
    return 0;
}
