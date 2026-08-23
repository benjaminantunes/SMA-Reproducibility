# C++ ablation: which implementation choices drive the first-peak divergence?

**Status: these results are reported in the paper (Table 8 and the surrounding discussion).**

## Method
A fast, grid-binned C++ SEIRS ABM (`seir_ablation.cpp`) faithful to the original C++ implementation
(20000 agents, 300x300 toroidal grid, 20 initially infected, beta=0.5, exponential residence times
mean 3/7/365, Moore neighbourhood incl. own cell, p = 1 - exp(-beta*N_I), daily random relocation,
730 steps). One modelling choice is varied at a time via command-line flags. 30 replications each;
first-peak amplitude = max infected in the first 150 days.

**Baseline validation.** The baseline configuration (floor durations, infect-then-move, strict `>`
transition, fixed per-agent durations) gives **peak = 7802 (sd 69) at day 37.4**, matching the
original C++ result in the paper (7795 at day ~38). The fast model is therefore a faithful stand-in.

## Single-factor ablation (baseline = floor / infect-then-move / `>` / fixed = 7802)
| Factor changed | variant | peak | Δ vs baseline | peak day |
|---|---|---|---|---|
| (baseline) | floor, infect-then-move, `>`, fixed | 7802 | 0 | 37.4 |
| residence-time rounding | round (nearest) | 8148 | **+346** | 39.1 |
| residence-time rounding | ceil | 8467 | **+665** | 41.2 |
| residence-time rounding | continuous (no rounding) | 7802 | 0 | 37.4 |
| within-step order | move-then-infect | 7810 | +8 | 37.4 |
| E→I transition test | `>=` instead of `>` | 7009 | **−793** | 34.2 |
| residence times | redraw on each re-entry | 7808 | +6 | 37.9 |

## Combined rounding × threshold (the two factors that matter)
| | `>` (strict) | `>=` |
|---|---|---|
| floor / continuous | 7802 | 7009 |
| round | 8148 | 7397 |
| ceil | 8467 | 7802 |

Minimum = 7009 (floor, `>=`); maximum = 8467 (ceil, `>`); **span = 1458 infected**.


