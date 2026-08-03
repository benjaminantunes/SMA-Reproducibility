#!/usr/bin/env Rscript
# Canonical analysis on the ORIGINAL harmonized dataset (reproduces the paper, then
# adds the reviewer-requested statistics). Netlogo = Dorian (published choice).
suppressMessages({library(data.table); library(effectsize); library(rstatix); library(FSA); library(dtw)})
set.seed(123)
BASE <- normalizePath(getwd())
O <- file.path(BASE,"results"); dir.create(O, showWarnings=FALSE)
N_AGENTS <- 20000; PEAKWIN <- 0:149

e<-new.env(); load(file.path(BASE,"data/harmonized/df_SMA_serveur_VF.RData"),envir=e)
df<-as.data.table(get("df",envir=e))
df<-df[!Langage %in% c("Netlogo Etienne","Netlogo Hanae")]
df[Langage=="Netlogo Dorian", Langage:="Netlogo"]
df[, platform:=factor(Langage, levels=c("C++","Cormas","GAMA","Julia","Netlogo","DSDEVS","Python"))]

# ---- per-rep first peak & no-reinfection ----
rows <- df[step %in% PEAKWIN, .(peak_frac=max(I), peak_day=step[which.max(I)]), by=.(platform,simu)]
rows[, peak_count:=peak_frac*N_AGENTS]
lateI <- df[step>=400, .(lateI=mean(I)), by=.(platform,simu)]
rows <- merge(rows, lateI, by=c("platform","simu"))
rows[, noreinf:=lateI<1e-4]

ci<-function(x){m<-mean(x);er<-qt(.975,length(x)-1)*sd(x)/sqrt(length(x));c(m,m-er,m+er)}
summ <- rows[, {a<-ci(peak_count);t<-ci(peak_day);
  .(n=.N, peak_mean=round(a[1]), peak_median=round(median(peak_count)), peak_sd=round(sd(peak_count)),
    peak_CI=sprintf("[%d, %d]",round(a[2]),round(a[3])),
    day_mean=round(t[1],1), day_median=median(peak_day), day_sd=round(sd(peak_day),1),
    day_CI=sprintf("[%.1f, %.1f]",t[2],t[3]), n_noreinf=sum(noreinf))}, by=platform]

# ---- amplitude: assumptions, tests, effect size, post-hoc ----
fit<-aov(peak_count~platform,data=rows); an<-summary(fit)[[1]]
SSb<-an["platform","Sum Sq"];SSw<-an["Residuals","Sum Sq"];dfb<-an["platform","Df"];MSw<-an["Residuals","Mean Sq"]
eta2<-SSb/(SSb+SSw); omega2<-(SSb-dfb*MSw)/(SSb+SSw+MSw)
shap<-shapiro.test(residuals(fit)); lev<-car::leveneTest(peak_count~platform,data=rows,center=mean)
welch<-oneway.test(peak_count~platform,data=rows,var.equal=FALSE)
kw_amp<-kruskal.test(peak_count~platform,data=rows)
gh<-rows %>% games_howell_test(peak_count~platform)
tuk<-as.data.table(TukeyHSD(fit)$platform,keep.rownames="pair")   # primary post-hoc (assumptions hold)
grp_sd<-tapply(rows$peak_count,rows$platform,sd)

# ---- timing ----
kw<-kruskal.test(peak_day~platform,data=rows); eps<-rows %>% kruskal_effsize(peak_day~platform)
dunn<-dunnTest(peak_day~platform,data=rows,method="bh")$res

# ---- distance to Julia ODE reference ----
ref<-fread(file.path(BASE,"data/reference/data-EDO-Julia.csv"))
refI<-ref[[4]][1:731]
distref <- rows[0]; distref<-df[, .(mu=mean(I)), by=.(platform,step)][
  , .(RMSE=round(sqrt(mean((mu-refI[step+1])^2)),4),
      DTW=round(dtw(mu, refI[1:.N], distance.only=TRUE)$normalizedDistance,4)), by=platform]

# Clustering (Euclidean hybrid and DTW hybrid) is computed in 02_clustering.R and 03_dtw.R.

# ---- write ----
fwrite(summ, file.path(O,"summary_table.csv")); fwrite(rows, file.path(O,"peaks_per_rep.csv"))
fwrite(distref, file.path(O,"distance_to_reference.csv")); fwrite(gh, file.path(O,"gameshowell_amplitude.csv"))
fwrite(tuk, file.path(O,"tukey_amplitude.csv")); fwrite(dunn, file.path(O,"dunn_timing.csv"))
sink(file.path(O,"stats_report.txt"))
cat("=== PER-PLATFORM SUMMARY (peak = infected count /20000) ===\n"); print(summ)
cat("\n=== AMPLITUDE ===\n"); print(an)
cat(sprintf("eta^2=%.3f omega^2=%.3f\n",eta2,omega2))
cat("group SDs:\n"); print(round(grp_sd))
cat(sprintf("Shapiro W=%.3f p=%.3g ; Levene(mean) F=%.2f p=%.3g\n",shap$statistic,shap$p.value,lev$`F value`[1],lev$`Pr(>F)`[1]))
cat(sprintf("Welch ANOVA F=%.1f df1=%d df2=%.1f p=%.3g ; Kruskal(amp) H=%.1f p=%.3g\n",
  welch$statistic,welch$parameter[1],welch$parameter[2],welch$p.value,kw_amp$statistic,kw_amp$p.value))
cat(sprintf("Games-Howell significant pairs: %d of %d\n", sum(gh$p.adj<0.05), nrow(gh)))
cat(sprintf("Tukey HSD significant pairs: %d of %d (non-sig: %s)\n", sum(tuk$`p adj`<0.05), nrow(tuk),
  paste(tuk[`p adj`>=0.05, pair], collapse="; ")))
cat("\n=== TIMING ===\n"); cat(sprintf("Kruskal H=%.1f df=%d p=%.3g ; epsilon^2=%.3f\n",kw$statistic,kw$parameter,kw$p.value,eps$effsize))
cat("\n=== DISTANCE TO ODE REFERENCE ===\n"); print(distref)
sink()
writeLines(readLines(file.path(O,"stats_report.txt")))
cat("\nOutputs -> results/\n")
