#!/usr/bin/env Rscript
# Full clustering on the ORIGINAL df, matching the published hybrid method:
# hierarchical (ward.D2) -> k-means refinement seeded by hierarchical centroids.
# Euclidean (k=8, all sims) and DTW (k=2, excluding no-reinfection runs).
suppressMessages({library(data.table); library(dtw)})
set.seed(123)
BASE <- normalizePath(getwd())
O <- file.path(BASE,"results")
e<-new.env(); load(file.path(BASE,"data/harmonized/df_SMA_serveur_VF.RData"),envir=e)
df<-as.data.table(get("df",envir=e))
df<-df[!Langage %in% c("Netlogo Etienne","Netlogo Hanae")]; df[Langage=="Netlogo Dorian",Langage:="Netlogo"]
w<-dcast(df, simu+Langage~step, value.var="I"); labs<-as.character(w$Langage); M<-as.matrix(w[,-(1:2)])

compo <- function(cl, labs, tag){
  cat("\n=== ", tag, " ===\n")
  for(k in sort(unique(cl))){tb<-sort(round(100*table(labs[cl==k])/sum(cl==k)),decreasing=TRUE);tb<-tb[tb>0]
    cat(sprintf("C%d(%d): %s\n",k,sum(cl==k),paste(sprintf("%s %d%%",names(tb),tb),collapse=", ")))}
}

## --- Euclidean hybrid: hclust ward.D2 (k=8) then k-means seeded by centroids ---
hcE<-hclust(dist(M,"euclidean"),"ward.D2"); grpE<-cutree(hcE,8)
centE<-t(sapply(1:8, function(k) colMeans(M[grpE==k,,drop=FALSE])))
kmE<-kmeans(M, centers=centE, iter.max=100)
compo(grpE, labs, "EUCLIDEAN hierarchical (k=8)")
compo(kmE$cluster, labs, "EUCLIDEAN hybrid (hier -> k-means refinement)")

## The DTW clustering is computed separately in 03_dtw.R.
## The hybrid result reproduces the paper's platform-by-cluster contingency table (Table 5).
sink(file.path(O,"euclidean_clusters_report.txt"))
compo(kmE$cluster, labs, "EUCLIDEAN hybrid (hclust ward.D2 k=8 -> k-means refinement) -- reproduces paper Table 5")
sink()
