
#include "SimulationParams.hpp"
#include <fstream>
#include <ostream>
#include <iostream>

using namespace std;


SimulationParams::SimulationParams(char * inFilename){

   _mapStringValues["size"] = 9;
   _mapStringValues["nbMalade"] = 10;
   _mapStringValues["nbHumain"] = 11;
   _mapStringValues["nbIteration"] = 12;
   _mapStringValues["transmissionRate"] = 13;
   _mapStringValues["durationIncubation"] = 14;
   _mapStringValues["durationInfection"] = 15;
   _mapStringValues["durationImmunity"] = 16;
   

   size_t   pos = 0;
   

   string   delimiterName = "||";
   string   delimiterValues = ",";
   
             
   
   ifstream readFile(inFilename);
   string   line;
   
   pos = 0;
   
   while (getline(readFile, line))
   {
      if(line.find("#") == string::npos)
      {
         string paramName = line.substr(0, line.find(delimiterName));
         string paramValues = line.erase(0,
                                         line.find(delimiterName) 
                                         + 
                                         delimiterName.length()
                                        );
         string value;
         int j = 0;
         
         switch (_mapStringValues[paramName])
         {
        
               
            case 9:
               _size = stoi(paramValues);
               break;
               
            case 10:
               _nbMalade = stoi(paramValues);
               break;
               
            case 11:
               _nbHumain = stoi(paramValues);
               break;
               
            case 12:
               _nbIteration = stoi(paramValues);
               break;
               
            case 13:
               _transmissionRate = stof(paramValues);
               break;
               
            case 14:
               _durationIncubation = stoi(paramValues);
               break;
               
            case 15:
               _durationInfection = stoi(paramValues);
               break;
               
            case 16:
               _durationImmunity = stoi(paramValues);
               break;
               
         }
      }
      
      
      
   }
   readFile.close();

}


int SimulationParams::getSize()
{
   return _size;
}

int SimulationParams::getNbMalade()
{
   return _nbMalade;
}

int SimulationParams::getNbHumain()
{
   return _nbHumain;
}

int SimulationParams::getNbIteration()
{
   return _nbIteration;
}

float SimulationParams::getTransmissionRate()
{
   return _transmissionRate;
}

int SimulationParams::getDurationInfection()
{
   return _durationInfection;
}

int SimulationParams::getDurationIncubation()
{
   return _durationIncubation;
}

int SimulationParams::getDurationImmunity()
{
   return _durationImmunity;
}

