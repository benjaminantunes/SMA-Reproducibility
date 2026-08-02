#include "Simulation.h"

Simulation::Simulation(int gridLength, int gridHeight, int numHumans, int initNumInfected, RandomGenerator& gen)
	: numHumans(numHumans), initNumInfected(initNumInfected), simulatedDays(0), grid(gridLength, gridHeight), randomGenerator(gen)
{
	// Initialisation du tableau de données
	data[0] = 19980;
	data[1] = 0;
	data[2] = 20;
	data[3] = 0;

	// Initialisation du tableau d'humains
	int x, y;

	for (int i = 0; i < numHumans; i++)
	{

		// Génération de positions aléatoires
		x = randomGenerator.generateUniform(0, grid.getLength() - 1);
		y = randomGenerator.generateUniform(0, grid.getHeight() - 1);

		// Les 20 premiers sont infectés
		Status status = (i < initNumInfected) ? Status::Infected : Status::Susceptible;

		humans[i] = new Human(x, y, status, gen);

		// Mise à jour des données dans la grille
		humans[i]->placeOnGrid(grid, x, y);
	}
}

// Destructeur de Simulation
Simulation::~Simulation()
{
	for (Human* human : humans)
	{
		delete human;
	}
}

void Simulation::simulateNdays(int numDays, string str)
{
	// Ouverture du fichier
	ofstream file;
	file.open(str);

	// Test si le fichier est ouvert
	if (!file.is_open())
	{
		cerr << "Erreur lors de l'ouverture du fichier." << endl;
		return;
	}

	// Boucle sur les jours de la simulation
	for (int jour = 0; jour < numDays; jour++)
	{

		// Exécutez la simulation pour un jour
		simulateAday();

		// Ajouter les données de la journée dans un .csv
		followStatistics(file);

		simulatedDays++;
	}
	file.close();
}

void Simulation::simulateAday()
{

	// Mélange du tableau d'humains
	shuffleHumans();

	// Mise a jour des données pour chaque humain
	for (Human* human : humans)
	{
		data[human->getStatusIndex()]--;

		// Déplacement d'un humain
		human->moveOnGrid(grid);

		data[human->getStatusIndex()]++;
	}
}

// Met les données du jour dans un fichier
void Simulation::followStatistics(ofstream& file)
{
	file << simulatedDays << ";" << data[0] << ";" << data[1] << ";" << data[2] << ";" << data[3] << "\n";
}

// Mélange le tableau d'humains
void Simulation::shuffleHumans()
{
	std::shuffle(&humans[0], &humans[19999], randomGenerator.getGenerator());
}