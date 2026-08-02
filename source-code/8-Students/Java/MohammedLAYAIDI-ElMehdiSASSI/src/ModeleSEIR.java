import java.util.ArrayList;
import java.util.List;



public class ModeleSEIR {
    private Population population;
    private int nombreSusceptibles;
    private int nombreExposes;
    private int nombreInfectes;
    private int nombreRecuperes;
    public final int largeur_hauteur=300;


    public ModeleSEIR(Population population) {
        this.population = population;
        this.nombreSusceptibles = 19980;
        this.nombreExposes = 0;
        this.nombreInfectes = 20;
        this.nombreRecuperes = 0;
    }




public void deplacerIndividusAleatoirement(MTRandom random) {

    List<Personne>[][] grille = population.getGrille();

    // Créez une liste temporaire pour stocker les personnes à déplacer
    List<Personne> personnesADeplacer = new ArrayList<>();

    for (int x = 0; x < largeur_hauteur; x++) {
        for (int y = 0; y < largeur_hauteur; y++) {
            List<Personne> personnes = grille[x][y];

            if (personnes != null && !personnes.isEmpty()) {
                // Ajoutez les personnes à la liste temporaire
                personnesADeplacer.addAll(personnes);
            }
        }
    }

    // Parcourez la liste temporaire et déplacez les individus
    for (Personne personne : personnesADeplacer) {
        int nouveauX = random.nextInt(largeur_hauteur);
        int nouveauY = random.nextInt(largeur_hauteur);

        // Déplacez la personne vers la nouvelle position
        // Supprimez la personne de la liste actuelle
        List<Personne> listeActuelle = grille[personne.getPosition_x()][personne.getPosition_y()];
        listeActuelle.removeIf(p -> p.equals(personne));

        grille[nouveauX][nouveauY].add(personne);
        personne.setPosition_x(nouveauX);
        personne.setPosition_y(nouveauY);
    }
}



    public int compterInfectesDansVoisinage(int x, int y) {
        int nombreInfectes = 0;
        List<Personne>[][] grille = population.getGrille();

        // Coordonnées relatives des 8 cellules voisines autour de (x, y)
        int[] dx = {-1, -1, -1, 0, 0, 1, 1, 1};
        int[] dy = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int i = 0; i < 8; i++) {
            int newX = (x + dx[i] + largeur_hauteur) % largeur_hauteur; // Gérer la grille toroïdale
            int newY = (y + dy[i] + largeur_hauteur) % largeur_hauteur;

            // Récupérer la liste des personnes sur la cellule (newX, newY)
            List<Personne> personnes = grille[newX][newY];
            
            for (Personne personne : personnes) {
                if (personne.getEtat() == 'I') {
                    nombreInfectes++;
                }
            }
        }

        return nombreInfectes;
    }



// Implémenter la transition d'état de S à E
    public void infecter(MTRandom random) {    
        List<Personne>[][] grille = population.getGrille();
        
        for (int x = 0; x < largeur_hauteur; x++) {
            for (int y = 0; y < largeur_hauteur; y++) {
                // Récupérer la liste des personnes sur la cellule (x, y)
                List<Personne> personnes = grille[x][y];
                
                for (Personne personne : personnes) {
                    if (personne.getEtat() == 'S') {
                        int nombreInfectesVoisinage = compterInfectesDansVoisinage(x, y);
                        double p = 1.0 - Math.exp(-0.5 * nombreInfectesVoisinage);
                        int temps = personne.getTemps_ecoule();
                        if (random.nextDouble() < p) {
                            personne.setEtat('E');
                            personne.setTemps_ecoule(temps + 1);
                            personne.setAFaitLaTransition(true); // Marquer la personne comme ayant fait la transition
                        }
                    }
                }
            }
        }
    }


// Implémenter la transition d'état de E à I
    public void exposerIndividus() {
        List<Personne>[][] grille = population.getGrille();
        for (int x = 0; x < largeur_hauteur; x++) {
            for (int y = 0; y < largeur_hauteur; y++) {
                List<Personne> personnes = grille[x][y];
                if (personnes != null) {
                    for (Personne personne : personnes) {
                        // Vérifiez si la personne est en état Exposé
                        if (personne != null && personne.getEtat() == 'E' ) {
                            // Récupérez le temps écoulé dans l'état Exposé
                            int tempsExpose = personne.getTemps_ecoule();

                            // Récupérez la durée de la période d'exposition (dE) de cette personne
                            int dE = personne.getDE();

                            // Vérifiez si le temps écoulé est supérieur ou égal à dE
                            if (tempsExpose > dE && !personne.getAFaitLaTransition()) {
                                // Transition de l'état Exposé (E) à l'état Infecté (I)
                                personne.setEtat('I');
                                // Marquer la personne comme ayant fait la transition
                                personne.setAFaitLaTransition(true); 
                                // Réinitialisez le temps écoulé dans l'état Exposé
                                personne.setTemps_ecoule(0);
                            } else {
                                personne.setTemps_ecoule(tempsExpose + 1);                            }
                        }
                    }
                }
            }
        }        
    }

// Implémenter la transition d'état de I à R
    public void recupererIndividus() {
        List<Personne>[][] grille = population.getGrille();
        for (int x = 0; x < largeur_hauteur; x++) {
            for (int y = 0; y < largeur_hauteur; y++) {
                List<Personne> personnes = grille[x][y];
                if (personnes != null) {
                    for (Personne personne : personnes) {
                        if (personne != null && personne.getEtat() == 'I' ) {
                            int tempsExpose = personne.getTemps_ecoule();
                            int  dI = personne.getDI();
                            if (tempsExpose > dI && !personne.getAFaitLaTransition()) {
                                personne.setEtat('R');
                                // Marquer la personne comme ayant fait la transition
                                personne.setAFaitLaTransition(true);
                                personne.setTemps_ecoule(0);
                            } else {
                                personne.setTemps_ecoule(tempsExpose + 1);                                
                            }
                        }
                    }
                }
            }
        }  
    }


// Implémenter la transition d'état de R à S
    public void perdreImmunité() {
        List<Personne>[][] grille = population.getGrille();
        for (int x = 0; x < largeur_hauteur; x++) {
            for (int y = 0; y < largeur_hauteur; y++) {
                List<Personne> personnes = grille[x][y];
                if (personnes != null) {
                    for (Personne personne : personnes) {
                        if (personne != null && personne.getEtat() == 'R'  ) {
                            int tempsExpose = personne.getTemps_ecoule();                  
                            int dR = personne.getDR();
                            if (tempsExpose > dR && !personne.getAFaitLaTransition()) {
                                personne.setEtat('S');
                                // Marquer la personne comme ayant fait la transition
                                personne.setAFaitLaTransition(true);
                                personne.setTemps_ecoule(0);
                            } else {
                                personne.setTemps_ecoule(tempsExpose + 1);
                            }
                        }
                    }
                }
            }
        }         
        
    }


    // méthodes pour récupérer le nombre d'individus dans chaque état.
    public int getNombreSusceptibles() {
        int nombreSusceptibles = 0;
        List<Personne>[][] grille = population.getGrille();
        for (int x = 0; x < largeur_hauteur; x++) {
            for (int y = 0; y < largeur_hauteur; y++) {
                List<Personne> personnes = grille[x][y];
                if (personnes != null) {
                    for (Personne personne : personnes) {
                        if (personne != null && personne.getEtat() == 'S') {
                        nombreSusceptibles++;
                        }
                    }
                }
            }
        }

        return nombreSusceptibles;    
    }

    public int getNombreExposes() {
        int nombreExposes = 0;
        List<Personne>[][] grille = population.getGrille();

        for (int x = 0; x < largeur_hauteur; x++) {
            for (int y = 0; y < largeur_hauteur; y++) {
                List<Personne> personnes = grille[x][y];
                if (personnes != null) {
                    for (Personne personne : personnes) {
                        if (personne != null && personne.getEtat() == 'E') {
                            nombreExposes++;
                        }
                    }
                }
            }
        }
        return nombreExposes;
    }

    public int getNombreInfectes() {
        int nombreInfectes = 0;
        List<Personne>[][] grille = population.getGrille();

        for (int x = 0; x < largeur_hauteur; x++) {
            for (int y = 0; y < largeur_hauteur; y++) {
                List<Personne> personnes = grille[x][y];
                if (personnes != null) {
                    for (Personne personne : personnes) {
                        if (personne != null && personne.getEtat() == 'I') {
                            nombreInfectes++;
                        }
                    }
                }
            }
        }

        return nombreInfectes;
    }

    public int getNombreRecuperes() {
        int nombreRecuperes = 0;
        List<Personne>[][] grille = population.getGrille();

        for (int x = 0; x < largeur_hauteur; x++) {
            for (int y = 0; y < largeur_hauteur; y++) {
                List<Personne> personnes = grille[x][y];
                if (personnes != null) {
                    for (Personne personne : personnes) {
                        if (personne != null && personne.getEtat() == 'R') {
                            nombreRecuperes++;
                        }
                    }
                }
            }
        }

        return nombreRecuperes;       
    }
}
