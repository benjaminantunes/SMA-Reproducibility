#!/usr/bin/env Rscript
# DTW clustering, exactly as published: the hybrid procedure applied with DTW.
# Hierarchical step = tsclust (dtwclust) with the dtw_basic distance and its default
# average linkage, no window constraint, k=2; then a k-means refinement seeded by the
# hierarchical cluster centres. The runs without reinfection are excluded first.
# Reproduces the published two-cluster DTW composition (59 / 147).
suppressMessages({library(data.table); library(dtw); library(dtwclust)})
set.seed(123)
BASE <- normalizePath(getwd())
O <- file.path(BASE,"results"); dir.create(O, showWarnings=FALSE)
e<-new.env(); load(file.path(BASE,"data/harmonized/df_SMA_serveur_VF.RData"),envir=e)
df<-as.data.table(get("df",envir=e))
df<-df[!Langage %in% c("Netlogo Etienne","Netlogo Hanae")]; df[Langage=="Netlogo Dorian",Langage:="Netlogo"]
w<-dcast(df, simu+Langage~step, value.var="I"); labs<-as.character(w$Langage); M<-as.matrix(w[,-(1:2)])

# exclude no-reinfection runs (keyed on Langage+simu, aligned to w's row order)
lateI <- df[step>=400, .(lateI=mean(I)), by=.(Langage,simu)]
nrkey <- lateI[lateI<1e-4, paste(Langage,simu)]
keep  <- !(paste(w$Langage,w$simu) %in% nrkey)
Mk<-M[keep,]; labk<-labs[keep]

# hybrid DTW: dtw_basic hierarchical (default avg linkage, k=2) -> k-means refinement
hcD <- tsclust(lapply(seq_len(nrow(Mk)), function(i) Mk[i,]), type="hierarchical", distance="dtw_basic")
grpD<- hcD@cluster
kmD <- kmeans(Mk, centers=aggregate(Mk,list(grpD),mean)[,-1], iter.max=100)

compo <- function(cl, tag){
  cat("\n===", tag, "===\n")
  for(k in sort(unique(cl))){tb<-sort(round(100*table(labk[cl==k])/sum(cl==k)),decreasing=TRUE);tb<-tb[tb>0]
    cat(sprintf("Cluster %d (%d): %s\n",k,sum(cl==k),paste(sprintf("%s %d%%",names(tb),tb),collapse=", ")))}
}
cat(sprintf("kept %d sims (dropped %d no-reinfection); series length %d\n", sum(keep), sum(!keep), ncol(Mk)))
compo(grpD,       "DTW hierarchical (dtw_basic, k=2)")
compo(kmD$cluster,"DTW hybrid (hier dtw_basic -> k-means refinement)")
cat("\n--- PUBLISHED DTW (for comparison) ---\n")
cat("C1(59): 51% C++, 42% Julia, 3% GAMA, 3% NetLogo\n")
cat("C2(147): 20% DSDEVS, 20% Python, 19% GAMA, 19% NetLogo, 18% Cormas, 3% Julia\n")

sink(file.path(O,"dtw_report.txt"))
compo(kmD$cluster,"DTW hybrid (dtw_basic hierarchical -> k-means refinement), no-reinfection excluded")
sink()
