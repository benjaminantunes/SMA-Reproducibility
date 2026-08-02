#!/usr/bin/env Rscript
# Student implementations: multiple independent developers within the SAME technology
# (5 C++ teams, 5 Java teams). Tests whether developers alone (same language) induce
# statistically different results. Stays modest: this shows a developer effect; it does
# NOT isolate a technology effect.
suppressMessages({library(data.table); library(rstatix); library(ggplot2)})
set.seed(123)
BASE <- normalizePath(getwd())
O <- file.path(BASE,"results"); dir.create(O, showWarnings=FALSE)
PEAKWIN <- 0:149

e<-new.env(); load(file.path(BASE,"data/student-data/df_etudiants.RData"),envir=e)
df<-as.data.table(get("df_etudiants",envir=e))
df[, lang := ifelse(grepl("^CPP", Langage), "C++", "Java")]
# relabel teams with consecutive numbers per language (Java teams were 1,2,4,5,7)
remap <- c(CPP1="C++ 1",CPP2="C++ 2",CPP3="C++ 3",CPP4="C++ 4",CPP5="C++ 5",
           Java1="Java 1",Java2="Java 2",Java4="Java 3",Java5="Java 4",Java7="Java 5")
df[, team := remap[Langage]]

pk <- df[step %in% PEAKWIN, .(peak=max(I), day=step[which.max(I)]), by=.(lang,team,simu)]
pk[, peak_pct := peak*100]   # percent of population (student pop sizes/inits vary; use proportion)

## summary per team
summ <- pk[, .(n=.N, peak_mean=round(mean(peak_pct),2), peak_sd=round(sd(peak_pct),2),
               day_mean=round(mean(day),1), day_sd=round(sd(day),1)), by=.(lang,team)][order(lang,team)]
cat("=== Per-team first-peak (amplitude as % of population) ===\n"); print(summ)

## within-technology developer effect
report <- function(sub, tag){
  a <- sub %>% anova_test(peak_pct ~ team)
  es <- sub %>% anova_test(peak_pct ~ team) %>% get_anova_table()
  eta <- (sub %>% anova_test(peak_pct ~ team))$ges          # generalized eta2
  kw <- sub %>% kruskal_test(day ~ team)
  eps <- (sub %>% kruskal_effsize(day ~ team))$effsize
  cat(sprintf("\n[%s] amplitude ANOVA: F(%d,%d)=%.1f, p=%.2g, eta2(ges)=%.3f | timing KW: H=%.1f, p=%.2g, eps2=%.3f\n",
      tag, a$DFn, a$DFd, a$F, a$p, eta, kw$statistic, kw$p, eps))
  invisible(list(a=a,eta=eta,kw=kw,eps=eps))
}
rc <- report(pk[lang=="C++"], "C++ (5 teams)")
rj <- report(pk[lang=="Java"], "Java (5 teams)")

## figure: boxplots per team, coloured by language
pk$team <- factor(pk$team, levels=summ$team)
pk[, team_short := sub("^(C\\+\\+|Java) ", "", team)]  # short x labels within each panel
p <- ggplot(pk, aes(team_short, peak_pct, fill=lang)) +
  geom_boxplot(outlier.size=0.4, show.legend=FALSE) +
  facet_wrap(~lang, scales="free_x") +
  scale_fill_manual(values=c("C++"="#4477AA","Java"="#EE6677")) +
  labs(x="Developer team", y="First-peak amplitude (% of population)") +
  theme_bw(base_size=12) + theme(strip.text=element_text(face="bold"))
ggsave(file.path(BASE,"figures/fig6_students.png"), p, width=8, height=4.2, dpi=150)

fwrite(summ, file.path(O,"students_summary.csv"))
sink(file.path(O,"students_report.txt"))
cat("Per-team first-peak (amplitude % of population):\n"); print(summ)
cat("\nWithin-technology developer effect:\n")
rc<-report(pk[lang=="C++"],"C++ (5 teams)"); rj<-report(pk[lang=="Java"],"Java (5 teams)")
sink()
cat("\nFigure -> figures/fig6_students.png ; outputs -> results/\n")
