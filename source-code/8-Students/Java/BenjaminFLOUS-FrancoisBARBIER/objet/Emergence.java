package objet;
import java.io.FileWriter;
import java.io.FileReader;
import java.io.IOException;
import java.io.BufferedReader;

public class Emergence
{
    public int tour;
    public int nb_S;
    public int nb_E;
    public int nb_I;
    public int nb_R;
    private FileWriter writer;

    public Emergence()
    {
    this.tour = 0;
    this.nb_S = 19980;
    this.nb_E = 0;
    this.nb_I = 20;
    this.nb_R = 0;
    } 

    private void clear_Emergence()
    {
    this.tour=this.tour+1;
    this.nb_S = 0;
    this.nb_E = 0;
    this.nb_I = 0;
    this.nb_R = 0;
    }  

    public void MAJ(Espace grille)
    {
    clear_Emergence();
        for(int i = 0; i < 20000; i++)
        {
            switch (grille.individus[i].etat)
            {
                case S:
                    nb_S++;
                    break;
                case E:
                    nb_E++;
                    break;
                case I:
                    nb_I++;
                    break;
                case R:
                    nb_R++;
                    break;
            } 
        } 
    }

    public void fermer_writer()
    {
        try
        {
            writer.close();
        }
        catch (Exception e)
        {

        }
    }
}
