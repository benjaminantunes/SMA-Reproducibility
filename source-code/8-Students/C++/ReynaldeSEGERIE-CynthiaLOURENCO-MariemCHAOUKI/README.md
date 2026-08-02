# Projet de Simulation Multi-Agent 🕹️

``SEGERIE Reynalde - LOURENCO Cynthia - CHAOUKI Mariem``

![Image](img/seir.png)


``Exécution du code`` : 

* Sous Windows : ``g++ -I.\include -o main .\src\*.cpp``
* Sous Linux : ``g++ -I./include -o main ./src/*.cpp``

- **3 générateurs (``RandomGenerator``)** sont disponibles : 

1. ``Mersenne Twister``
2. ``LCG (Linear Congruential Generator)``
3. ``Middle-Square`` : ce générateur étant assez mauvais, la simulation donnent des résultats de moins bonne qualité.

Le générateur par défaut est le ``Mersenne Twister``.

## Introduction 📜
Le projet de simulation multi-agent vise à modéliser la propagation d'une maladie infectieuse dans une population. Les individus sont placés sur une grille torïque en 2D et sont caractérisés par leur statut (S, E, I, R) et des paramètres de durée (dE, dI, dR).

## Objectifs 🎯
- Étudier les comportements émergents de la propagation d'une maladie dans la population.
- Optimiser les paramètres pour comprendre les dynamiques de la maladie.
- Explorer les effets de différentes conditions initiales.

## Implémentation du Projet 🛠️

### Diagramme UML

![UML](UML.png)

### Structure de la Grille
- La grille est représentée par une classe `Grid` qui définit les propriétés de la grille, y compris sa taille (300x300), les états possibles (S, E, I, R), et la population.

### Individus (Agents)
- Les individus sont représentés par la classe `Agent`. Chaque individu a un identifiant, un statut, une position, et des paramètres de durée (dE, dI, dR).

### Population
- La classe `Population` gère l'ensemble des agents. Elle initialise la population, ajoute des agents, et permet d'accéder aux agents individuellement ou collectivement.

### Position
- La classe `Position` représente la position des individus dans la grille en 2D.

### Génération de Nombres Aléatoires
- La classe `RandomGenerator` implémente le modèle Singleton pour générer des nombres aléatoires, assurant une génération cohérente et sécurisée tout au long de la simulation.

### États
- Les états (S, E, I, R) sont définis dans l'énumération `State`.

## Comportements des Agents 🤖

### Déplacement Aléatoire
- À chaque pas de temps, tous les individus se déplacent aléatoirement vers une autre cellule de la grille.

### Transmission de la Maladie
- Les individus susceptibles (S) deviennent exposés (E) avec une certaine probabilité s'ils sont à proximité d'individus infectieux (I).

### Exposition et Récupération
- Les individus exposés (E) deviennent infectieux (I) lorsque leur temps d'exposition atteint la durée d'exposition (dE).
- Les individus infectieux (I) deviennent récupérés (R) après avoir passé la durée infectieuse (dI).

### Perte d'Immunité
- Les individus récupérés (R) perdent leur immunité et redeviennent susceptibles (S) après la durée d'immunité (dR).

## Fonctionnement de la simulation

La fonction `simulateAnEpidemic` prends en charge la simulation multi-agent :

1. **Initialisation des populations et des grilles** : Pour chaque simulation, cette fonction initialise une population et une grille. Chaque simulation a sa propre population et grille. La population représente les individus impliqués dans l'épidémie. La grille est utilisée pour modéliser la propagation de l'épidémie dans l'espace et chaque population (```NUM_SIMULATIONS``` populations au total) possède sa propre grille.

2. **Création de fichiers CSV** : La fonction crée un fichier CSV distinct pour chaque simulation. Ces fichiers CSV enregistrent les données de la simulation, notamment le nombre d'individus dans chaque état (susceptible, exposé, infecté, guéri - S,E,I,R) pour chaque jour.

3. **Simulation de l'épidémie** : La fonction effectue la simulation de l'épidémie pour un certain nombre de jours (défini par `NUM_DAYS`). Pour chaque jour, elle simule l'évolution de l'épidémie dans chaque grille (une grille par simulation) en appelant la méthode `simulate()`.

4. **Enregistrement des données dans les fichiers CSV** : Pour chaque simulation et chaque jour, la fonction enregistre le nombre d'individus dans chaque état (S, E, I, R) dans le fichier CSV correspondant à la simulation en cours. Les données comprennent le jour de la simulation, le nombre d'individus susceptibles, le nombre d'individus exposés, le nombre d'individus infectés et le nombre d'individus guéris.

## Résultats notables

Pour chaque résultat, le générateur utilisé est mentionné en puce.

1. **Mersenne Twister (MT)**
Voici le graphique obtenu en effectuant la moyenne des 100 simulations.

![Graphique](img/simulation-average-result-MT.png)

2. **LCG**
Avec le générateur ```LCG (Linear Congruential Generator)```, nous avons une instance au cours de laquelle l'épidémie n'a pas lieue.

![Graphique](img/weird-result1.png)