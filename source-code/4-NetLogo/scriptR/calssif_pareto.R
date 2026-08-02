## Une tentative de selectionné parmis les résultat les plus pertinant du front 
## de pareto ceux qui pourrait être mis dans en parametre du modèle
## Pour essayer d'y voir un peut clair, j'ai utilise une CAH sur les valeur d'entré
## pour essayer d'avoir un clustering et donc des individus groupé


library("ggplot2")

## suprimer les colonnes de la fin qui contienne toutes les valeurs de la population
# system("cut -d, -f11- --complement ~/Téléchargements/population400.csv  > ~/Téléchargements/tmp4.csv")
## l'argument -f désigne les colonne a surprimé.  4-7 par exemple ou 11- jusqu'a la fin.

data.df <- read.csv("~/Téléchargements/tmp4.csv")
data.df <- data.df[,1:10]

## identification du front de pareto
ggplot(data = data.df)+
  geom_point(aes(x = objective.arraySuseptible, y = objective.arrayInfected))+
  theme_bw()
ggsave()

## On cherche a minimiser les deux objectif qui sont dans les deux cas la distance à la médiane
## sur l'ensemble de la simulation. 


sel <- data.df$objective.arraySuseptible < 75 & data.df$objective.arrayInfected < 50

min.df <- data.df[sel,]

mydi = dist(min.df[,-c(9,10)])
myclust <- hclust(mydi, method="ward.D2")
# Afficher le dendrogramme en indiquant comme étiquette les résultats du k-means (cluster_l$cluster

plot(myclust) # labels est optionnel

min.df$class <- cutree(myclust,4)

ggplot(data = min.df)+
  geom_point(aes(x = objective.arraySuseptible, y = objective.arrayInfected, 
                 color = as.factor(class)))+
  theme_bw()

write.table(min.df[min.df$class == 3,], "~/Téléchargements/classif.csv", row.names = F, 
            col.names = F, sep = ",")
