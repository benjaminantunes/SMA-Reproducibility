#include "Grid.h"

Grid::Grid(int length, int height) : length(length), height(height) {

    // Initialisation de la grille
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            grid[i][j] = {};
        }
    }
}

// Renvoie la largeur de la grille
int Grid::getLength() const {
    return length;
}

// Renvoie la hauteur de la grille
int Grid::getHeight() const {
    return height;
}

// Renvoie l'adresse de la case de la grille
int& Grid::getSquare(int x, int y) {
    return grid[x][y];
}