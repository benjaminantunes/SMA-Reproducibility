# Student implementations (developer-effect analysis)

Ten independent student teams implemented the same SEIRS model from the ODD, five in C++ and five
in Java. These are used in the paper to probe the **developer effect within a single technology**
(analysis: `analysis/05_students.R`).

Source code is organised by language and team:

```
8-Students/
├── C++/   <team>/    (5 teams)
└── Java/  <team>/    (5 teams)
```

Each team's simulation outputs are provided as an `.RData` file in `data/student-data/`, named by
technology and developers, e.g. the team `C++/EvahnLEGAL-NathanMEGUIN` corresponds to
`data/student-data/CPP_EvahnLEGAL_NathanMEGUIN.RData`, and `Java/AymenBENBANI-MaryamMOUSTAGHFIR`
corresponds to `data/student-data/JAVA_AymenBENBANI_MaryamMOUSTAGHFIR.RData`. The combined tidy
table used by the analysis is `data/student-data/df_etudiants.RData` (labels `CPP1..CPP5`,
`Java1..Java5`).

Only source code is kept here; simulation outputs, build artifacts and figures were removed to keep
the repository small (the outputs are the `.RData` files above).
