# SMA-SEIR-Repro

Here is the C++ code and results of the colaborative project of reproducing a SEIR model.

In order to run this project, on Linux system : 

Command : Jupyter notebook&
This should open a jupyter notebook.

Inside the Jupyter notebook, the first command is "make" to compile C++ files.  
Then, ./replicationSimulation.sh config 30 run 30 replications of the simulation with config file, initialized with 30 different Mersenne Twister statuses. 

Generated results are stored in logX.txt

Python code in the jupyter notebook will generate figures and CSV. 


## Needed : 
sudo apt-get install gcc (to have g++ compiler).  
sudo apt-get install jupyter  
sudo apt-get install python  
pip install matplotlib  
pip install csv  
pip install scipy  
pip install pandas  
pip install numpy  

