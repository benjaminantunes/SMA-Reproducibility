# PyPDEVS
from pypdevs.simulator import Simulator
from pypdevs.DEVS import AtomicDEVS, CoupledDEVS

# Current app
from model.seir_agent import *
from model.seir_environment import *


class World(CoupledDEVS):
	def __init__(self, width, height, susceptible_agents, infected_agents, incubation_duration, infectious_duration, immune_duration, transmission_rate, random):
		CoupledDEVS.__init__(self, "World")

		# Constants
		self.GRID_WIDTH = width
		self.GRID_HEIGHT = height

		self.rand = random

		# Build agents
		self.agents = set()

		for _ in range(susceptible_agents):
			x = self.rand.randrange(self.GRID_WIDTH)
			y = self.rand.randrange(self.GRID_HEIGHT)
			self.agents.add(self.addSubModel(Agent("S", (x, y), width, height, incubation_duration, infectious_duration, immune_duration, transmission_rate, random)))

		for _ in range(infected_agents):
			x = self.rand.randrange(self.GRID_WIDTH)
			y = self.rand.randrange(self.GRID_HEIGHT)
			self.agents.add(self.addSubModel(Agent("I", (x, y), width, height, incubation_duration, infectious_duration, immune_duration, transmission_rate, random)))

		# Build environment
		self.environment = self.addSubModel(Environment())

		# Static connections: from environment to agents
		for agent in self.agents:
			self.connectPorts(self.environment.outports["Instructions"], agent.inports["Instructions"])

		# Placeholder for agents connections
		self.connections = set()

	def buildGrid(self):
		grid = [[None for y in range(self.GRID_HEIGHT)] for x in range(self.GRID_WIDTH)]

		for agent in self.agents:
			(x, y) = agent.state["Position"]
			if grid[x][y] == None:
				grid[x][y] = set()
			grid[x][y].add(agent)

		return grid

	def getNeighbours(self, grid, x, y, deltax, deltay):
		if (x + deltax > 0) and \
		   (y + deltay > 0) and \
		   (x + deltax < self.GRID_WIDTH) and \
		   (y + deltay < self.GRID_HEIGHT):
			return grid[x+deltax][y+deltay]
		else:
			return None

	def addAgentsConnection(self, source_port, target_port):
		self.connectPorts(source_port, target_port)
		self.connections.add( (source_port, target_port) )

	def clearAgentsConnections(self):
		for connection in self.connections:
			(source, target) = connection
			self.disconnectPorts(source, target)
		self.connections = set()

	def buildAgentsConnections(self):
		grid = self.buildGrid()

		for agent in self.agents:
			for delta_x in range (-1, 2):
				for delta_y in range (-1, 2):
					neighbours = self.getNeighbours(grid, agent.state["Position"][0], agent.state["Position"][1], delta_x, delta_y)
					if neighbours != None:
						for neighbour in neighbours:
							if neighbour != agent:
								self.addAgentsConnection(agent.outports["Infection"], neighbour.inports["Infection"])

	def modelTransition(self, state):
		# This method is called when the same method in a sub-model returns True

		self.clearAgentsConnections()
		self.buildAgentsConnections()

		# Always returns False, as this is top-level
		return False
