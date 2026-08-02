#include "Human.hpp"
#include <ostream>
#include <iostream>

using namespace std;




// -------------------------------------------------------------------- //
// Human::Human:  Constructeur de Human                                 //
//                                                                      //
// En entrée:                                                           // 
//                                                                      //
//    inSimulationParams :                                              //
//       Objet contenant les paramètres du fichier de configuration     //
//                                                                      //
//                                                                      //
//    inRow :                                                           //
//       La ligne de l'humain (Position X sur la carte)                 //
//                                                                      //
//    inColumn :                                                        //
//       La colonne de l'humain  (Position Y sur la carte)              //
//                                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Un objet humain                                                   //
// -------------------------------------------------------------------- //
Human::Human(SimulationParams * inSimulationParams,
             int                inRow, 
             int                inColumn
            )

{
   _pos       = Position(inRow,inColumn);
   _symbol    = Human::SYMBOL_SUSCEPTIBLE;
   _stateName = "susceptible";
   _dE        = randmt->negExp(inSimulationParams->getDurationIncubation());
   _dI        = randmt->negExp(inSimulationParams->getDurationInfection());
   _dR        = randmt->negExp(inSimulationParams->getDurationImmunity());
   
}



// -------------------------------------------------------------------- //
// Human::getState  Retourne l'état de l'humain (les jours dans l'état) //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Integer : L'état                                                  //
// -------------------------------------------------------------------- //

int Human::getElapsedTimeInState()
{
   return _elapsedTimeInstate;
}

// -------------------------------------------------------------------- //
// Human::incrementState                                                //
//    Augmente l'état de l'humain, un jour de plus dans l'etat courant  //
// -------------------------------------------------------------------- //

void Human::incrementElapsedTimeInState()
{
   _elapsedTimeInstate += 1;
}

// -------------------------------------------------------------------- //
// Human::to_string  Renvoi une représentation graphique de l'humain    //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Char : Signe pour représenter l'état de l'humain                  //
// -------------------------------------------------------------------- //

char Human::to_string()
{
   
   if(_stateName == "susceptible")
   {
      return Human::SYMBOL_SUSCEPTIBLE;
   }
   if(_stateName == "exposed")
   {
      return Human::SYMBOL_EXPOSED;
   }
   if(_stateName == "infected")
   {
      return Human::SYMBOL_INFECTED;
   }
   if (_stateName == "recovered")
   {
      return Human::SYMBOL_RECOVERED;
   }
   else
   {
      return _symbol;
   }
}


string Human::getStateName()
{
   return _stateName;
}


void Human::setStateName(string stateName)
{
   _stateName = stateName;
   resetElapsedTimeInState();
}
// -------------------------------------------------------------------- //
// Human::setPosition  Modifie la position de l'humain                  //
//                                                                      //
// En entrée:                                                           // 
//                                                                      //
//    inPosX :                                                          //
//       Position de la ligne                                           //
//                                                                      //
//     inPosY :                                                         //
//        Position de la colonne                                        // 
// -------------------------------------------------------------------- //

void Human::setPosition(int inPosX,int inPosY)
{
   _pos.setPosX(inPosX);
   _pos.setPosY(inPosY);
};

// -------------------------------------------------------------------- //
// Human::getPosition  Retourne la position de l'humain                 //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Position : La position de l'humain                                //
// -------------------------------------------------------------------- //

Position  Human::getPosition()
{
   return _pos;
}



// -------------------------------------------------------------------- //
// Human::resetElapsedTimeInState  Remet l'état à 0                     //
// -------------------------------------------------------------------- //

void Human::resetElapsedTimeInState()
{
   _elapsedTimeInstate = 0;
}

int Human::getDE(){
    return _dE;
}

int Human::getDI(){
    return _dI;
}

int Human::getDR(){
    return _dR;
}
