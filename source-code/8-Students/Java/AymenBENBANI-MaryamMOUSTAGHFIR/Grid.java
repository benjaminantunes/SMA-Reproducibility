//import java.util.Random;
//import java.util.List;

public class Grid 
{
    private int width;
    private int height;
    private Individu [] individus;
    private int [] randArray;
    private int [][] IndividuInfected;
    private int nombreAgents = 20000;
    
    public Grid(int width, int height)  //constructeur
    {  
        this.width = width;
        this.height = height;
        this.randArray = new int[nombreAgents];
        for (int i = 0;i<nombreAgents;i++)
        {
            randArray[i]= i ;
        }

        this.individus =new Individu[nombreAgents];
        addIndividualsToGrid(0,19980,Etat.S);
        addIndividualsToGrid(19980,nombreAgents,Etat.I);
        this.IndividuInfected = new int[width][height];
        
    
    }
    public int [] getrandArray()
    {
        return this.randArray;
    }
    public Individu [] getIndividus()
    {
        return this.individus;
    }

    public void randomizeArray(int[] array)
    {
    
        for (int i = 0; i < array.length; i++) 
        {

            // Générer un index aléatoire entre i et la fin du tableau
            int index = i + Individu.getInt(array.length - i);
    
            // Échanger l'élément à l'index i avec l'élément à l'index aléatoire
            int temp = array[i];
            array[i] = array[index];
            array[index] = temp;
        }
    }


    public int countInfectedNeighbors(int x, int y)
    {
        int count = 0; // Initialiser le compteur à zéro

        // Coordonnées des cellules voisines
        int[] neighborX = {x - 1, x - 1, x - 1, x, x, x + 1, x + 1, x + 1};
        int[] neighborY = {y - 1, y, y + 1, y - 1, y + 1, y - 1, y, y + 1};

        // Parcourir les cellules voisines
        for (int i = 0; i < 8; i++) 
        {
            int neighborXCoord = neighborX[i];
            int neighborYCoord = neighborY[i];

            // Assurez-vous que les coordonnées restent dans les limites de la grille toroïdale
            neighborXCoord = (neighborXCoord + width) % width;
            neighborYCoord = (neighborYCoord + height) % height;
            count += IndividuInfected[neighborXCoord][neighborYCoord];

            
        }
        return count;
    }
    

    public void addIndividualsToGrid(int dep,int arr,Etat statut) 
    {
        for (int i = dep; i < arr; i++) 
        {
            individus[i] = new Individu(statut,this.width,this.height);
        }
    }
    public void initGrid()
    {
        for (int i=0;i<width;i++)
        {
            for (int j=0;j<height;j++)
            {
                IndividuInfected[i][j] =0;
                
            }
        }
    }

    public void deplacer()
    {
        Individu[] agents = getIndividus(); 
        randomizeArray(getrandArray());
        for (int i =0;i<20000;i++)
        {
            int agent = getrandArray()[i];
            agents[agent].changerEtat(countInfectedNeighbors(agents[agent].getPositionX(),agents[agent].getPositionY()));
            agents[agent].deplacerAgent(getwidth(),getheight());

        }
    }

    //les getters 
    public int getwidth()
    {
        return this.width;
    }
    public int getheight()
    {
        return this.height;
    }
    
    public int[][] getIndividuInfected()
    {
        return this.IndividuInfected;

    }
    

    





    
    
}
