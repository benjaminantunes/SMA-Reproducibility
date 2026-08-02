#!/usr/bin/env Rscript
# DTW clustering robustness: downsample the infected series (every 5th step) so the
# full pairwise DTW is tractable, then reproduce the published hybrid DTW (k=2,
# excluding no-reinfection runs). Compares to the published DTW composition.
suppressMessages({library(data.table); library(dtw)})
set.seed(123)
BASE <- normalizePath(getwd())
e<-new.env(); load(file.path(BASE,"data/harmonized/df_SMA_serveur_VF.RData"),envir=e)
df<-as.data.table(get("df",envir=e))
df<-df[!Langage %in% c("Netlogo Etienne","Netlogo Hanae")]; df[Langage=="Netlogo Dorian",Langage:="Netlogo"]
w<-dcast(df, simu+Langage~step, value.var="I"); labs<-as.character(w$Langage); M<-as.matrix(w[,-(1:2)])

# exclude no-reinfection runs (as in the published DTW analysis)
lateI <- df[step>=400, .(lateI=mean(I)), by=simu]
keep <- w$simu %in% lateI[lateI>=1e-4, simu]
Mk<-M[keep,]; labk<-labs[keep]
# downsample every 5th step (731 -> 147 points)
idx <- seq(1, ncol(Mk), by=5)
Md <- Mk[, idx]
cat(sprintf("kept %d sims (dropped %d no-reinfection); series length %d -> %d after downsampling\n",
            sum(keep), sum(!keep), ncol(Mk), ncol(Md)))

D <- dtwDist(Md)                       # full pairwise DTW on the short series
hcD<-hclust(as.dist(D),"ward.D2"); grpD<-cutree(hcD,2)
centD<-t(sapply(1:2, function(k) colMeans(Md[grpD==k,,drop=FALSE])))
kmD<-kmeans(Md, centers=centD, iter.max=100)

compo <- function(cl, tag){
  cat("\n===", tag, "===\n")
  for(k in sort(unique(cl))){tb<-sort(round(100*table(labk[cl==k])/sum(cl==k)),decreasing=TRUE);tb<-tb[tb>0]
    cat(sprintf("Cluster %d (%d): %s\n",k,sum(cl==k),paste(sprintf("%s %d%%",names(tb),tb),collapse=", ")))}
}
compo(grpD, "DTW hierarchical (k=2), downsampled")
compo(kmD$cluster, "DTW hybrid (hier -> k-means), downsampled")
cat("\n--- PUBLISHED DTW ---\n")
cat("C1(59): 51% C++, 42% Julia, 3% GAMA, 3% NetLogo\n")
cat("C2(147): 20% DSDEVS, 20% Python, 19% GAMA, 19% NetLogo, 18% Cormas, 3% Julia\n")

sink(file.path(BASE,"results/dtw_downsampled_report.txt"))
compo(kmD$cluster, "DTW hybrid (hier -> k-means), downsampled (every 5th step)")
sink()
