import java.io.FileWriter;
import java.io.IOException;
import java.util.List;

public class App{
    public static void main(String[] args) throws Exception {
        int largeur_hauteur = 300;
        int nombreDeJours = 730;
        int nombreDeRepetitions = 100;  // Choisissez le nombre de répétitions
        MTRandom randomGenerator = new MTRandom(12345); // Create the random generator

        for (int repetition = 0; repetition < nombreDeRepetitions; repetition++) {
            Population population = new Population();
            population.initialiserPopulation(randomGenerator);

            ModeleSEIR modele = new ModeleSEIR(population);

            // Créez un nom de fichier unique pour chaque répétition
            String nomFichier = "./bin/data/donnees_simulation_replication_" + repetition + ".csv";


            try (FileWriter writer = new FileWriter(nomFichier)) {
                writer.write("Jour,Susceptible,Exposed,Infected,recovered\n"); // En-têtes
                List<Personne>[][] grille = population.getGrille();
                for (int jour = 0; jour <= nombreDeJours; jour++) {
                    for (int x = 0; x < largeur_hauteur; x++) {
                        for (int y = 0; y < largeur_hauteur; y++) {
                            List<Personne> personnes = grille[x][y];
                            if (personnes != null) {
                                for (Personne personne : personnes) {
                                    if (personne != null) {
                                        personne.setAFaitLaTransition(false); // Réinitialisez le marquage
                                    }
                                }
                            }
                        }
                    }
                    if(jour==0){
                        int susceptibles = modele.getNombreSusceptibles();
                        int exposes = modele.getNombreExposes();
                        int infectes = modele.getNombreInfectes();
                        int recuperes = modele.getNombreRecuperes();
                        writer.write(jour + "," + susceptibles + "," + exposes + "," + infectes + "," + recuperes + "\n");                       
                    }
                    else
                    {
                        modele.infecter(randomGenerator);
                        modele.exposerIndividus();
                        modele.recupererIndividus();
                        modele.perdreImmunité();
                    

                        int susceptibles = modele.getNombreSusceptibles();
                        int exposes = modele.getNombreExposes();
                        int infectes = modele.getNombreInfectes();
                        int recuperes = modele.getNombreRecuperes();

                        modele.deplacerIndividusAleatoirement(randomGenerator);
                    
                        writer.write(jour + "," + susceptibles + "," + exposes + "," + infectes + "," + recuperes + "\n");
                    }

                }
            }
             catch (IOException e) {
                e.printStackTrace();
            }

            System.out.println("Répétition " + repetition + " terminée. Les données ont été enregistrées dans '" + nomFichier + "'.");
        }

    }
}
