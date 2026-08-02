## Un script pour éclaté en fichier les simulations individuelles
## produite par netlogo 

setwd("~/github/repro-seir/")

data.df <- read.csv("results_bs/m2-seir experiment-table_140420231645.csv", skip = 6)

for( i in sort(unique(data.df$X.run.number.))){
  sel <- data.df$X.run.number. == i
  df <- data.df[sel,]
  sm.df <- subset(df, select = c(X.step., propSuseptible, propExposed, propInfected, propRecovered))
  colnames(sm.df) <- c("t", "S", "E", "I", "R")
  write.csv(sm.df, file = paste0("results_bs/simu_indiv2/result",i,".csv"),row.names = F)
}
