package objet;
import java.util.Random;

public class Individu
{
    
    public Etat etat;
    private int tps;
    private int dE;
    private int dI;
    private int dR;
    int posx;
    int posy;
    Random new_random = new Random();

    public Individu(Etat e){
        this.etat = e;
        this.dE = (int)(-3 * java.lang.Math.log( 1 - new_random.nextDouble()));
        this.dI = (int)(-7 * java.lang.Math.log( 1 - new_random.nextDouble()));
        this.dR = (int)(-365 * java.lang.Math.log( 1 - new_random.nextDouble()));
        this.posx = new_random.nextInt(300);
        this.posy = new_random.nextInt(300);
        tps = 0;
    }

    public void deplacer_individu(){
        tps++;
        posx = new_random.nextInt(300);
        posy = new_random.nextInt(300);
    }

    public void maj_individu(int nb_malade_adjacent){
        switch (etat){
            case S:
                double proba_infect = 1 - java.lang.Math.exp(-0.5*nb_malade_adjacent);
                double p = new_random.nextDouble();
                if(p < proba_infect){
                    etat = Etat.E;
                    tps = 0;
                }
                break;
            case E:
                if (tps > dE){
                    tps = 0;
                    etat = Etat.I;
                }
                break;
            case I:
                if (tps > dI){
                    tps = 0;
                    etat = Etat.R;    
                }
                break;
            case R:
                if (tps > dR){
                    tps = 0;
                    etat = Etat.S;
                }
                break;
            default:
                break;
        }
    }
}