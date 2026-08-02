//
// Created by guill on 20/10/2023.
//

#include <fstream>
#include <iostream>
#include <filesystem>

#include "FileWriter.h"



void FileWriter::writeCSV( int (*tab)[4], int nbDay, int nbSimu) {

    std::string filename = "output/Simulation n " + std::to_string(nbSimu) + ".csv";
    std::ofstream csvFile(filename);

    std::filesystem::create_directories("output");

    /*
    if (!csvFile.is_open()) {
        std::cerr << "Failed to open the CSV file for writing." << std::endl;
        exit(EXIT_FAILURE);
    }*/

    csvFile << "Susceptible;Exposed;Infected;Recovered\n";

    for (int i = 0; i < nbDay; i++) {
        csvFile << tab[i][0] << ";" << tab[i][1] << ";" << tab[i][2] << ";" << tab[i][3] << "\n";
    }

    csvFile.close();

    std::cout << "File "+ filename +" Created Successfully." << std::endl;

}
