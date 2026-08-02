# Python
import getopt
import random as rand
import os
import sys
import time as tm

# Current app
from config import *
from model.seir_world import *
from monitor import *


def print_help():
	print()
	print("*** Help page ***")
	print()
	print("Run without arguments to launch GUI")
	print("If running in command mode, paramter \"output_file\" is required.")
	print()
	print("* available command-line options: *")
	print()
	print("Short commands")
	print("  -h:             display help (the current text)")
	print("  -d:             run in command line with default arguments")
	print("  -f:             force write to output file even if the file already exists")
	print()
	print("Long commands: set value using \"--<command>=<value>\"")
	print("  output_file:    (MANDATORY) path to the output file")
	print("  width:          set the width of the world. Default value: " + str(DEFAULT_WIDHT))
	print("  height:         set the height of the world. Default value: " + str(DEFAULT_HEIGHT))
	print("  agents:         set the number of agents. Default value: " + str(DEFAULT_AGENT_COUNT))
	print("  infected_ratio: set the initial ratio of infected agents. Default value: " + str(DEFAULT_AGENT_INFECTED_RATIO))
	print("  incubation:     set the incubation period in days. Default value: " + str(DEFAULT_DURATION_INCUBATION))
	print("  infectious:     set the infectious period in days. Default value: " + str(DEFAULT_DURATION_INFECTIOUS))
	print("  immune:         set the immune period in days. Default value: " + str(DEFAULT_DURATION_IMMUNE))
	print("  transmission:   set the transmission rate in %. Default value: " + str(DEFAULT_TRANSMISSION_RATE))
	print("  duration:       set the simulation duration in days. Default value: " + str(DEFAULT_SIMULATION_DURATION))
	print("  seed:           set the simulation seed for random. Do not set this option to base seed on current time.")

def execute_command_line(args):

	display_help   = False
	width          = DEFAULT_WIDHT
	height         = DEFAULT_HEIGHT
	agents         = DEFAULT_AGENT_COUNT
	infected_ratio = DEFAULT_AGENT_INFECTED_RATIO
	incubation     = DEFAULT_DURATION_INCUBATION
	infectious     = DEFAULT_DURATION_INFECTIOUS
	immune         = DEFAULT_DURATION_IMMUNE
	transmission   = DEFAULT_TRANSMISSION_RATE*100
	duration       = DEFAULT_SIMULATION_DURATION
	seed           = None
	output_file    = None
	force_write    = False

	try:
		options = "hdf"
		long_options = ["output_file=", \
						"width=", \
						"height=", \
						"agents=", \
						"infected_ratio=", \
						"incubation=", \
						"infectious=", \
						"immune=", \
						"transmission=", \
						"duration=", \
						"seed="]
		arguments, _ = getopt.getopt(args, options, long_options)

		for currentArgument, currentValue in arguments:

			if currentArgument == "-h":
				display_help = True
				break
			if currentArgument == "-d":
				if len(args) > 1:
					raise ValueError("-d option can't be used along with another option")
				break
			if currentArgument == "-f":
				force_write = True
				break
			elif currentArgument == "--output_file":
				output_file = currentValue
			elif currentArgument == "--width":
				width = int(currentValue)
				if width <= 0:
					raise ValueError("Width must be strictly positive")
			elif currentArgument == "--height":
				height = int(currentValue)
				if height <= 0:
					raise ValueError("Height must be strictly positive")
			elif currentArgument == "--agents":
				agents = int(currentValue)
				if agents <= 0:
					raise ValueError("Agents count must be strictly positive")
			elif currentArgument == "--infected_ratio":
				infected_ratio = float(currentValue)
				if infected_ratio < 0 or infected_ratio > 1:
					raise ValueError("Infection ration must be between 0 and 1")
			elif currentArgument == "--incubation":
				incubation = int(currentValue)
				if incubation < 0:
					raise ValueError("Incubation duration must be positive")
			elif currentArgument == "--infectious":
				infectious = int(currentValue)
				if infectious < 0:
					raise ValueError("Infectious duration must be positive")
			elif currentArgument == "--immune":
				immune = int(currentValue)
				if immune < 0:
					raise ValueError("Immune duration must be positive")
			elif currentArgument == "--transmission":
				transmission = int(currentValue)
				if transmission <= 0:
					raise ValueError("Transmission rate must be strictly positive")
			elif currentArgument == "--duration":
				duration = int(currentValue)
				if duration <= 0:
					raise ValueError("Simulation duration must be strictly positive")
			elif currentArgument == "--seed":
				seed = currentValue

	except getopt.error as err:
		print("Error!", end = " ")
		print(err)
		display_help = True
	except ValueError as err:
		print("Error!", end = " ")
		print(err)
		display_help = True

	if (output_file == None) and (display_help == False):
		print("Error! No output file provided to store results.")
		display_help = True

	if display_help == True:
		# Help is displayed if requested by the user or
		# there has been an error with the parameters.
		print_help()
	else:
		# If we reach this point, parameters are correctly formed.

		# Chech if provided file is correct
		if force_write == False:
			file_exists = True
			try:
				file = open(output_file, "r")
			except FileNotFoundError:
				file_exists = False

			if file_exists == True:
				sys.exit("Error! File provided to store results already exists.\nRun with parameter -f to allow file overwrite.")

		try:
			file = open(output_file, "w")
		except FileNotFoundError:
			sys.exit("Error! Can't write to output file.")

		file.close()

		# Compute parameters
		infected_agents = int(agents*infected_ratio/100)
		susceptible_agents = agents - infected_agents

		# Display simulation parameters
		print("Running simulator with the following parameters:")
		print("  Output file:         " + os.path.realpath(file.name))
		print("  World size:          " + str(width) + "x" + str(height) + " cells")
		print("  Agents count:        " + str(agents) + " (" + str(susceptible_agents) + " susceptible and " + str(infected_agents) + " infected)")
		print("  Incubation period:   " + str(incubation) + " days")
		print("  Infectious period:   " + str(infectious) + " days")
		print("  Immune period:       " + str(immune) + " days")
		print("  Transmission rate:   " + str(transmission) + "%")
		print("  Simulation duration: " + str(duration) + " days")

		random = rand.Random()
		if seed != None:
			print("  Seed:                " + seed + "")
			random.seed(seed)

		# Build model and simulator
		model = World(width, height, susceptible_agents, infected_agents, incubation, infectious, immune, transmission/100, random)
		simulator = Simulator(model)
		simulator.setDSDEVS(True)

		current_time = simulator.termination_time

		if current_time != INFINITY:
			end_time = current_time + duration
		else:
			current_time = 0
			end_time = duration

		# Build monitor
		agents = susceptible_agents + infected_agents
		monitor = Monitor(agents, model)

		# Proceed to simulation
		start_time = tm.process_time()
		for time in range(int(current_time)+1, int(end_time)+1):
			simulator.setTerminationTime(time)
			simulator.simulate()
			monitor.update_results(simulator.termination_time)
		end_time = tm.process_time()
		print("Done. Simulation took " + str(int(end_time-start_time)) + "s")

		# Export results.
		print("Exporting results to " + output_file)
		file = open(output_file, "w")
		monitor.export_results(file)
		file.close()
