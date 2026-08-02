package com.example;


public class GrillePeriodique {
	
    //attribut de la GrillePeriodique
    private static final int LARGEUR = 300;
    private static final int HAUTEUR = 300;
    private static final int NUM_POPULATION = 20000;
    private Individu[] individus;
    private int[][] grille = new int[300][300];
    
    
    //constructeur de la GrillePeriodique
    public GrillePeriodique(){
        grille = new int [LARGEUR][HAUTEUR];
        individus = new Individu[NUM_POPULATION];   
    }
    
    
   //Getters
    
    public static int getLargeur() {
	return LARGEUR;
    }

    public static int getHauteur() {
	return HAUTEUR;
    }
	
    public int[][] getGrille() {
	return grille;
    }
	
    public Individu[] getIndividus() {
	return individus;
    }
  
    
    //initialser la grille par les individus de l'enoncé
    public void initialiserGrille(){
    	
    	int numInfected = 20;	
    	
    	for(int i=0; i<numInfected; i++){
             Individu individu = new Individu(Statut.INFECTED , 0 );
             this.grille[individu.getX()][individu.getY()]++;
             this.individus[i] = individu;            
        }
    	 
        for(int i=numInfected; i<NUM_POPULATION; i++){
            Individu individu = new Individu(Statut.SUSCEPTIBLE , 0 );
            this.individus[i] = individu;
        }
        
    }
    

    //Deplacer tous les individus 
    public void deplacerIndividus() {
    	
        for (Individu individu : this.individus) {
            if (individu.getStatut() == Statut.INFECTED) {
            	
                this.grille[individu.getX()][individu.getY()]--; 
                individu.setX(RandomSingleton.getInstance().nextInt(GrillePeriodique.getLargeur()));
                individu.setY(RandomSingleton.getInstance().nextInt(GrillePeriodique.getHauteur()));
                this.grille[individu.getX()][individu.getY()]++;

            } else {
                individu.setX(RandomSingleton.getInstance().nextInt(GrillePeriodique.getLargeur()));
                individu.setY(RandomSingleton.getInstance().nextInt(GrillePeriodique.getHauteur()));
            }
        }
    }

    
    
    
    //Changer le statut des individus
    public void changeStatuts(){
    	for(Individu I : this.individus) {
        	switch(I.getStatut()){
        
             	  case SUSCEPTIBLE :  { I.deSusceptibleVersExposed(this); 
            	                        break;                   
                       }
            
                  case EXPOSED     :  { I.deExposedVersInfected(this);
            	                        break;
                      }
            
                  case INFECTED    :  { I.deInfectedVersRecovered(this);
            	                        break;
                      }
            
                  case RECOVERED   :   { I.deRecoveredVersSusceptible(); 
            	                         break;
                     }
 
                }
       }
    }
      		

}

    
