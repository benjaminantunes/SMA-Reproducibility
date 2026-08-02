#include "World.hpp"
#include <typeinfo>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <cmath>
#include <algorithm>    // std::find

using namespace std;

// -------------------------------------------------------------------- //
// World::World:  Constructeur de l'objet World                         //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    inSimulationParams :                                              //
//       Permet de récupérer les données du fichier de config           //
//                                                                      //                          
//    inNomFichierLog :                                                 //
//       Détermine le nom du fichier de log dans lequel                 //
//       on va stocker les résultats                                    //
//                                                                      //
//    inLog :                                                           //
//       Booléen pour déterminer si oui ou non on stocke les résultats  //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
World::World(SimulationParams * inSimulationParams,
             char             * inNomFichierLog, 
             bool               inLog)
{
   _size               = inSimulationParams->getSize();
                     
   _nbIteration        = inSimulationParams->getNbIteration();
                     
   _nbHumain           = inSimulationParams->getNbHumain();

   _nbMalade           = inSimulationParams->getNbMalade();
   
   _transmissionRate   = inSimulationParams->getTransmissionRate();
                     
   _durationImmunity   = inSimulationParams->getDurationImmunity();
                     
   _durationIncubation = inSimulationParams->getDurationIncubation();
                     
   _durationInfection  = inSimulationParams->getDurationInfection();
   
                  

   _log = inLog;
   _stats["susceptible"] = 0;
   _stats["exposed"] = 0;
   _stats["infected"] = 0;
   _stats["recovered"] = 0;
   if(_log)
   {
      _logfile.open(inNomFichierLog,ios::out);
   }
   
}




// -------------------------------------------------------------------- //
// World::~World:  Destructeur de l'objet World                         //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//   Pas de sortie                                                      //
// -------------------------------------------------------------------- //
World::~World()
{
    
   if(_log)
   {
      _logfile.close();
   }
}



// -------------------------------------------------------------------- //
// World::writeLog:  Permet d'écrire un message dans le fichier de log  //
//                                                                      //
// En entrée:                                                           // 
//                                                                      //
//    inSimulationParams :                                              //
//       Permet de récupérer les données du fichier de config           //
//                                                                      //
//    inNomFichierLog :                                                 //
//       Détermine le nom du fichier de log dans lequel                 //
//       on va stocker les résultats                                    //
//                                                                      //
//    inLog :                                                           //
//       Booléen pour déterminer si oui ou non on stocke les résultats  //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
void World::writeLog(string inMsg)
{
   _logfile << inMsg;
   _logfile << endl;
}


// -------------------------------------------------------------------- //
// World::pause:  Permet d'afficher un message de pause                 //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//   Pas de sortie                                                      //
// -------------------------------------------------------------------- //
void World::pause()
{
   cout << "Hit <Return to continue" << endl ;
}



// -------------------------------------------------------------------- //
// World::updateStats:                                                  //
//    Permet de mettre à jour les statistiques des Humains.             //
//    Les statistiques sont : Le nombre d'humain qui n'ont pas eu la    //
//    maladie, le nombre d'humain qui ont eu la maladie puis ce sont    //
//    retabli, le nombre d'humain actuellement contaminé, et enfin      //
//    le nombre d'humain qui sont morts.                                //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    inState :                                                         //
//       String représentant le changement d'état de l'Humain           //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//   Pas de sortie                                                      //
// -------------------------------------------------------------------- //
void World::updateStats(string inState)
{
   if(inState == "recovered")
   {
      _stats.at("infected") -= 1;
      _stats.at("recovered") += 1;     
   }
   else if(inState == "infected")
   {
      _stats.at("exposed") -= 1;
      _stats.at("infected") += 1;
   }
   else if(inState == "exposed")
   {
      _stats.at("susceptible") -= 1;
      _stats.at("exposed") += 1;
   }
   else if(inState == "susceptible")
   {
      _stats.at("recovered") -= 1;
      _stats.at("susceptible") += 1;
   }
}


// -------------------------------------------------------------------- //
// World::displayStats:  Affiche les statistiques                       //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//   Pas de sortie                                                      //
// -------------------------------------------------------------------- //
void World::displayStats()
{
   cout << "***************STATISTICS******************" <<endl;
   cout <<"Susceptible : " << _stats.at("susceptible") << endl;
   cout <<"Exposed : " << _stats.at("exposed") << endl;
   cout <<"Infected : " << _stats.at("infected") << endl;
   cout <<"Recovered : " << _stats.at("recovered") << endl;
}

// -------------------------------------------------------------------- //
// World::addAgent:  Initialise la carte en ajoutant les Agents         //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    inSimulationParams :                                              //
//       Les paramètres du fichier de configuration                     //
//                                                                      //
//    inWorldMax :                                                      //
//        Facteur déterminant le nombre maximal d'humain                //
//        (Param à supprimer ?)                                         //
//                                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//   Pas de sortie                                                      //
// -------------------------------------------------------------------- //
void World::addAgent(SimulationParams * inSimulationParams, 
                     float              inWorldMax 
                    )
{


   int maxAgents = pow(_size,2) * inWorldMax;
   _stats.at("susceptible") = _nbHumain - _nbMalade;
   _stats.at("infected") = _nbMalade;


   if(_nbHumain > maxAgents)
   {
      cout << "trop d'agent" << endl;
      exit(1);
   }

   if(_nbMalade > _nbHumain)
   {
      cout << "trop de malade" << endl;
      exit(1);
   }
   
   for(int qtyAgent = 0; qtyAgent < _nbHumain-_nbMalade; qtyAgent++)
   {        
      bool  varEmpty = false;
      int   row;
      int   column;
 
      row = randmt->genrand_int32()%_size;
      column = randmt->genrand_int32()%_size;
      Human h = Human(inSimulationParams,row,column);
      _humans.push_back(h);

      
   }
   

   for(int qtyAgents = 0; qtyAgents<_nbMalade;qtyAgents++)
   {
      
      bool varEmpty = false;
      int row;
      int column;

      row = randmt->genrand_int32()%_size;
      column = randmt->genrand_int32()%_size;

      Human h = Human(inSimulationParams,row,column);
      h.setStateName("infected");
      _humans.push_back(h);// passage par copie dans le vecteur, pas par réf ...

      

   }
   

}


// -------------------------------------------------------------------- //
// World::initialize:  Initialise en appelant addAgent                  // 
//                     (Fonction inutile ?)                             //
//                                                                      //
// En entrée:                                                           // 
//                                                                      //
//    inSimulationParams :                                              //
//       Les paramètres du fichier de configuration                     //
//                                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//   Pas de sortie                                                      //
// -------------------------------------------------------------------- //
void World::initialize(SimulationParams * inSimulationParams)
{
   addAgent(inSimulationParams,World::MAX_HUMANS);
}



// -------------------------------------------------------------------- //
// World::vision:  Détermine le contenu des cases voisines d'une cases  //
//                                                                      //
// En entrée:                                                           // 
//                                                                      //
//    inLength :                                                        //
//       La distance à observer (voisinage de Moore)                    //
//                                                                      //
//    inRow :                                                           //
//       La ligne de départ (Position X)                                //
//                                                                      //
//    inColumn :                                                        //
//       La colonne de départ (Position Y)                              //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Un dictionnaire/map associant les cases vides à une liste de      //
//    positions et les cases occupées à une liste de positions.         // 
// -------------------------------------------------------------------- //
int World::vision(int inLength, Human inHuman)
{

   //Ne retourner que le nombre de personne infecté dans le voisinage, c'est la seul chose qui sera utile.
   int countInfectedNeighbour = 0;
   /*
   for(Human human: _humans){
      if(abs(human.getPosition().getPosX() - inHuman.getPosition().getPosX()) <=1){
         if(abs(human.getPosition().getPosY() - inHuman.getPosition().getPosY()) <=1){
            if(human.getStateName()=="infected"){
               countInfectedNeighbour++;
            }
            
         }
      }
   }
   */
   //cout << "oh" << endl;
   for (Human human : _humans) {
      int dx = abs(human.getPosition().getPosX() - inHuman.getPosition().getPosX());
      int dy = abs(human.getPosition().getPosY() - inHuman.getPosition().getPosY());
      if (dx <= 1 || dx >= _size) { // check if human is in x-range of inHuman
         if (dy <= 1 || dy >= _size) { // check if human is in y-range of inHuman
            if (human.getStateName() == "infected") {
                countInfectedNeighbour++;
            }
         }
      }
   }
   /*
   vector<int> neighbourPosX;
   vector<int> neighbourPosY;
   //I do this for toroidal space, with %_size to go the other way.
   neighbourPosX.push_back( (inHuman.getPosition().getPosX() == 0) ? _size : (inHuman.getPosition().getPosX() - 1) );
   neighbourPosX.push_back( (inHuman.getPosition().getPosX()));
   neighbourPosX.push_back( (inHuman.getPosition().getPosX() + 1)%_size);
   
   neighbourPosY.push_back( (inHuman.getPosition().getPosY() == 0) ? _size : (inHuman.getPosition().getPosY() - 1) );
   neighbourPosY.push_back( (inHuman.getPosition().getPosY()));
   neighbourPosY.push_back( (inHuman.getPosition().getPosY() + 1)%_size);
   
   //If the human infected is in my neibourhood
   for(Human human: _humans){
      if(find(neighbourPosX.begin(), neighbourPosX.end(), human.getPosition().getPosX()) != neighbourPosX.end() && find(neighbourPosY.begin(), neighbourPosY.end(), human.getPosition().getPosY()) != neighbourPosY.end()){
         if(human.getStateName()=="infected"){
            countInfectedNeighbour++;
         }
      }
   }
   */
   /* how the find is working : 
    * Find returns :
    * An iterator to the first element in the range that compares equal to val.
      If no elements match, the function returns last.
      
      The "last" is not really the last value, that's why it is working.
      The explaination is that vector.end do not refer to the last value
      vector.end() returns :
      Returns an iterator referring to the past-the-end element in the vector container.
      The past-the-end element is the theoretical element that would follow the last element in the vector. 
      It does not point to any element, and thus shall not be dereferenced.
    * 
    */
   
   return countInfectedNeighbour;
}





// -------------------------------------------------------------------- //
// World::Contamination:                                                // 
//    Un malade essaye de contaminer ses voisins sains                  //
//    lors d'un déplacement                                             //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    inRow :                                                           //
//       La ligne de destination de l'humain malade                     //
//                                                                      //
//    inColumn :                                                        //
//       La colonne de destination de l'humain malade                   //
//                                                                      //
//                                                                      //
//    inCurrentRow :                                                    //
//       La ligne actuelle de l'humain malade                           //
//                                                                      //
//    inCurrentColumn :                                                 //
//       La colonne actuelle de l'humain malade                         //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
Human World::contamination(Human inHuman)
{
   
   int nbInfectedNeighbour = vision(1,inHuman);
   
   //cout <<"Nb voisin infected : " << nbInfectedNeighbour << endl;
   double probaInfected = exp(-_transmissionRate*nbInfectedNeighbour);
   
   if(randmt->genrand_real1() > probaInfected){
      inHuman.setStateName("exposed");
      updateStats("exposed");
   }
   return inHuman;
}



// -------------------------------------------------------------------- //
// World::moveHumanSusceptible:                                         //
//                        Réalise le comportement des humains sains     //
//                                                                      //
// En entrée:                                                           //
//                                                                      //
//    inRow :                                                           //
//       La ligne de l'humain sur la carte (Position X sur la carte)    //
//                                                                      //
//    inColumn :                                                        //
//       La colonne de l'humain sur la carte (Position Y sur la carte)  //
//                                                                      //
//                                                                      //
//                                                                      //
// En sortie:                                                           // 
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
void World::moveHumans()
{
   int rowDeplacement;
   int columnDeplacement;

    

   for(Human human: _humans){
      /* 
      cout <<"Human dE : " << human.getDE() << endl;
      cout <<"Human dI : " << human.getDI() << endl;
      cout <<"Human dR : " << human.getDR() << endl;
      cout <<"Human position X : " << human.getPosition().getPosX() << endl;
      cout <<"Human position Y : " << human.getPosition().getPosY() << endl;
      cout <<"Human position State : " << human.to_string() << endl;
      */
      // Il peut se déplacer de 0 à size
      rowDeplacement = randmt->genrand_int32()%_size; 
      columnDeplacement = randmt->genrand_int32()%_size;
      if(human.to_string() == 'S'){
         human.resetElapsedTimeInState(); // we don't care about time in state for susceptible.
         human = contamination(human);
         human.setPosition(rowDeplacement,columnDeplacement);
         _humansNext.push_back(human);
      }
      else if(human.to_string() == 'E'){
         if(human.getElapsedTimeInState() > human.getDE()){
            human.setStateName("infected");
            updateStats("infected");
            human.resetElapsedTimeInState();
         }else{
            human.incrementElapsedTimeInState();
         }
         human.setPosition(rowDeplacement,columnDeplacement);
         _humansNext.push_back(human);
      }
      else if(human.to_string() == 'I'){
         if(human.getElapsedTimeInState() > human.getDI()){
            human.setStateName("recovered");
            updateStats("recovered");
            human.resetElapsedTimeInState();
         }else{
            human.incrementElapsedTimeInState();
         }
         human.setPosition(rowDeplacement,columnDeplacement);
         _humansNext.push_back(human);
      }
      else if(human.to_string() == 'R'){
         if(human.getElapsedTimeInState() > human.getDR()){
            human.setStateName("susceptible");
            updateStats("susceptible");
            human.resetElapsedTimeInState();
         }else{
            human.incrementElapsedTimeInState();
         }
         human.setPosition(rowDeplacement,columnDeplacement);
         _humansNext.push_back(human);
      }
   }

}







// -------------------------------------------------------------------- //
// World::nextIteration:                                                //
//    Effectue les changements necessaires et écrit les log             //
//    pour passer à l'itération suivante                                //
//                                                                      //
// En entrée:                                                           // 
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
void World::nextIteration()
{
   writeLog(to_string(_iteration));
   writeLog(to_string(_stats.at("susceptible")));
   writeLog(to_string(_stats.at("exposed")));
   writeLog(to_string(_stats.at("infected")));
   writeLog(to_string(_stats.at("recovered")));
   writeLog("##########");

   _iteration += 1;

   moveHumans();

   _humans = _humansNext;
   _humansNext.clear();
   
}




// -------------------------------------------------------------------- //
// World::startSimulation:  Démarre la simulation                       //
//                                                                      //
// En entrée:                                                           // 
//                                                                      //
//    inSimulationParams :                                              //
//       Objet contenant les paramètres du fichier de configuration     //
//                                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Pas de sortie                                                     //
// -------------------------------------------------------------------- //
void World::startSimulation(SimulationParams * inSimulationParams)
{


   for(int iteration = 0;
       iteration < inSimulationParams->getNbIteration();
       iteration++)
   {
      displayStats();
      //display();
      
      //World::pause();
      nextIteration();
      /*
      if(_humansPosition.size() == 0){
         cout << "no more humans in the simulation" << endl;
         //self.writeLog('[STOP] No more human in the simulation !\n')
         break;
      }
      */
   }

   //cout << "\033[2J" << endl;
   displayStats();
   
}


