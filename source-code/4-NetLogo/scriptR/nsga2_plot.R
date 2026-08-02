library(ggplot2)
library(knitr)

data.df <- read.csv("~/github/repro-seir/resultats_nsga2/population1300.csv")
data.df$densityInit <- data.df$popInit/1024 

ggplot(data = data.df)+
  geom_point(aes(x = objective.integraleExposed, y = objective.integraleInfected, size = evolution.samples, colour = densityInit))+
  # geom_segment(aes(x = 1.5, y = 20, xend = 1, yend = 9.2),
  #              arrow = arrow(length = unit(0.5, "cm")))+
  # geom_segment(aes(x = 22, y = 20, xend = 21.1, yend = 12.2),
  #              arrow = arrow(length = unit(0.5, "cm")))+
  # annotate(geom="text", x=1.5, y=21, label="1")+
  # annotate(geom="text", x=22, y=21, label="2")+
  theme_bw()+
  labs(title = "1300 evolutions for NSGA2", 
       subtitle = "multi-obj : infected and exposed",
       x = paste0("\u2211","\u0394","Exposed"),
       y = paste0("\u2211","\u0394","Infected"),
       size = "samples", 
       colour = "density")

ggsave("~/github/repro-seir/img/nsga2_evol1300.png", width = 10, height = 5)

ggplot(data = data.df)+
  geom_point(aes(x = objective.integraleExposed, y = objective.integraleInfected, size = evolution.samples, colour = infectionRadiusI))+
  # geom_segment(aes(x = 35, y = 35, xend = 27, yend = 25),
  #             arrow = arrow(length = unit(0.5, "cm")),
  #             colour = "grey")+
  # annotate(geom="text", x=36, y=36, label="3")+
  theme_bw()+
  labs(title = "1300 evolutions for NSGA2",
       subtitle = "multi-obj : infected and exposed",
       x = paste0("\u2211","\u0394","Exposed"),
       y = paste0("\u2211","\u0394","Infected"))+
  xlim(0, 50)+
  ylim(30,45)

ggsave("~/github/repro-seir/img/nsga2_evol1300_radius_zoom.png", width = 8, height = 5)
# 
# 
 sel <- data.df$evolution.samples >= 75
small.df <- data.df[sel,2:7]
knitr::kable(small.df, "pipe") 
 
################################################################
## 2nd analyse ou on fait varier les paramètres de déplacement
#############################################################
data2.df <- read.csv("~/github/repro-seir/resultsNSGA2_m1Seir/population1600.csv")
data2.df$densityInit <- data2.df$popInit/1024 

ggplot(data = data2.df)+
  geom_point(aes(x = objective.integraleExposed, y = objective.integraleInfected, size = evolution.samples, colour = densityInit))+
  # geom_segment(aes(x = 1.5, y = 20, xend = 1, yend = 9.2),
  #              arrow = arrow(length = unit(0.5, "cm")))+
  # geom_segment(aes(x = 22, y = 20, xend = 21.1, yend = 12.2),
  #              arrow = arrow(length = unit(0.5, "cm")))+
  # annotate(geom="text", x=1.5, y=21, label="1")+
  # annotate(geom="text", x=22, y=21, label="2")+
  theme_bw()+
  labs(title = "1300 evolutions for NSGA2", 
       subtitle = "multi-obj : infected and exposed",
       x = paste0("\u2211","\u0394","Exposed"),
       y = paste0("\u2211","\u0394","Infected"),
       size = "samples", 
       colour = "density")


ggplot(data = data2.df)+
  geom_point(aes(x = objective.integraleExposed, y = objective.integraleInfected, size = evolution.samples, colour = infectionRadiusI))+
  theme_bw()+
  labs(title = "1600 evolutions for NSGA2",
       subtitle = "multi-obj : infected and exposed (space effect)",
       x = paste0("\u2211","\u0394","Exposed"),
       y = paste0("\u2211","\u0394","Infected"))+
  xlim(0, 50)+
  ylim(30,45)

ggsave("~/github/repro-seir/img/nsga2_evol1600_radius_zoom_randomWoalk.png", width = 8, height = 5)
