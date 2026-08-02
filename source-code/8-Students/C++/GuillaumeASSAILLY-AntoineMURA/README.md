# Architecture Logicielle - TP1 

Guillaume ASSAILLY - Antoine Mura


## Execution de notre programme par Jupyter Notebook
Le projet s'exécute avec un cmake en lancant tout simplement le notebook 'Simulation multi agents.ipynb' avec jupyter notebook.
On utilise le générateur de MinGW car celui de Visual Studio ne fonctionnait pas localement sur nos machines, mais celui là fonctionne à merveille (normalement).

## Gestion de l'aléatoire
Nous avons utilisé un mersenne twister comme attribut statique déclaré dans une classe dédiée statique pour s'assurer de son unicité. Ce mersenne twister est initialisé avec une seed précise, et nous nous sommes assurés de la reproductibilité des résultats pour cette seed. 

## Diagramme de Classe

<img src="Diagramme TP Archi.svg" alt="Diagramme de classe" width="500"/>
