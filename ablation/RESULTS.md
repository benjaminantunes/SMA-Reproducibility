# C++ ablation: which implementation choices drive the first-peak divergence?

**Status: exploratory analysis only. Nothing here is written into the paper yet.**

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

## Interpretation
- **The divergence is driven almost entirely by how each implementation turns the continuous
  exponential residence times into a whole number of simulated days.** The rounding rule and the
  strict-vs-non-strict transition test together set the *effective* number of days an agent spends
  infectious; that single mechanism spans 7009–8467, i.e. about **87% of the 1,686-individual gap**
  observed across the seven platforms (Cormas 6,514 to Julia 8,200).
- Note the interaction: continuous durations with `>` are identical to floor with `>`, and ceil with
  `>=` equals floor with `>` — because the day counter is an integer, only the *effective* integer
  duration matters, not the rounding rule in isolation.
- **Within-step order (infect-then-move vs move-then-infect) and redrawing residence times on
  re-entry are negligible for the first peak** (Δ < 10 infected). Redraw was expected to be small,
  since re-infection mostly happens after the first wave.
- The baseline (floor, `>`) reproduces C++ exactly (7802 ≈ 7795). The ablation explains the dominant
  axis; residual per-platform differences not captured here (e.g. GAMA discretising the infection
  probability, NetLogo using a Euclidean-radius neighbourhood, Cormas's move-then-infect combined
  with its `>=` threshold, and the no-reinfection runs) account for the remainder of the spread.

## Takeaway for the paper (if we later choose to use it)
An ODD that leaves the residence-time discretisation and the transition test unspecified permits a
~1,500-individual (≈19%) difference in peak amplitude between conforming implementations. Pinning
down these two decision points would remove most of the divergence. This converts the finding from
"implementations diverge" into "here are the specific decision points an ODD must fix."

Reproduce: `g++ -O2 -o seir_ablation seir_ablation.cpp` then e.g.
`./seir_ablation ceil infect_move gt fixed 30 1`.

## Follow-up: is the C++/Julia residual (405) a technology effect?

C++ and Julia agree on every axis in Table 7 (Moore-8+own, discrete step, infect-then-move, floor,
strict `>`) yet differ by 405 infected (7,795 vs 8,200) and 4 days. Inspecting the Julia source
(`MAS-Repro-main/seirsABM.jl`) reveals a factor not in Table 7: Julia uses `Schedulers.Randomly()`
with an in-place `agent_step!`, i.e. **asynchronous** updates (agents processed in random order,
state changes visible within the same step), whereas the hand-written C++ is **synchronous**
(double-buffered start-of-step snapshot). Asynchronous updates let infection chain within a step.

Ablation (new `sync|async` flag, 30 reps):

| Update semantics | peak amplitude | peak day |
|---|---|---|
| synchronous (C++ style) | 7802 ± 69 | 37.4 |
| asynchronous (Julia/Agents.jl style) | 8081 ± 75 | 35.0 |

Switching sync→async raises the peak by **+279** and moves it ~2.4 days earlier, accounting for
about two-thirds of the observed C++/Julia gap (405 amplitude, 4 days). The remainder (~126) is
plausibly the different PRNG (Julia Xoshiro vs C++ Mersenne Twister) and initial-condition details
(`add_agent_single!`; the `mod[1].status=3` loop seeds one infectious agent, not 20).

**Interpretation.** The dominant part of the C++/Julia residual is the synchronous-vs-asynchronous
update. This is precisely where technology and modeler blur: Agents.jl's idiomatic/default execution
model is asynchronous, random-order, in-place updating, whereas a hand-written C++ model naturally
uses an explicit synchronous double buffer. The modeler followed each tool's natural pattern, so the
difference is imposed largely by the **framework's default execution model** — a genuine technology
effect. It is a concrete, quantified example of the technology/modeler confound the paper is about:
even holding the identifiable modelling choices fixed, the technology silently supplies a further
choice (the scheduler/update semantics) that changes the numbers.
