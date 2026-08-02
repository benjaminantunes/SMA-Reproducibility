# A graphic to see influence of each output on varibles 

library("ggplot2")
library('reshape2')

setwd("~/github/repro-seir/")

data.df <- read.csv("results_saltelli/totalOrderIndices.csv")

data.melt <- melt(data.df, id.vars = "output")

ggplot(data = data.melt)+
  geom_bar(aes(x = variable, y = value), stat = "identity")+
  facet_grid(.~output)+
  theme(axis.text.x = element_text(angle = 45, hjust=1))

ggsave("img/totalOrderIndices.png")

##############################################################
## Saltelli M1
##############################################################

data2.df <- read.csv("results_saltelli2_m1Seir/totalOrderIndices.csv")

data2.melt <- melt(data2.df, id.vars = "output")

ggplot(data = data2.melt)+
  geom_bar(aes(x = variable, y = value), stat = "identity")+
  facet_grid(.~output)+
  theme(axis.text.x = element_text(angle = 45, hjust=1))

ggsave("img/totalOrderIndices_sm1.png")
