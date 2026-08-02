package com.example;

public class Individu{

	//Attributs de l'individu
    private int dE;
    private int dI;
    private int dR;
    private int x;
    private int y;
    private Statut statut;
    private int temps_ecoule_statut;
    
    
    
    //le constructeur
    Individu(Statut statut, int temps_ecoule_statut){
    	RandomSingleton.getInstance().setSeed(12345);
    	this.dE = (int)  RandomSingleton.getInstance().negExp(3.);
        this.dI = (int)  RandomSingleton.getInstance().negExp(7.);
        this.dR = (int)  RandomSingleton.getInstance().negExp(365.);
        this.x = RandomSingleton.getInstance().nextInt(GrillePeriodique.getLargeur());
        this.y = RandomSingleton.getInstance().nextInt(GrillePeriodique.getHauteur());
        this.statut = statut;
        this.temps_ecoule_statut = temps_ecoule_statut;  
    }
    
    //Getters et Setters des attributs
    public int getdE() {
        return dE;
    }
    public void setdE(int dE) {
        this.dE = dE;
    }

    public int getdI() {
        return dI;
    }
    public void setdI(int dI) {
        this.dI = dI;
    }
    
    public int getdR() {
        return dR;
    }
    public void setdR(int dR) {
        this.dR = dR;
    }
    
    public int getX() {
	return x;
    }
    public void setX(int x) {
	this.x = x;
    }
	
    public int getY() {
	return y;
    }

    public void setY(int y) {
	this.y = y;
    }
	
    public Statut getStatut() {
        return statut;
    }

    public void setStatut(Statut statut) {
        this.statut = statut;
    }
    
    public int getTemps_ecoule_statut() {
	return temps_ecoule_statut;
    }

    public void setTemps_ecoule_statut(int temps_ecoule_statut) {
        this.temps_ecoule_statut = temps_ecoule_statut;
    }
	
	
	

    //Infection
    public void deSusceptibleVersExposed(GrillePeriodique grillePeriodique){
    	
      //Nombre des Infections au voisinage de l'individu
      int Ni = this.nombreDesInfections(grillePeriodique);
      double p =  1 - Math.exp(-0.5 * Ni);
      
      if(p > RandomSingleton.getInstance().nextDouble()) {
    	  this.setStatut(Statut.EXPOSED);
          this.setTemps_ecoule_statut(0);
      }
      
      else   this.setTemps_ecoule_statut(this.getTemps_ecoule_statut()+1);  
 
    }

    

    //Exposition
    public void deExposedVersInfected(GrillePeriodique grillePeriodique){
    	
        if (this.temps_ecoule_statut > this.dE){
        	this.setStatut(Statut.INFECTED);
        	grillePeriodique.getGrille()[this.getX()][this.getY()]++;
                this.setTemps_ecoule_statut(0);
        }
        
        else  this.setTemps_ecoule_statut(this.getTemps_ecoule_statut()+1);	 
        
    }
    
    
    //Récupération
    public void deInfectedVersRecovered(GrillePeriodique grillePeriodique){
    	
        if (this.temps_ecoule_statut>this.dI){
        	this.setStatut(Statut.RECOVERED);
        	grillePeriodique.getGrille()[this.getX()][this.getY()]--;
                this.setTemps_ecoule_statut(0);            
        }
        
        else  this.setTemps_ecoule_statut(this.getTemps_ecoule_statut()+1);     	  
                
    }
    
    
    //Perte d'immunité 
    public void deRecoveredVersSusceptible(){
    	
        if (this.temps_ecoule_statut>this.dR){        	
        	this.setStatut(Statut.SUSCEPTIBLE);
                this.setTemps_ecoule_statut(0);           
        }
        
        else this.setTemps_ecoule_statut(this.getTemps_ecoule_statut()+1);
      	          
    }


    //calcul du nombres des individus infected au voisinage d'un individu
    public int nombreDesInfections(GrillePeriodique grillePeriodique){
     int Ni = 0;
     int x = this.getX();
     int y = this.getY();
     int[] voisinsXPos = {-1,0,1};
     int[] voisinsYPos = {-1,0,1};
     
     for(int i = 0 ; i<3 ; i++) {
    	 for(int j=0 ; j<3; j++) {
            Ni += grillePeriodique.getGrille()[(x + voisinsXPos[i]+GrillePeriodique.getLargeur())% GrillePeriodique.getLargeur()][(y + voisinsYPos[j]+GrillePeriodique.getHauteur())%GrillePeriodique.getHauteur()];
    	 }
     }

     return Ni;
     
    }

 


}
