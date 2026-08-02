using Random, Distributions # for reproducibility
using Agents
using InteractiveDynamics
#using CairoMakie	


@agent Individual GridAgent{2} begin
    status::Int64 # (1,2,3,4) = (S, E, I, R)
    t_in_status::Int64
    lifespan_E::Int64
    lifespan_I::Int64
    lifespan_R::Int64
end

total_agents = 20000
seed = 11290177
prng = Random.Xoshiro(seed)

function initialize(; griddims = (300, 300))
    space = GridSpace(griddims, metric = :chebyshev)	
    
    mod = UnkillableABM(
        Individual, space;
        rng = prng, scheduler = Schedulers.Randomly()
    )
    # populate the model with agents
    # at random positions in the model
    for n in 1:total_agents
        agent = Individual(n, (1, 1),
                           1, 0,
                           floor(Int, rand(prng, Exponential(3.))),
                           floor(Int, rand(prng, Exponential(7.))),
                           floor(Int, rand(prng, Exponential(365.)))
                           )
        #add_agent!(agent, mod)
        add_agent_single!(agent, mod)
    end
    for i in 1:20
        mod[1].status = 3
    end
    return mod
end

function infect!(agent, model)
    i_neighbors = 0
    # Here `nearby_agents` (with default arguments) will provide an iterator
    # over the nearby agents one grid point away, which are at most 8.
    for neighbor in nearby_agents(agent, model)
        if neighbor.status == 3
            i_neighbors += 1
        end
    end
    if i_neighbors > 0 && rand(prng) > exp(-0.5*i_neighbors)
        agent.status = 2
        agent.t_in_status = 0
    end
end

function infection!(agent, model)
    if agent.status == 1
        infect!(agent, model)
    elseif agent.status == 2 && agent.t_in_status > agent.lifespan_E
           agent.status = 3
           agent.t_in_status = 0
    elseif agent.status == 3 && agent.t_in_status > agent.lifespan_I
           agent.status = 4
           agent.t_in_status = 0
    elseif agent.t_in_status > agent.lifespan_R
           agent.status = 1
           agent.t_in_status = 0
    else
        agent.t_in_status += 1
    end
    return
end

function move!(model)
    # Move the agent.
    for agent in allagents(model)
        move_agent!(agent, model)
        #move_agent_single!(agent, model)
        #randomwalk!(agent, model, 1)
    end
    return
end

# Function to assign colors regarding agents status (using CairoMakie)
groupcolor(a) = a.status == 1 ? "#338c54" : a.status == 2 ? "#ffa500" : a.status == 3 ? "#bf2642" : "#2b2b33"

#step!(model, agent_step!, 4)
#figure, _ = abmplot(model; ac = groupcolor, as = 10)
#figure


x1(agent) = agent.status == 1 ? 1 : 0
x2(agent) = agent.status == 2 ? 1 : 0
x3(agent) = agent.status == 3 ? 1 : 0
x4(agent) = agent.status == 4 ? 1 : 0

adata = [(x1, sum), (x2, sum), (x3, sum), (x4, sum)]
alabels = ["S", "E", "I", "R"]

#using CSV
#using DataFrames

#for i in 1:30
#    m = initialize()
#    data, _ = run!(m, infection!, move!, 730; adata)
#    rename!(data, "sum_x1" => "S", "sum_x2" => "E", "sum_x3" => "I", "sum_x4" => "R")
#    data.S /= total_agents
#    data.E /= total_agents
#    data.I /= total_agents
#    data.R /= total_agents
#    CSV.write(string("JuliaSMA/", string(i, pad = 3), ".csv"), data)
#end

model = initialize()

using GLMakie	
figure, abmobs = abmexploration(
    model;
    agent_step! = infection!, model_step! = move!, dummystep, ac = groupcolor, as = 5,
    adata, alabels
)







