## Le fichier de raphaël en Julia est trop gros. Il a travailler avec trop d'intervals
## On ne va garder que les valeurs entières

data <- read.csv("~/Téléchargements/data-EDO-Julia.csv")

data <- data[!data$timestamp%%1,] # on ne prend que les valeurs entières 

t(data)

write.table(t(data$value1), "~/Téléchargements/data_susceptible2.csv",
            sep=",",row.names = F, col.names = F)
