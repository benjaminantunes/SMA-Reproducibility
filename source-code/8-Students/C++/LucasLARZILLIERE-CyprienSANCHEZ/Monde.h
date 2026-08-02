#include "Individu.h"
#include <fstream> // Pour manipuler des fichiers

class Monde{
    public:
        int nbInfectes[300][300];
        Individu** ListeIndividu = new Individu * [nbIndiv]; // Tableau de pointeurs (obligé car on manipule des individus, et pour les créer on les passera par adresse à la liste)
        array<int, nbIndiv> OrdreDep; // Tableau d'entiers

        Monde(mt19937& mt); // Constructeur
        void PasserUnJour(mt19937& mt);
        void EcrireCourant(ofstream& f);
        void Deplacement(Individu& indiv, mt19937& mt); // si on déplace un infecté, ++ et -- dans la grille, si on déplace un S, on VerifInf
        void VerifInf(Individu& indiv, int x, int y, mt19937& mt); // coordonée de l'individu pour vérifier le voisinage, sera appelé dans Déplacement donc on les aura
        
        int getcptS();
        void setcptS(int v);

        int getcptE();
        void setcptE(int v);

        int getcptI();
        void setcptI(int v);

        int getcptR();
        void setcptR(int v);


    private:
        int cptS, cptE, cptI, cptR;
};