#include <iostream>
#include <chrono>
#include <sstream>

#include "Human.h"
#include "Grid.h"
#include "Simulation.h"
#include "RandomGenerator.h"

using namespace std;

int main()
{
    // Créer une instance de RandomGenerator
    RandomGenerator* randomGenerator = new RandomGenerator();

    // Initialiser la simulation
    int gridLength = 300;
    int gridHeight = 300;
    int numHumans = 20000;
    int initNumInfected = 20;

    auto start = chrono::high_resolution_clock::now();

    // Execution des 100 simulations
    for (int i = 0; i < 100; i++)
    {

        // Création d'une simulation
        Simulation* simulation = new Simulation(gridLength, gridHeight, numHumans, initNumInfected, *randomGenerator);

        // Détermination du fichier .csv correspondant
        ostringstream os;
        os << "out/simulation" << i + 1 << ".csv";
        string filename = os.str();

        // Simulation des 730 jours
        simulation->simulateNdays(730, filename);

        // Libération mémoire
        simulation->~Simulation();

        cout << "Simulation numero " << i + 1 << " terminee." << endl;
    }

    // Calcul du temps d'execution
    auto end = chrono::high_resolution_clock::now();
    auto int_s = chrono::duration<double>(end - start);
    cout << "Temps d'execution : " << int_s.count() << " sec" << endl;

    return EXIT_SUCCESS;
}