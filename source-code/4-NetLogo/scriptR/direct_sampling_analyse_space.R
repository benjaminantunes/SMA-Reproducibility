library(ggplot2)
library(plyr)
library(reshape2)

setwd("~/github/repro-seir/")

data.df <- read.csv("directSampling_m1Seir.csv", header = T)
names(data.df)
# [1] "popInit"              "infectionRadiusI"     "distRandomWalk"       "angleRotatRandomWalk" "integraleInfected"    "integraleExposed"    
# [7] "openmole.experiment"

cdata <- ddply(data.df, c("popInit", "infectionRadiusI", "distRandomWalk", "angleRotatRandomWalk"), summarise,
               # meanIntegraleInfected    = mean(integraleInfected),
               # meanIntegraleExposed = mean(integraleExposed),
               medianIntegraleInfected    = median(integraleInfected),
               medianIntegraleExposed = median(integraleExposed)
               )
cdata

plot(cdata)


## Si on fixe popInit et infectionRadius
### Test 1 avec une population de 500
sel <- cdata$popInit==500 & cdata$infectionRadiusI == 2 

b <- melt(cdata[sel,], id.vars=c("popInit","infectionRadiusI","distRandomWalk", "angleRotatRandomWalk"))

ggplot(data = b)+
  geom_boxplot(aes(x = as.factor(distRandomWalk), y = value, color = variable))+
  theme(axis.text.x = element_text(angle = 90, vjust = 0.5, hjust=1))+
  labs(x = "Random walk distance", subtitle = "popInit==500 and infectionRadiusI == 2")+
  scale_color_discrete(name="Median",
                      breaks=c("medianIntegraleInfected", "medianIntegraleExposed"),
                      labels=c("Integrale Infected", "Integrale Exposed"))+
  ylim(0,100)
ggsave("img/space_influence_distance500_2.png")



sel <- cdata$popInit==500 & cdata$infectionRadiusI == 2 & cdata$distRandomWalk == 5

a <- melt(cdata[sel,], id.vars=c("popInit","infectionRadiusI","distRandomWalk","angleRotatRandomWalk"))

ggplot(data = a, aes(x = as.factor(angleRotatRandomWalk), y = value, color = variable, group = variable))+
  geom_point()+
  geom_line() +
  theme(axis.text.x = element_text(angle = 90, vjust = 0.5, hjust=1))+
  labs(x = "angle rotation for random walk", subtitle = "popInit==500 and infectionRadiusI == 2")+
  scale_color_discrete(name="Median",
                       breaks=c("medianIntegraleInfected", "medianIntegraleExposed"),
                       labels=c("Integrale Infected", "Integrale Exposed"))+
  ylim(0,100)
ggsave("img/space_influence_angle500_2.png")


### Test 2 avec une population de 1000
sel <- cdata$popInit==1000 & cdata$infectionRadiusI == 2 

b <- melt(cdata[sel,], id.vars=c("popInit","infectionRadiusI","distRandomWalk", "angleRotatRandomWalk"))

ggplot(data = b)+
  geom_boxplot(aes(x = as.factor(distRandomWalk), y = value, color = variable))+
  theme(axis.text.x = element_text(angle = 90, vjust = 0.5, hjust=1))+
  labs(x = "Random walk distance", subtitle = "popInit==1000 and infectionRadiusI == 2")+
  scale_color_discrete(name="Median",
                       breaks=c("medianIntegraleInfected", "medianIntegraleExposed"),
                       labels=c("Integrale Infected", "Integrale Exposed"))+
  ylim(0,100)
ggsave("img/space_influence_distance1000_2.png")



sel <- cdata$popInit==1000 & cdata$infectionRadiusI == 2 & cdata$distRandomWalk == 5

a <- melt(cdata[sel,], id.vars=c("popInit","infectionRadiusI","distRandomWalk","angleRotatRandomWalk"))

ggplot(data = a, aes(x = as.factor(angleRotatRandomWalk), y = value, color = variable, group = variable))+
  geom_point()+
  geom_line() +
  theme(axis.text.x = element_text(angle = 90, vjust = 0.5, hjust=1))+
  labs(x = "angle rotation for random walk", subtitle = "popInit==1000 and infectionRadiusI == 2")+
  scale_color_discrete(name="Median",
                       breaks=c("medianIntegraleInfected", "medianIntegraleExposed"),
                       labels=c("Integrale Infected", "Integrale Exposed"))+
  ylim(0,100)
ggsave("img/space_influence_angle1000_2.png")
