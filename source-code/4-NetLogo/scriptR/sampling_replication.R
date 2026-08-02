library("dplyr")
library("ggplot2")

setwd("~/github/repro-seir/")

df <- read.csv("results_bs/m0-seir simple_replication_experiment-table.csv", skip = 6)

df <- df[df$X.step. == 730,] # on ne prend que les valeurs entières 

# on va tirer 10 fois le même nombre de sample 
# créer des groupes dans un data frame
# et on plotera les boxplot correspondant par groupe

sample.v <- seq(from = 10, to = 100, by = 5) # vecteur du nombre de tirage

df.gp <- data.frame()
for(i in sample.v){
  for(j in 1:10){
    a <- df %>% slice_sample(n = i, replace = T)
    a$gp <- j
    df.gp <- rbind(df.gp, a)
  }
  ggplot(data = df.gp)+
    geom_boxplot(aes(x = as.factor(gp), y = propExposed))+
    labs(x  = "sample", title = paste("nombre de réplication:", i))+
    ylim(0.8,0.95)+
    theme_bw()
  ggsave(paste0("img/sample/sample",i,".png"))
}


