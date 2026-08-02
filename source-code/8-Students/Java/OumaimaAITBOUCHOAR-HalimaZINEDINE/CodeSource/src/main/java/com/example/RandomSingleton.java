package com.example;

import java.util.Random;
import java.lang.Math;

public class RandomSingleton extends Random{
	
    private static RandomSingleton randomInstance = new RandomSingleton();


    private RandomSingleton() {
        // Constructeur privé pour évité l'instantiation
    }

    public static RandomSingleton getInstance() {
 
        return randomInstance;
    }
    
   
    //la methode negExp expliqué dans l'énoncé
    public double negExp(double inMean) { 
    	
    	Random random = new Random();
        return -inMean * Math.log(1 - random.nextDouble()); } 

}
