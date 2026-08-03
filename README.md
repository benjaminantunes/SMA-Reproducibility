# SMA-Reproducibility

Reproducibility package for the paper *"Replicability of Agent-Based Simulations: A Case Study
with a SEIRS Epidemiological Model"*.

The study implements one SEIRS agent-based model, specified once with an ODD protocol, on **seven
platforms and languages** (C++, Julia, Python, NetLogo, GAMA, Cormas, PythonPDEVS), each by a
different modeler, and asks whether the independently developed implementations agree. A
complementary set of **student implementations** (5 C++ and 5 Java teams) is used to probe the
developer effect within a single technology.

This repository contains everything needed to reproduce the analysis, figures and statistics of the
paper, plus the source code of every implementation.

## Repository structure

```
SMA-Reproducibility/
├── source-code/            # the seven implementations (source only)
│   ├── 1-Cpp/              # C++ (from scratch)
│   ├── 2-Julia/            # Julia ABM (seirsABM.jl) + ODE reference (ODE-Julia.jl)
│   ├── 3-Python/           # Python / AgentPy notebook
│   ├── 4-NetLogo/          # NetLogo model (model/m2-seir.nlogo)
│   ├── 5-GAMA/             # GAMA model (models/m2-seir.gaml)
│   ├── 6-Cormas/           # Cormas / Pharo (Smalltalk) package
│   ├── 7-PythonPDEVS/      # PythonPDEVS (DEVS) model
│   └── 8-Students/         # 10 student implementations (5 C++, 5 Java) for the developer-effect test
├── data/
│   ├── harmonized/         # df_SMA_serveur_VF.RData  (all runs, one tidy table)
│   ├── reference/          # data-EDO-Julia.csv       (ODE reference trajectory)
│   ├── raw-outputs/        # per-implementation, per-replication CSVs (step,S,E,I,R)
│   └── student-data/       # student implementations (C++ / Java), *.RData
├── analysis/               # R scripts that reproduce the paper (run from repo root)
│   ├── 01_statistics.R     # per-platform summary, ANOVA/Welch/Kruskal, effect sizes, Tukey + Games-Howell post-hoc
│   ├── 02_clustering.R     # hybrid hierarchical + k-means (Euclidean, k=8); reproduces the Table 5 contingency
│   ├── 03_dtw.R            # hybrid DTW clustering (dtw_basic, no window, k=2); reproduces the published 59/147 split
│   ├── 04_figures.R        # figures 1-3 (ODE, trajectories, boxplots)
│   └── 05_students.R       # student developer-effect analysis + figure
├── ablation/               # controlled C++ ablation of implementation choices
│   ├── seir_ablation.cpp   # fast, flag-driven SEIRS ABM (varies one choice at a time)
│   └── RESULTS.md          # ablation results and interpretation
├── figures/                # generated figures (regenerable)
└── results/                # generated tables and reports (regenerable)
```

Platform-name note: the PythonPDEVS implementation was labelled `DSDEVS` in earlier versions of the
data; it is now labelled `PythonPDEVS` throughout (dataset, scripts, outputs and paper).

## Requirements

**To reproduce the analysis (recommended path):** R (>= 4.0) with the packages

```r
install.packages(c("data.table","ggplot2","effectsize","rstatix","FSA","dtw","dtwclust","dendextend"))
```

The harmonized dataset and the raw outputs are provided, so the full analysis reproduces **without
re-running any simulation**.

**To re-run the simulations from source (optional):** each implementation needs its own runtime:
C++ (`g++`), Julia, Python 3 + `agentpy`, NetLogo, GAMA, Cormas (Pharo), and PythonPDEVS. See the
README inside each `source-code/` folder.

## How to reproduce the analysis

From the repository root:

```bash
Rscript analysis/01_statistics.R    # -> results/summary_table.csv, stats_report.txt, ...
Rscript analysis/02_clustering.R    # Euclidean hybrid clustering (reproduces the 8 clusters)
Rscript analysis/03_dtw.R           # DTW clustering (2 clusters)
Rscript analysis/04_figures.R       # -> figures/fig1..fig3
Rscript analysis/05_students.R      # -> figures/fig6_students.png, results/students_*.txt
```

`01_statistics.R` writes `results/peaks_per_rep.csv`, which `04_figures.R` uses, so run 01 before 04.

## Main results (for a quick check)

- First-peak amplitude differs strongly across implementations: one-way ANOVA
  `F(6, 203) = 1690.7`, `p < 2.2e-16`, `eta^2 = 0.98`; mean amplitude ranges from 6\,514 (Cormas)
  to 8\,200 (Julia) infected out of 20\,000. Timing: Kruskal-Wallis `H = 177.0`, `eps^2 = 0.84`.
- Euclidean clustering yields 8 clusters, each dominated by one technology (C++ and Julia each form
  their own cluster; Cormas and PythonPDEVS carry the runs without reinfection).
- Student data: within a single language, different developers still diverge strongly (C++
  `eta^2 = 0.997`, Java `eta^2 = 0.994`), showing a large developer effect.

## Ablation (why the implementations diverge)

`ablation/` contains a fast, flag-driven C++ SEIRS model that varies one implementation choice at a
time (residence-time rounding, transition test, within-step order, synchronous vs asynchronous
update) while keeping everything else fixed. Its baseline reproduces the original C++ result
(7,802 vs 7,795 infected). Build and run:

```bash
cd ablation
g++ -O2 -o seir_ablation seir_ablation.cpp
./seir_ablation floor infect_move gt fixed 30 1 sync    # baseline
./seir_ablation round infect_move gt fixed 30 1 sync    # round durations
./seir_ablation floor infect_move ge fixed 30 1 sync    # >= transition test
./seir_ablation floor infect_move gt fixed 30 1 async   # asynchronous update
```

Flags: `rounding {floor|round|ceil|cont}`, `order {infect_move|move_infect}`, `thresh {gt|ge}`,
`redraw {fixed|redraw}`, `nreps`, `seed0`, `update {sync|async}`. Full results and interpretation
are in `ablation/RESULTS.md`.

## Data dictionary

Each raw-output CSV has columns `step, S, E, I, R` (proportions of the population, 731 rows,
steps 0..730). The harmonized `df_SMA_serveur_VF.RData` holds one long `data.table` with columns
`step, S, E, I, R, simu, Langage` for every replication of every implementation.
