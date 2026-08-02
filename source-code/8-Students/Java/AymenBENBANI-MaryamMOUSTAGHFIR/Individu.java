public class Individu
{
    private int dE;
    private int dI;
    private int dR;
    private Etat Statut;
    private int TempsEcoule;
    private int positionX;
    private int positionY;


    
    private static MersenneTwisterFast random = new MersenneTwisterFast(new int []{0x567,0X786,0x50,0x136 });
   
    public Individu(Etat statut,int width,int height) //constructeur
    { 
        // Utilisation de la méthode GenererTempsExponentiel pour calculer les valeurs dE, dI et dR
        dE = GenererTempsExponentiel(3.0);
        dI = GenererTempsExponentiel(7.0);
        dR = GenererTempsExponentiel(365.0);
         
        this.Statut = statut;
        TempsEcoule = 0;
        positionX = random.nextInt(width);
        positionY = random.nextInt(height);
    }

    public void changerEtat(int nombreInfected)
    {
        switch (Statut) 
        {
            case S:
                double probability = 1.0 - Math.exp(-0.5 * nombreInfected);

                if (random.nextDouble() <= probability)
                {
                    setStatut(Etat.E);
                    ResetTempsEcoule();
                }               
                break;
            case E:
                if (TempsEcoule > dE)
                {
                    setStatut(Etat.I);
                    ResetTempsEcoule();
                }
                break;
            case I: 
                if (TempsEcoule > dI)
                {
                                    
                    setStatut(Etat.R);
                    ResetTempsEcoule();
                }
                break;
            case R:
                if (TempsEcoule > dR)
                {
                    setStatut(Etat.S);
                    ResetTempsEcoule();
                }
                break;
        }
    }

    //les getteurs 

    public Etat getStatut() 
    {
        return this.Statut;
    }
   
    public int getPositionX() 
    {
        return this.positionX;
    }

    public int getPositionY() 
    {
        return this.positionY;
    }
    public int getTempsEcoule()
    {
        return this.TempsEcoule;

    }
    
    public static int getInt(int n)
    {

        return random.nextInt(n);
    }
    //les setteurs
     public void setStatut(Etat statut)
    {
        this.Statut = statut;
    }
 


    // Méthode pour générer un temps basé sur une loi exponentielle négative
    private int GenererTempsExponentiel(double inMean) 
    {
        double randomValue = random.nextDouble();
        return (int)(-inMean * Math.log(1.0 - randomValue));
    }

    public void IncrementeTempsEcoule()
    {
        this.TempsEcoule ++;
    }

    public void ResetTempsEcoule()
    {
        this.TempsEcoule = 0;
    }

    public void deplacerAgent(int width,int height)
    {
        IncrementeTempsEcoule();
        this.positionX = random.nextInt(width);
        this.positionY = random.nextInt(height);
    }
    

}