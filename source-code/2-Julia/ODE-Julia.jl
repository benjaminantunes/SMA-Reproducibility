using DifferentialEquations
# Initial conditions
u0 = [0.999, 0.0, 0.001, 0.0]
# Parameters values
p = [1/365, 0.5, 1/3, 1/7]
tspan = (0.0, 730.0)
function seirs!(du,u,p,t)
   du[1] = p[1] * u[4] - p[2] * u[3] * u[1]
   du[2] = p[2] * u[3] * u[1] - p[3] * u[2] 
   du[3] = p[3] * u[2] - p[4] * u[3]
   du[4] = p[4] * u[3] - p[1] * u[4]
end


prob = ODEProblem(seirs!,u0,tspan,p)
algo = Tsit5()
sol = solve(prob, algo, saveat = 1)

using SplitApplyCombine # here for vector of vector transposition
inv = invert(sol.u)

df = DataFrame(time=sol.t, S=inv[1], E=inv[2], I=inv[3], R=inv[4])

CSV.write("data-EDO-Julia.csv", df)


