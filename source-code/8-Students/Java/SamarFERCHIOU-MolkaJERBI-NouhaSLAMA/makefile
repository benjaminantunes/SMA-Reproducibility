# Spécifie le compilateur Java
JAVAC = javac

# Spécifie le dossier pour les fichiers source Java
SRC_DIR = src

# Spécifie le dossier pour les fichiers compilés (.class)
BIN_DIR = bin

# Liste de tous les fichiers source Java
SOURCES = $(wildcard $(SRC_DIR)/*.java)

RESULTS_DIR = resultats

# Liste de tous les fichiers compilés (.class)
CLASSES = $(patsubst $(SRC_DIR)/%.java, $(BIN_DIR)/%.class, $(SOURCES))

# Règle par défaut : compile tous les fichiers source
all: $(RESULTS_DIR) $(CLASSES)

$(RESULTS_DIR):
	mkdir -p $(RESULTS_DIR)
# Règle pour la compilation des fichiers source Java en fichiers .class
$(BIN_DIR)/%.class: $(SRC_DIR)/%.java
	$(shell mkdir -p $(BIN_DIR))
	$(JAVAC) -d $(BIN_DIR) $(SRC_DIR)/*.java

# Règle pour l'exécution du programme Java
run: all
	java -cp $(BIN_DIR) Simulation

# Règle pour nettoyer les fichiers générés
clean:
	rm -rf $(BIN_DIR)	
