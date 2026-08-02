using StatsBase
using Plots

# Corss-correlation

lag = [0]
cr = crosscor(mat,mat,lag)


p2 = heatmap(
    cr[1,:,:],
    title = "Cross-correlation matrix",
    c = :balance,
    clims = (-1, 1),	
    xticks=(1:length(mat[1,:]), [labels[i] for i in 1:length(labels)]),
    yticks=(1:length(mat[1,:]), [labels[i] for i in 1:length(labels)])
    )

