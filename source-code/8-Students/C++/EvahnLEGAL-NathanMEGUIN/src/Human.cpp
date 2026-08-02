#include "Human.h"

Human::Human(int x, int y, Status status, RandomGenerator randomGenerator) : status(status), statusTime(0), posX(x), posY(y), randomGenerator(randomGenerator)
{
    // D�termination al�atoire des dur�e d'�tat
    dE = (int)randomGenerator.negExp(3.0);
    dI = (int)randomGenerator.negExp(7.0);
    dR = (int)randomGenerator.negExp(365.0);
}

// Renvoie le statut de l'humain
Status Human::getStatus()
{
    return status;
}

// Renvoie le chiffre associ� au statut de l'humain
int Human::getStatusIndex()
{
    switch (status) {
    case Status::Susceptible:
        return 0;
    case Status::Exposed:
        return 1;
    case Status::Infected:
        return 2;
    case Status::Recovered:
        return 3;
    default: return 4;
    }
}

// Renvoie la position X de l'humain
int Human::getPosX() const
{
    return posX;
}

// Renvoie la position Y de l'humain
int Human::getPosY() const
{
    return posY;
}

// Met � jour le statut de l'humain
void Human::updateStatus(Grid& grid)
{
    statusTime++;
    int numInfected;
    double proba;

    switch (status)
    {
    case Status::Exposed:
        if (statusTime >= dE)
        {
            status = Status::Infected;
            statusTime = 0;
        }
        break;

    case Status::Infected:
        if (statusTime >= dI)
        {
            status = Status::Recovered;
            statusTime = 0;
        }
        break;

    case Status::Recovered:
        if (statusTime >= dR)
        {
            status = Status::Susceptible;
            statusTime = 0;
        }
        break;
    case Status::Susceptible:
        // Calcul du nombre d'infect� autour de l'humain
        numInfected = numInfectedAround(grid);

        // Calcul de la probabilit� que l'humain soit contamin�
        proba = 1 - exp(-0.5 * numInfected);

        if (randomGenerator.genrand_real2(0.0, 1.0) < proba) {

            // S'il est contamin� alors il devient Exposed
            status = Status::Exposed;
            statusTime = 0;
        }
        break;

    default:
        break;
    }
}

// Calcul du nombre d'infect�s autour de l'humain
int Human::numInfectedAround(Grid& grid) const
{
    int numInfected = 0;

    // R�cup�ration de la taille de la grille
    int length = grid.getLength();
    int height = grid.getHeight();

    // D�termination du nombre d'infect�s autour de l'humain
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            // Ajout du nombre d'infect�s d'une case
            numInfected += grid.getSquare((posX + j + length) % length, (posY + i + height) % height);
        }
    }

    return numInfected;
}

// Place l'humain sur la grille s'il est infect�
void Human::placeOnGrid(Grid& grid, int x, int y)
{
    // V�rification des coordonn�es de l'humain
    if (x < grid.getLength() && y < grid.getHeight())
    {
        // R�cup�ration de la case dans laquelle il se trouve
        int& currentSquare = grid.getSquare(x, y);

        // S'il est infect� on incr�mente la case
        if (status == Status::Infected) {
            currentSquare++;
        }
    }
}

void Human::moveOnGrid(Grid& grid)
{
    // R�cup�ration de la taille de la grille
    int length = grid.getLength();
    int height = grid.getHeight();

    // G�n�ration de nouvelles coordonn�es
    int newPosX = randomGenerator.generateUniform(0, length - 1);
    int newPosY = randomGenerator.generateUniform(0, height - 1);

    // V�rification des coordonn�es de l'humain
    if (posX < grid.getLength() && posY < grid.getHeight())
    {
        // R�cup�ration de la case dans laquelle il se trouve
        int& currentSquare = grid.getSquare(posX, posY);

        // S'il est infect� on d�cr�mente la case
        if (status == Status::Infected)
        {
            currentSquare--;
        }
    }

    // Mise � jour de la position de l'humain
    posX = newPosX;
    posY = newPosY;

    // Mise � jour de son statut
    updateStatus(grid);

    // Mise � jour de la grille
    placeOnGrid(grid, posX, posY);

}