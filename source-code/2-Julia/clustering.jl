#############
# Clustrering
#############

using Clustering
using Distances

D = pairwise(Euclidean(), mat, dims=2)
result = hclust(D, linkage=:single, branchorder=:optimal)

labels = []
for i in 1:length(D[:,1])
    if i < 7
       push!(labels, "o")
    elseif i < 37
       push!(labels, "J")
    elseif i < 66
       push!(labels, "D")
    elseif i < 96
       push!(labels, "c")
    else
       push!(labels, "n")
    end   
end

#assign = cutree(result, k = 10)

using(StatsPlots)

p1 = plot(
     plot(result, title = "Clustering", xticks=:none),
     heatmap(
         mat[:, result.order],
         title = "Susceptible density",
         colorbar=:none,
         c = :bilbao,
         ylabel = "days",
         xticks=(1:length(result.order), [labels[i] for i in result.order]),
         xlabel = "Samples (o:ODE, d:DSDEVS c:C++ n:Netlogo)"
         ),
     layout=grid(2,1, heights=[0.2,0.8])
    )




