import java.util.List;
import java.util.ArrayList;

public class Population {

    private List<Personne>[][] grille;
    final int nbre_individu=20000;
    public final int largeur_hauteur=300;

    
    public Population() {
        this.grille = new List[largeur_hauteur][largeur_hauteur];
        for (int x = 0; x < largeur_hauteur; x++) {
            for (int y = 0; y < largeur_hauteur; y++) {
                grille[x][y] = new ArrayList<>();
            }
        }

    }


    private double negExp(double mean,MTRandom random) {
        return -mean * Math.log(1.0 - random.nextDouble());
    }




    public void initialiserPopulation(MTRandom random) {

        int nbre_individu_S=nbre_individu-20;
        for (int i = 0; i < nbre_individu_S; i++) {
            int x = random.nextInt(largeur_hauteur);
            int y = random.nextInt(largeur_hauteur);
            char etat = 'S';
            int dE = (int) negExp(3, random);
            int dI = (int) negExp(7, random);
            int dR = (int) negExp(365, random);
            grille[x][y].add(new Personne(etat, dE, dI, dR, x, y));

        }
        for(int i = 0; i < 20; i++){
            int x = random.nextInt(largeur_hauteur);
            int y = random.nextInt(largeur_hauteur);
            int dE = (int) negExp(3, random);
            int dI = (int) negExp(7, random);
            int dR = (int) negExp(365, random);
            char etat = 'I';
            grille[x][y].add(new Personne(etat, dE, dI, dR, x, y));
        }
    }
    



    public List<Personne> getPersonnes(int x, int y) {
        if (x >= 0 && x < largeur_hauteur && y >= 0 && y < largeur_hauteur) {
            return grille[x][y];
        } else {
            return new ArrayList<>(); // Retourne une liste vide si la position est en dehors des limites
        }
    }



    public void setPersonnes(int x, int y, List<Personne> personnes) {
        if (x >= 0 && x < largeur_hauteur && y >= 0 && y < largeur_hauteur) {
            grille[x][y] = personnes;
        }
    }



    public List<Personne>[][] getGrille() {
        return grille;
    }
}
