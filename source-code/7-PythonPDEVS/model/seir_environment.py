# PyPDEVS
from pypdevs.simulator import Simulator
from pypdevs.DEVS import AtomicDEVS, CoupledDEVS


class Environment(AtomicDEVS):
	def __init__(self):
		AtomicDEVS.__init__(self, "Environment")

		self.state = {}
		self.state["Phase"] = "Move"
		self.state["Update connections"] = False

		self.outports = {}
		self.outports["Instructions"] = self.addOutPort("Instruction output")

	def timeAdvance(self):
		if self.state["Phase"] == "Move":
			return 0
		elif self.state["Phase"] == "Update":
			return 0
		elif self.state["Phase"] == "Infect":
			return 0
		elif self.state["Phase"] == "Wait":
			return 1

	def outputFnc(self):
		if self.state["Phase"] == "Move":
			return { self.outports["Instructions"]: ["Move"]}
		if self.state["Phase"] == "Infect":
			return { self.outports["Instructions"]: ["Infect"]}
		else:
			return {}

	def intTransition(self):
		self.state["Update connections"] = False

		if self.state["Phase"]  == "Move":
			self.state["Phase"] = "Update"
		elif self.state["Phase"] == "Update":
			self.state["Update connections"] = True
			self.state["Phase"] = "Infect"
		elif self.state["Phase"]  == "Infect":
			self.state["Phase"] = "Wait"
		elif self.state["Phase"] == "Wait":
			self.state["Phase"] = "Move"

		return self.state

	def modelTransition(self, state):
		# This method instructs the world that agents connections have to be updated
		return self.state["Update connections"]
