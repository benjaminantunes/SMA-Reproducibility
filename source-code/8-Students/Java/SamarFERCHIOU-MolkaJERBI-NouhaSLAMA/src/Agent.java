 public class Agent 
 {
    private Etats etat;
    private int dE;
    private int dI;
    private int dR;
    private int dEtatCourant; 
    private int x;
    private int y;

    public Agent (Etats etat)
    {
        this.etat= etat;       
        this.x=Simulation.random.nextInt(300);
        this.y=Simulation.random.nextInt(300);
        this.calculParam();
    }
    
    public Etats getEtat()
    {
        return this.etat ; 
    }

    public int getX() {
        return this.x;
    }

    public int getY() {
        return this.y;
    }

    public double loiExponentielle(double lambda) 
    {
        double u = Simulation.random.nextDouble(); 
        return -Math.log(1 - u) * lambda;
    }

    public void calculParam ()
    {
       this.dE = (int) loiExponentielle(3.0);
       this.dI = (int) loiExponentielle(7.0);
       this.dR = (int) loiExponentielle(365.0); 
    }

    public void seDeplacer(Grille grille) 
    {
        if (this.etat == Etats.Infected) 
        {
            grille.decrementerCase(this.x,this.y);
        }

        this.x=Simulation.random.nextInt(300);
        this.y=Simulation.random.nextInt(300);

    }
    
    public void changerEtat(Grille grille)
    {
        switch (this.etat)  
        {
            case Infected : 
                    recuperation();
                    break; 
            case Exposed :
                    exposition();
                    break;
            case Susceptible : 
                    infection(grille); 
                    break; 
            default: 
                    susceptibilite(); 
                    break ;            
        }
        if (this.etat == Etats.Infected)
              grille.incrementerCase(this.x,this.y) ; 
    }

    public void infection (Grille grille)       //S-->E
    {
        double p;
        double u = Simulation.random.nextDouble();
        int Ni = grille.nbVoisins(this); 
        p = 1 - Math.exp(-0.5 * Ni);
        if (u < p )
        {
           etat = Etats.Exposed;
           dEtatCourant= 1 ;
        }
        else 
            dEtatCourant++ ;  
    }
    public void exposition()     //E-->I
    {
        if (dEtatCourant>this.dE)
        {
            etat = Etats.Infected;
            dEtatCourant= 1 ;
        }
        else 
            dEtatCourant++ ;  
    }
    public void recuperation()    //I-->R
    {
        if (dEtatCourant>this.dI)
        {
            etat = Etats.Recovered;
            dEtatCourant= 1 ;
        }
        else 
            dEtatCourant++ ;  
    }
    public void susceptibilite()    //R-->S
    {
        if (dEtatCourant>this.dR)
        {
            etat = Etats.Susceptible;
            dEtatCourant= 1 ;
        }
        else 
            dEtatCourant++ ;  
    }

 }

enum Etats
    {
        Susceptible,Exposed,Infected,Recovered
    }