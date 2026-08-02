package objet;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Arrays;

public class Espace
{
    private final int size = 300;
    private final int nb_individus = 20000;
    public Individu[] individus;
    private int [][] grille_malade;

    public Espace()
    {

        this.grille_malade = new int[size][size];
        for (int i = 0 ; i < size ; i++)
            for (int j = 0 ; j < size ; j++)
                grille_malade[i][j] = 0;


        this.individus = new Individu [nb_individus];
        for (int i = 0 ; i < nb_individus - 20 ; i++){
            this.individus[i] = new Individu(Etat.S);
        }

        for (int i = nb_individus - 20 ; i < nb_individus ; i++){
            this.individus[i] = new Individu(Etat.I);
            grille_malade[individus[i].posx][individus[i].posy] ++;
        }


    }

    private int voisin(int x, int y)
    {
        int nb_voisin = 0;
        for(int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                int a = ((x+i)%size == -1) ? size -1 : (x+i) % size;
                int b = ((y+i)%size == -1) ? size -1 : (y+i) % size;
                nb_voisin = nb_voisin + grille_malade[a][b];  
            }
        }
        return nb_voisin;
    }

    public void maj_individus(){
        int nb_voisin;
        List<Individu> listeIndividus = new ArrayList<>(Arrays.asList(individus));
        Collections.shuffle(listeIndividus);
        listeIndividus.toArray(individus);
        for(int i = 0; i < nb_individus; i++){
            nb_voisin = voisin(individus[i].posx, individus[i].posy);
            individus[i].maj_individu(nb_voisin);
        } 
    }

    private void clear_grille(){
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                grille_malade[i][j] = 0;
            }
        }
    }

    public void deplacer_individus(){
        clear_grille();
        List<Individu> listeIndividus = new ArrayList<>(Arrays.asList(individus));
        Collections.shuffle(listeIndividus);
        listeIndividus.toArray(individus);
        for(int i = 0; i < nb_individus; i++){
            individus[i].deplacer_individu();
            if(individus[i].etat == Etat.I)
                grille_malade[individus[i].posx][individus[i].posy]++;            
        }
    }
}