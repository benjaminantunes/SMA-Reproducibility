import java.util.Random;
import java.io.FileWriter;
import java.io.IOException;

public class Main 
{
    public static void main(String[] args) 
    {
        for (int i = 1; i < 100; i++)
        {
            //int i =3;
            MersenneTwisterFast random = new MersenneTwisterFast(generateNewSeed());
            Population population = new Population(730, random);
            int[] tableau = population.CountEtat();
            saveSimulationResultsToCSV(i, tableau, "simulation_results_replication_" + i + ".csv", population);
        }
    }

    public static void saveSimulationResultsToCSV(int replication, int[] tableau, String csvFileName, Population population) 
    {
        try (FileWriter writer = new FileWriter(csvFileName)) 
        {
            writer.append("Iteration,CountS,CountE,CountI,CountR\n");
            
            for (int i = 0; i < population.getnumIterations(); i++) 
            {
                writer.append(String.format("%d,%d,%d,%d,%d\n", i, tableau[0], tableau[1], tableau[2], tableau[3]));
                population.getGrid().deplacer();
                tableau = population.CountEtat();
            }
            System.out.println("Les résultats de la simulation (Réplication " + replication + ") ont été enregistrés dans le fichier CSV : " + csvFileName);
        } 
        catch (IOException e) 
        {
            System.err.println("Une erreur s'est produite lors de l'écriture dans le fichier CSV : " + e.getMessage());
        }
    }

    // Méthode pour générer une nouvelle graine aléatoire
    private static int[] generateNewSeed()
    {
        Random rand = new Random();
        int[] seed = { rand.nextInt(), rand.nextInt(), rand.nextInt(), rand.nextInt() };
        return seed;
    }
}
