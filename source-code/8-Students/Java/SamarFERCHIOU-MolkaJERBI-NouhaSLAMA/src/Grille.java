public class Grille {
    private int[][] grille;
    private static final int NOMBRE_DE_LIGNES = 300;
    private static final int NOMBRE_DE_COLONNES = 300;

    public Grille() 
    {
        grille = new int[NOMBRE_DE_LIGNES][NOMBRE_DE_COLONNES];
    }

     public int getCase(int x, int y)
    {
        return grille[x][y];
    }
    public void incrementerCase(int x, int y)
    {
        grille[x][y]++;
    }
    public void decrementerCase(int x, int y)
    {
        grille[x][y]--;
    }
    
    public int nbVoisins(Agent agent) 
    {
        int x = agent.getX();
        int y = agent.getY();
        int Ni = this.getCase(x, y);

        int[] dx = {-1, -1, -1, 0, 0, 1, 1, 1};
        int[] dy = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int i = 0; i < 8; i++) 
        {
            int voisinX = (x + dx[i] + NOMBRE_DE_LIGNES) % NOMBRE_DE_LIGNES;
            int voisinY = (y + dy[i] + NOMBRE_DE_COLONNES) % NOMBRE_DE_COLONNES;

            Ni += this.getCase(voisinX, voisinY);
        }
        return Ni;
    }   
}






