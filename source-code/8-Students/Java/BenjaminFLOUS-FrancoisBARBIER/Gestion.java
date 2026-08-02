import objet.*;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class Gestion {

    public static void main(String[] args) {
        // Répétez la simulation 100 fois
        for (int k = 1; k <= 100; k++) {
            String nomFichier = "Resultat_Simulation_" + k + ".csv";

            try {
                // Ouvrez un fichier pour écrire les résultats
                BufferedWriter writer = new BufferedWriter(new FileWriter(nomFichier));
                Espace grille = new Espace();
                Emergence liste = new Emergence();
                for(int i = 0; i < 730; i++)
                {
                    writer.write(liste.tour+" "+liste.nb_S+" "+liste.nb_E+" "+liste.nb_I+" "+liste.nb_R+" \n");
                    grille.maj_individus();
                    grille.deplacer_individus();
                    liste.MAJ(grille);

                }
                // Fermez le fichier
                writer.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
