#include "Monde.h"
// #include <chrono> // si on veut réellement de l'aléatoire

/////////////////////////////////////////////////////////////////////////////////////////
/* ! POUR COMPILER : g++ AleaPerso.cpp Individu.cpp Main.cpp Monde.cpp -lm -o sortie ! */
/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    mt19937 mt{}; // Toujours initialisé avec le même état -> reproductabilité

    /*
    mt19937 mt{ static_cast<mt19937::result_type>(
		chrono::steady_clock::now().time_since_epoch().count()
		) };
    */

    for (int i = 0; i < 100; i++) // environ 2s/génération, moins de 3min au total
    {
        
        Monde * m = new Monde(mt);
        ofstream f;
        f.open("./fichiersResultatsCSV/resultats" + to_string(i) + ".csv");
        for (int j = 0; j < 730; j++)
        {
            
            m->PasserUnJour(mt);
            m->EcrireCourant(f);
        }
        cout << "Génération " << i << " finie" << endl;
        f.close();
    } 

	return 0;  
}
