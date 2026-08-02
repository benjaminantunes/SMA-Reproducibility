#pragma once

#include <string>

#include "Position.hpp"
#include "RandMT.hpp"
#include "SimulationParams.hpp"

extern RandMT * randmt;

class Human 
{
   private:
      
      static const char SYMBOL_SUSCEPTIBLE = 'S';
      static const char SYMBOL_EXPOSED = 'E';
      static const char SYMBOL_INFECTED = 'I';
      static const char SYMBOL_RECOVERED = 'R';
      
      int      _elapsedTimeInstate = 0;
      char     _symbol;
      Position _pos;
      string   _stateName;
      int      _dE;
      int      _dI;
      int      _dR;

   public:
 
      Human(SimulationParams*,int,int);
      
      int       getElapsedTimeInState();
      int       getDE();
      int       getDI();
      int       getDR();
      void      resetElapsedTimeInState();
      void      incrementElapsedTimeInState();
      char      to_string();
      void      setPosition(int,int);
      Position  getPosition();
      string    getStateName();
      void      setStateName(string);

};
