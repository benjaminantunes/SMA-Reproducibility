public class Population
{
    private Agent[] agents;
    public Population(Grille grille)
    {
        this.agents = new Agent[20000]; 
        for(int i = 0; i < 20; i++)
        {
            agents[i] = new Agent(Etats.Infected);
            grille.incrementerCase(this.agents[i].getX(),this.agents[i].getY()); 
            
        }

        for(int i = 20; i < 20000; i++)
        {
            agents[i] = new Agent(Etats.Susceptible);
        }
    }

    public void melanger() 
    {
        for (int i = 20000 - 1; i > 0; i--) 
        {
            int j = Simulation.random.nextInt(i + 1);

            Agent temp = agents[i];
            agents[i] = agents[j];
            agents[j] = temp;
        }
    }
    
    public void faireEvoluer(Grille grille)
    {   
        for (Agent agent : agents) 
        {
            agent.seDeplacer(grille);
            agent.changerEtat(grille);
        }
    }

    public void resultat(int resultat[])
    {
        for (Agent agent : agents) 
        {
            switch (agent.getEtat())  
            {
            case Infected : 
                    resultat[0]++;
                    break; 
            case Exposed :
                    resultat[1]++;
                    break;
            case Susceptible : 
                    resultat[2]++; 
                    break; 
            default: 
                    resultat[3]++; 
                    break ;            
            }
        }
    }
}