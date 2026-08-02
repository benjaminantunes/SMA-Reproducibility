#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <deque>

#include "RandMT.hpp"
#include "Human.hpp"
#include "SimulationParams.hpp"

using namespace std;

extern RandMT * randmt;

class World{
   private:
      int              _size;
      int              _nbIteration;
      int              _nbHumain;
      int              _nbMalade;
      vector<Human>    _humans;
      vector<Human>    _humansNext;
      int              _durationIncubation;
      int              _durationInfection;
      int              _durationImmunity;
      float            _transmissionRate;

   
      bool             _log = false;
      fstream          _logfile;
      int              _iteration = 0;
      map<string, int> _stats;

      static const char SYMBOL_EMPTY = '.';
      static constexpr float MAX_HUMANS = 0.8;
      
      
      

   public:
      World(SimulationParams*,char *, bool);
      ~World();
      
      void        writeLog(string);
      static void pause();
      void        display();
      void        updateStats(string);
      void        displayStats();
      void        addAgent(SimulationParams*,float);
      void        initialize(SimulationParams*);
      int         vision(int,Human);
      Human       contamination(Human);
      void        moveHumans();
      void        nextIteration();
      void        startSimulation(SimulationParams*);
};
