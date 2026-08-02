library(tidyverse)
library(reshape2)

setwd("~/github/repro-seir/")

data.df <- read.csv("results_bs/m2-seir experiment-table_140420231645.csv", skip = 6)

data.df %>%
  group_by(X.step.) %>%
  summarise(meanI = mean(propInfected), 
            SdI = sd(propInfected),
            meanS = mean(propSuseptible), 
            SdS = sd(propSuseptible),
            meanE = mean(propExposed), 
            SdE = sd(propExposed),
            meanR = mean(propRecovered), 
            SdR = sd(propRecovered),
            ) -> data.s

write_csv(data.s, "results_bs/m2-seir_summerised.csv")

sel <- subset(data.df, select = c("X.step.", "propInfected", "propSuseptible", 
                                  "propExposed", "propRecovered"))

data.m <- melt(sel,id.vars=c("X.step."),
            measured.vars=c("propInfected", "propSuseptible", 
                            "propExposed", "propRecovered"))

ggplot(data = data.m)+
  geom_smooth(aes(x = X.step., y = value, color = variable))+
  labs(x = "time", title = "30 replications")+
  theme_bw()

ggsave("img/replication.png", width = 8)

## create 30 file one per sim
nb <- unique(data.df$X.run.number.)

for(i in nb){
  sel <- data.df$X.run.number.== i
  small.df <- data.df[sel,c(10:13)]
  small.df <- small.df[,c(2,3,1,4)]
  write_csv(x = small.df, file = paste0("results_bs/simu_indiv/result",i,".csv"), col_names = FALSE )
}


