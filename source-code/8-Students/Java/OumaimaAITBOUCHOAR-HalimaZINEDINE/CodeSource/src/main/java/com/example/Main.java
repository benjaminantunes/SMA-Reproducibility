package com.example;

public class Main {
    public static void main(String[] args) {
        int NUM_THREADS = 100;
        for (int i = 0; i < NUM_THREADS; i++) {
            Thread thread = new Thread(() -> {
                Simulation simulation = new Simulation();
                simulation.simuler730Iteration(simulation.getGrillePeriodique());
            });
            thread.start();
        }
    }
}
