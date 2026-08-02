#include "Monde.h"

Monde::Monde(mt19937& mt) { // constructeur donc initialisation du monde
  int i = 0;
  int r;
  int x, y;
  setcptS(19980);
  setcptE(0);
  setcptI(20);
  setcptR(0);
  AleaPerso a = AleaPerso();

  for (int k = 0; k < nbIndiv; k++) {
        ListeIndividu[k] = new Individu(mt); // Crée un nouvel objet Individu et le met a sa place dans la liste
        OrdreDep[k] = k; // Initialise le tableau OrdreDep dans l'ordre mais sera shuffle ensuite
    }

  while (i < 20) // 20 permiers infectés, while car si on retombe sur quelqu'un de déjà infecté, on incrément pas
  {
    r = a.RandomMinMax(0, nbIndiv, mt); // on prend un individu au hasard pour l'infecter
    if (ListeIndividu[r]->getStatut() != 'I') // si il n'est pas déjà infecté
    {
      
      ListeIndividu[r]->setStatut('I');
      i++;
      // on les place (c'est inutile de placer les non infectés car pas de
      // mémorisation de l'état précendent et à chaque jour, déplacement
      // aléatoire)
      x = a.RandomMinMax(0, 300, mt);
      y = a.RandomMinMax(0, 300, mt);
      nbInfectes[x][y]++;
      ListeIndividu[r]->setX(x);
      ListeIndividu[r]->setY(y);
    }
  }
  a.ShuffleOrdre(OrdreDep, mt); // et on mélange l'ordre en vu du premier jour
}

int Monde::getcptS() { return cptS; }
void Monde::setcptS(int v) { cptS = v; }

int Monde::getcptE() { return cptE; }
void Monde::setcptE(int v) { cptE = v; }

int Monde::getcptI() { return cptI; }
void Monde::setcptI(int v) { cptI = v; }

int Monde::getcptR() { return cptR; }
void Monde::setcptR(int v) { cptR = v; }

void Monde::VerifInf(Individu& indiv, int x, int y, mt19937& mt) {
  int nbInfectesCurr = 0;
  AleaPerso a = AleaPerso();

  // regarder les 9 cases, compter ni et faire la proba
  for (int i = -1; i <= 1; i++)
  {
    for (int j = -1; j <= 1; j++)
    {
      // Coordonnées de la case à vérifier
      int voisinX = (x + i + 300) % 300; // Utilisation de l'opérateur modulo pour l'espace torique
      int voisinY = (y + j + 300) % 300;
      nbInfectesCurr += nbInfectes[voisinX][voisinY];
    }
  }

  if (a.probaInf(nbInfectesCurr, mt) == 1) {
    indiv.setStatut('E');
  }
}

void Monde::Deplacement(Individu& indiv, mt19937& mt)
{
  AleaPerso a = AleaPerso();
  char statutCourant = indiv.getStatut();
  if (statutCourant == 'I')
  {
    nbInfectes[indiv.getX()][indiv.getY()]--; // décrémenter la matrice d'infecté avant de tirer de nouvelles coordonées et le bouger
  }
  
  indiv.setX(a.RandomMinMax(0, 300, mt));
  indiv.setY(a.RandomMinMax(0, 300, mt));

  if (statutCourant == 'S') { // obligé de le faire avant d'incrémenter les compteurs au cas où il devienne E
    VerifInf(indiv, indiv.getX(), indiv.getY(), mt);
  }
  statutCourant = indiv.MajStatut();
  if (statutCourant == 'I') // si devenu Infecté, incrémenter la matrice
  {
    nbInfectes[indiv.getX()][indiv.getY()]++; // en public donc pas de soucis
    setcptI(getcptI() + 1);
  }
  if (statutCourant == 'S') // sinon maj des compteurs
  {
    setcptS(getcptS() + 1);
  }
  if (statutCourant == 'E')
  {
    setcptE(getcptE() + 1);
  }
  if (statutCourant == 'R')
  {
    setcptR(getcptR() + 1);
  }
}

void Monde::PasserUnJour(mt19937& mt) {
  AleaPerso a = AleaPerso();
  Individu * individuCourant;

  setcptS(0);
  setcptE(0);
  setcptI(0);
  setcptR(0);

  for (int i = 0; i < nbIndiv; i++) {
    individuCourant = ListeIndividu[OrdreDep[i]];
    Deplacement(*individuCourant, mt);
  }
  a.ShuffleOrdre(OrdreDep, mt); // et on mélange l'ordre pour le prochain jour
}

void Monde::EcrireCourant(ofstream& f) {

  if (f.is_open())
  {
    f << getcptS() << ";" << getcptE() << ";"  << getcptI() << ";"  << getcptR() << "\n";
  } 
  else
  {
    cout << "soucis à l'ouverture" << endl;
  } 
}
