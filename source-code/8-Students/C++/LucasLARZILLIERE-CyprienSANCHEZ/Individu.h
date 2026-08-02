#include "AleaPerso.h" 

class Individu{
    public:
        Individu(mt19937& mt); // Constructeur
        char MajStatut();
        char getStatut();
        void setStatut(char s);

        int getX();
        void setX(int v);
    
        int getY();
        void setY(int v);

    private:
        char statut;
        int tempsStatut, x, y; // x et y utile que pour les I et S, les autres n'ont pas besoin de savoir où ils sont
        int dE, dI, dR;
};
