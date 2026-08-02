public class Population 
{
    private Grid grid;
    private int numIterations;

    public Population(int numIterations, MersenneTwisterFast random)
    {
        grid = new Grid(300, 300);
        this.numIterations = numIterations;
        
    }
        
    public int[] CountEtat()
    {
        int [] tableau ={0,0,0,0};
        grid.initGrid();
        for (int i = 0;i<20000;i++)
        {
            Etat statut = grid.getIndividus()[i].getStatut();
            switch (statut) 
            {
                case S:
                    tableau[0]++;
                    
                    break;
                case E:
                    tableau[1]++;
                    break;
                case I:
                    tableau[2]++;
                    grid.getIndividuInfected()[grid.getIndividus()[i].getPositionX()][grid.getIndividus()[i].getPositionY()]++;
                    break;
                case R:
                    tableau[3]++;
                    break;    
            
                default:
                    break;
            }
        }
        return tableau;

    }
    //getters
    public Grid getGrid()
    {
        return this.grid;
    }
    public int getnumIterations ()
    {
        return this.numIterations;
    }
   
   
}
