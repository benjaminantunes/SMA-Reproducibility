#
# Read simulation results files and build the time series matrix
#

using CSV
using DataFrames

# Results from ODE solvers
solver_names = [
               "sim-results/ODE/data-EDO-Julia.csv"
               "sim-results/ODE/Scipy_RK45_step1.0.csv"
               "sim-results/ODE/Scipy_LSODA_step1.0.csv"
               "sim-results/ODE/Odespy_RK4_step1.0.csv"
               "sim-results/ODE/Odespy_ForwardEuler_step1.0.csv"
               "sim-results/ODE/Odespy_AdamsBashMoulton2_step1.0.csv"
               ]
df = []
labels = []
for name in solver_names
    push!(df, CSV.read(name, DataFrame))
    push!(labels, "e")
end

# Results from Julia SMA
for i in 1:30
        filename = string("sim-results/JuliaSMA/", string(i, pad = 3), ".csv")
        push!(df, CSV.read(filename, DataFrame, header=true))
        push!(labels, "j")
end

# Results from DSDEVS

for i in 1:30
    if i != 3 # !!!! File 003.csv is empty !!!!
        filename = string("sim-results/DSDEVS-results/", string(i, pad = 3), ".csv")
        push!(df, CSV.read(filename, DataFrame, header=false))
        rename!(df[length(df)], "Column1" => "S", "Column2" => "E", "Column3" => "I", "Column4" => "R")
        push!(labels, "d")
    end
end

# Results from SMA C++
for i in 1:30
    filename = string("sim-results/SMA_C++/ResultatRepli", string(i-1), ".csv")
    push!(df, CSV.read(filename, DataFrame, header=false))
    rename!(df[length(df)], "Column1" => "S", "Column2" => "E", "Column3" => "I", "Column4" => "R")
    pushfirst!(df[length(df)], [0.999 0.0 0.001 0])
    push!(labels, "c")
end

# Results from Netlogo
for i in 1:30
    filename = string("sim-results/Netlogo/result", string(i), ".csv")
    push!(df, CSV.read(filename, DataFrame, header=false))
    rename!(df[length(df)], "Column1" => "S", "Column2" => "E", "Column3" => "I", "Column4" => "R")
    push!(labels, "n")
end

# Create Matrix 'mat' containing time series for S or I
global mat = df[1].I
for i in 2:length(df)
    global mat = hcat(mat,df[i].I)
end


