
public class Personne {
    
    /**
     * etat de la personnes (S, E, I ou R)
     */
    private char etat;  

    private int temps_ecoule ;

    private int dE;

    private int dI;

    private int dR;

    private boolean aFaitLaTransition;


    
    /**
     * position en x de la personne
     */
    private int position_x; 
    
    /**
     * position en y de la personne
     */
    private int position_y; 
    

    //méthodes:

    //Constructeur d'une personne
    public Personne(char e ,int ex, int i,int r, int x, int y) {
        temps_ecoule=0;
        etat = e;
        dE = ex;
        dI = i;
        dR = r;
        this.aFaitLaTransition = false; // Initialisation à false
        // On place la personne sur une position du Monde
        position_x = x;
        position_y = y;
    }

    //
    public char getEtat(){
        return etat;
    }
    
    /**
     * 
     * @return la position en x de la personne 
     */
    public int getPosition_x(){
        return position_x;
    }
    
    /**
     * 
     * @return la position en y de la personne 
     */
    public int getPosition_y(){
        return position_y;
    }

    public int getTemps_ecoule(){
        return temps_ecoule;
    }

    public int  getDE(){
        return dE;
    }

    public int getDI(){
        return dI;
    }

    public int getDR(){
        return dR;
    }

    public void setEtat(char e){
        etat = e;
    }


    public void setPosition_x(int x){
        position_x = x;
    }


    public void setDE(int e){
        dE=e;
    }

    public void setDI(int i){
        dI=i;
    }
    
    public void setDR(int r){
        dR=r;
    }
    /**
     * 
     * @param y mettre à jour la position en y de la personne
     */
    public void setPosition_y(int y){
        position_y = y;
    }
    


    public void setTemps_ecoule(int t){
        temps_ecoule = t;
    }

    public boolean getAFaitLaTransition() {
        return aFaitLaTransition;
    }

    public void setAFaitLaTransition(boolean aFaitLaTransition) {
        this.aFaitLaTransition = aFaitLaTransition;
    }


}