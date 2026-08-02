package com.example;

public class Simulation {
	
   private CSVGenerator csvGenerator;
   private GrillePeriodique grillePeriodique;
    
    public Simulation() {
    	csvGenerator = new CSVGenerator();
    	grillePeriodique = new GrillePeriodique();
    	
    }
    
	

    public GrillePeriodique getGrillePeriodique() {
	return grillePeriodique;
    }


    //effectuer la simulation 730 fois : itérations    
    public void simuler730Iteration(GrillePeriodique grillePeriodique) {
    	
    	csvGenerator.createCSV();
    	grillePeriodique.initialiserGrille();
    	csvGenerator.ajouterLigne(this);
    	
   	for(int j=1; j<731; j++) { 
   	    	
   	    	this.simulerIterationGrille(grillePeriodique);
    		csvGenerator.ajouterLigne(this);
    		
     	}
    	
    }
    

    //processus de chaque iteration
    public void simulerIterationGrille(GrillePeriodique grillePeriodique){
    	
    	grillePeriodique.deplacerIndividus();
    	grillePeriodique.changeStatuts();

    }
    
    
    //calcul du nombre d'individus dans chaque statut
    public int[] calculNombreStatut() {
    	
    	int[] nombreStatut = {0,0,0,0}; 
    	
    	for (Individu individuActuel : this.grillePeriodique.getIndividus()) {
    	    	 switch(individuActuel.getStatut()) {
                
                	 case SUSCEPTIBLE: {
                		 	    nombreStatut[0]++;
                	                    break;
                	      }
                	 
                	 case EXPOSED: {
                		 	    nombreStatut[1]++;
	                                    break;
	                      }
                	 
                	 case INFECTED: {
                		 	    nombreStatut[2]++;
	                                    break;
	                      }
                	 
                	 case RECOVERED: {
                		 	     nombreStatut[3]++;
	                                     break;
	                      }
                  }
                	 
        }
                   	 
    	return nombreStatut;
}
	
	
	
}
