# PyPDEVS
from pypdevs.simulator import Simulator
from pypdevs.DEVS import AtomicDEVS, CoupledDEVS
from pypdevs.infinity import INFINITY

import numpy as np

class Agent(AtomicDEVS):
	def __init__(self, initial_status, initial_position, grid_width, grid_height, incubation_duration, infectious_duration, immune_duration, transmmission_rate, random):
		AtomicDEVS.__init__(self, "Agent")

		# Constants
		self.rand = random

		self.INCUBATION_PERIOD = self.rand.expovariate(1/incubation_duration)
		self.INFECTIOUS_PERIOD = self.rand.expovariate(1/infectious_duration)
		self.IMMUNE_PERIOD     = self.rand.expovariate(1/immune_duration)
		self.TRANSMISSION_RATE = transmmission_rate

		self.GRID_WIDTH  = grid_width
		self.GRID_HEIGHT = grid_height

		self.STEP_ANGLE = np.pi/8

		# Initialize state
		self.state = {}
		self.state["Status"]   = initial_status
		self.state["Position"] = initial_position
		self.state["Phase"]    = "Idle"
		self.state["Time"]     = 0
		if self.state["Status"] == "E":
			self.state["Next time event"] = self.state["Time"] + self.INCUBATION_PERIOD
		elif self.state["Status"] == "I":
			self.state["Next time event"] = self.state["Time"] + self.INFECTIOUS_PERIOD
		elif self.state["Status"] == "R":
			self.state["Next time event"] = self.state["Time"] + self.IMMUNE_PERIOD
		self.state["Infected neighbors"] = 0

		# Create input ports
		self.inports = {}
		self.inports["Infection"] = self.addInPort("Infection input")
		self.inports["Instructions"] = self.addInPort("Instructions input")

		# Create output ports
		self.outports = {}
		self.outports["Infection"] = self.addOutPort("Infection output")

	def timeAdvance(self):
		if self.state["Phase"] == "Infect":
			return 0
		elif self.state["Phase"] == "Get infected":
			return 0
		else: # Phase is Idle
			if self.state["Status"] == "S":
				return INFINITY
			else:
				return self.state["Next time event"] - self.state["Time"]

	def outputFnc(self):
		if self.state["Phase"] == "Infect":
			return { self.outports["Infection"]: ["Infect!"] }
		else:
			return {}

	def extTransition(self, inputs):
		# Update time
		self.state["Time"] = self.state["Time"] + self.elapsed

		if self.inports["Instructions"] in inputs:
			# Received instruction from environment
			if inputs[self.inports["Instructions"]][0] == "Move":
				self.move()
			elif inputs[self.inports["Instructions"]][0] == "Infect":
				if self.state["Status"] == "I":
					self.state["Phase"] = "Infect"
		else:
			# Received a message on an infection port
			if self.state["Status"] == "S":
				for input in inputs:
					for value in inputs[input]:
						if value == "Infect!":
							self.state["Phase"] = "Get infected"
							self.state["Infected neighbors"] = self.state["Infected neighbors"] + 1

		return self.state

	def intTransition(self):
		# Update time
		self.state["Time"] = self.state["Time"] + self.timeAdvance()

		if self.state["Phase"] == "Infect":
			self.state["Phase"] = "Idle"
		elif self.state["Phase"] == "Get infected":
			transmission_probability = 1 - np.exp(-self.TRANSMISSION_RATE * self.state["Infected neighbors"])
			transmitted = self.rand.random()
			if transmitted < transmission_probability:
				self.state["Status"] = "E"
				self.state["Next time event"] = self.state["Time"] + self.INCUBATION_PERIOD
			self.state["Infected neighbors"] = 0
			self.state["Phase"] = "Idle"
		else:
			if self.state["Status"] == "E":
				self.state["Status"] = "I"
				self.state["Next time event"] = self.state["Time"] + self.INFECTIOUS_PERIOD
			elif self.state["Status"] == "I":
				self.state["Status"] = "R"
				self.state["Next time event"] = self.state["Time"] + self.IMMUNE_PERIOD
			elif self.state["Status"] == "R":
				self.state["Status"] = "S"

		return self.state

	def move(self):
		"""
		This function is called once a day to move the agent
		to a new random position on the grid.
		"""

		xf = self.rand.randint(0, self.GRID_WIDTH-1)
		yf = self.rand.randint(0, self.GRID_HEIGHT-1)

		self.state["Position"] = (xf, yf)
