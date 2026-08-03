#!/usr/bin/env Rscript
# Regenerate publication figures from the ORIGINAL dataset (Reviewer #4 3.8):
# labelled S/E/I/R ODE plot, de-cluttered infected trajectories (counts), annotated
# boxplots, and dendrograms with readable platform membership.
suppressMessages({library(data.table); library(ggplot2); library(dendextend)})
set.seed(123)
BASE <- normalizePath(getwd())
IMG  <- file.path(BASE,"figures"); dir.create(IMG, showWarnings=FALSE)
HARM <- file.path(BASE,"data/harmonized"); REF <- file.path(BASE,"data/reference")
N <- 20000
plats <- c("C++","Cormas","GAMA","Julia","NetLogo","PythonPDEVS","Python")
pal <- c("C++"="#4477AA","Cormas"="#EE6677","GAMA"="#228833","Julia"="#CCBB44",
         "NetLogo"="#66CCEE","PythonPDEVS"="#AA3377","Python"="#777777")
code <- c("C++"="Cpp","Cormas"="Cor","GAMA"="GAM","Julia"="Jul","NetLogo"="Net",
          "PythonPDEVS"="PDE","Python"="Pyt")

e<-new.env(); load(file.path(HARM,"df_SMA_serveur_VF.RData"),envir=e); df<-as.data.table(get("df",envir=e))
df<-df[!Langage %in% c("Netlogo Etienne","Netlogo Hanae")]
df[Langage=="Netlogo Dorian",Langage:="NetLogo"]
df[, platform:=factor(Langage, levels=plats)]
stopifnot(!any(is.na(df$platform)))

## ---- Fig 1: ODE reference with S/E/I/R labels ----
ode <- fread(file.path(REF,"data-EDO-Julia.csv")); setnames(ode, c("time","S","E","I","R"))
odeL <- melt(ode, id.vars="time", variable.name="Compartment", value.name="proportion")
odeL$Compartment <- factor(odeL$Compartment, levels=c("S","E","I","R"))
p1 <- ggplot(odeL, aes(time, proportion, colour=Compartment)) + geom_line(linewidth=0.8) +
  scale_colour_manual(values=c(S="#4477AA",E="#CCBB44",I="#EE6677",R="#228833")) +
  labs(x="Time (days)", y="Proportion of the population", colour="Compartment") +
  theme_classic(base_size=13) + theme(legend.position="top")
ggsave(file.path(IMG,"fig1_ode_SEIR.png"), p1, width=8, height=4.5, dpi=150)

## ---- Fig 2: mean infected COUNT per platform, full + zoom ----
traj <- df[, .(meanI=mean(I)*N), by=.(platform,step)]
traj_full <- copy(traj)[, panel:="Full run (0-730 days)"]
traj_zoom <- traj[step<=100][, panel:="Zoom on the first peak (0-100 days)"]
tt <- rbind(traj_full, traj_zoom)
p2 <- ggplot(tt, aes(step, meanI, colour=platform)) + geom_line(linewidth=0.7) +
  facet_wrap(~panel, scales="free") + scale_colour_manual(values=pal) +
  labs(x="Time (days)", y="Number of infected individuals", colour="Platform") +
  theme_classic(base_size=12) + theme(legend.position="top")
ggsave(file.path(IMG,"fig2_infected_by_platform.png"), p2, width=10, height=4.5, dpi=150)

## ---- Fig 3: annotated boxplots (peak amplitude and timing) ----
pk <- fread(file.path(BASE,"results/peaks_per_rep.csv"))
pk[platform=="Netlogo", platform:="NetLogo"]
pk$platform <- factor(pk$platform, levels=plats)
stopifnot(!any(is.na(pk$platform)))
p3a <- ggplot(pk, aes(platform, peak_count, fill=platform)) + geom_boxplot(show.legend=FALSE) +
  scale_fill_manual(values=pal) + labs(x=NULL, y="First-peak amplitude (infected /20000)",
  subtitle=expression(paste("ANOVA F(6,203)=1690.7, p<2.2e-16, ", eta^2, "=0.98"))) +
  theme_classic(base_size=12) + theme(axis.text.x=element_text(angle=30,hjust=1))
p3b <- ggplot(pk, aes(platform, peak_day, fill=platform)) + geom_boxplot(show.legend=FALSE) +
  scale_fill_manual(values=pal) + labs(x=NULL, y="First-peak day",
  subtitle=expression(paste("Kruskal-Wallis H=177.0, p=1.5e-35, ", epsilon^2, "=0.84"))) +
  theme_classic(base_size=12) + theme(axis.text.x=element_text(angle=30,hjust=1))
ggsave(file.path(IMG,"fig3a_boxplot_amplitude.png"), p3a, width=6.5, height=4.2, dpi=150)
ggsave(file.path(IMG,"fig3b_boxplot_timing.png"), p3b, width=6.5, height=4.2, dpi=150)

## Dendrogram figures removed from the manuscript (kept only as text cluster
## descriptions), so they are no longer generated here.

cat("Figures written to figures/:\n"); print(list.files(IMG, pattern="^fig"))
