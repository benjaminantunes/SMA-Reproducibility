package com.example;

import com.opencsv.CSVWriter;

import java.io.FileWriter;
import java.io.IOException;


public class CSVGenerator {
	
   private static int idCSV = 0; 
   private CSVWriter writer;
	   

   //créer un csv file et mettre la première ligne
   public void createCSV() {
	 
	String csvFilePath = "Simulation" + idCSV + ".csv";
	idCSV++;
	        
	try {
	      writer = new CSVWriter(new FileWriter(csvFilePath));
	      String[] header = {"NombreS","NombreE", "NombreI", "NombreR"};
	      writer.writeNext(header);
	           
	     } catch (IOException e) {
	            e.printStackTrace();
	            
	        }
	    }
	    
	    
    //écrire une ligne dans un csvfile
    public void ajouterLigne(Simulation simulation) {
	    	
	    if (writer == null) {
	            System.err.println("Le CSVWriter n'a pas été initialisé.");
	            return;
	    }
	        
	    int[] nombreStatut = simulation.calculNombreStatut();
	    String[] row = {Integer.toString(nombreStatut[0]), Integer.toString(nombreStatut[1]), Integer.toString(nombreStatut[2]), Integer.toString(nombreStatut[3])};
	    writer.writeNext(row);
	        
	    try {
		   writer.flush();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		        }	        
	    }
   
}
