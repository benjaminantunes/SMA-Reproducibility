import java.io.FileWriter;
import java.io.IOException;
import java.util.List;
import java.util.ArrayList;

public class Simulation
{   
    private List<int[]> resultats = new ArrayList<>();
    public static MTRandom random = new MTRandom(true);
    
    public static void resultatToCSV(FileWriter writer, int[] resultat) throws IOException 
    {  
        for (int i = 0; i < 4; i++) 
                {
                    writer.append(String.valueOf(resultat[i] / 20000.0));
                    if (i < 3) {
                        writer.append(",");
                    }
                }
                writer.append("\n");
        }        
       



    public static void main(String[] args) 
    {   
      String csvFileName;
      for(int j=0; j<100;j++)
      {
        csvFileName = "resultats/exp"+j+".csv";
        
        try (FileWriter writer = new FileWriter(csvFileName) )
        {
            writer.append("I,E,S,R\n");
            Simulation simulation = new Simulation();
            Grille grille = new Grille();
            int[] resultat = {0,0,0,0};
            Population population = new Population(grille);
            population.resultat(resultat);
            
            for(int i = 0; i < 730; i++)
            {   
                for (int k =0;k<4;k++)
                {
                    resultat[k] = 0; 
                }
                population.melanger();
                population.faireEvoluer(grille);
                population.resultat(resultat);
                resultatToCSV( writer,resultat) ; 
                
            }
            writer.close();
        }
        catch (IOException e) 
        {
           e.printStackTrace();
        }
    }
  }
}