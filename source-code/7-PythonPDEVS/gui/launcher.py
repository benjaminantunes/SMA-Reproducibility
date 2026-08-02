# Python
import random as rand

# Tkinter
from tkinter import *

# Current app
from gui.gui import *
from model.seir_world import *
from config import *


class Launcher():
	def __init__(self):
		"""
		Launcher class allows user to tweak simulation parameters,
		then builds the model, the simulator and the gui matching
		these parameters.
		To use it, one has to build a Launcher object then call
		the run_launcher() function on the object.
		"""

		# Build window
		self.root = Tk()

		# Create variables
		self.verbose_var = IntVar()
		self.random_var  = IntVar()

		# Create visual elements
		## Main frame
		self.main_frame = Frame(self.root)

		## World size frame
		self.size_frame = Frame(self.main_frame, pady=10)
		self.label_size = Label(self.size_frame, text = "World size:")
		self.label_sw   = Label(self.size_frame, text = "Width:")
		self.entry_sw   = Entry(self.size_frame, width = 5)
		self.label_sh   = Label(self.size_frame, text = "Height:")
		self.entry_sh   = Entry(self.size_frame, width = 5)

		## Agents count frame
		self.agents_frame = Frame(self.main_frame, pady=10)
		self.label_agents = Label(self.agents_frame, text = "Agents count:")
		self.label_as     = Label(self.agents_frame, text = "Agents:")
		self.entry_as     = Entry(self.agents_frame, width = 5)
		self.label_ai     = Label(self.agents_frame, text = "Infected:")
		self.entry_ai     = Entry(self.agents_frame, width = 5)
		self.label_ap     = Label(self.agents_frame, text = "%")

		## Duration frame
		self.duration_frame = Frame(self.main_frame, pady=10)
		self.label_duration = Label(self.duration_frame, text = "Durations:")
		self.label_dic      = Label(self.duration_frame, text = "Incubation:")
		self.entry_dic      = Entry(self.duration_frame, width = 5)
		self.label_dif      = Label(self.duration_frame, text = "Infectious:")
		self.entry_dif      = Entry(self.duration_frame, width = 5)
		self.label_dim      = Label(self.duration_frame, text = "Immune:")
		self.entry_dim      = Entry(self.duration_frame, width = 5)

		## Transmission frame
		self.transmission_frame = Frame(self.main_frame, pady=10)
		self.label_transmission = Label(self.transmission_frame, text = "Transmission probability:")
		self.entry_tr           = Entry(self.transmission_frame, width = 5)
		self.label_trp          = Label(self.transmission_frame, text = "%")

		## Seed frame
		self.seed_frame            = Frame(self.main_frame, pady=10)
		self.label_seed            = Label(self.seed_frame, text = "Random seed:")
		self.radio_noseed          = Radiobutton(self.seed_frame, text="Random (current time)",variable=self.random_var, value=0, command=self.disable_custom_seed)
		self.radio_explicitseed    = Radiobutton(self.seed_frame, text="Specific seed:",variable=self.random_var, value=1, command=self.enable_custom_seed)
		self.entry_seed            = Entry(self.seed_frame, width = 10)
		self.label_seed_disclaimer = Label(self.seed_frame, text = "Warning: choosing a specific seed guarantees reproducibility\non the initial state, but not on the simulation sequence.")

		## Verbose checkbox (alone, no frame)
		self.verbose_checkbox = Checkbutton(self.main_frame, text = "Verbose simulator", variable = self.verbose_var, pady=10)

		## Validate frame
		self.validate_frame            = Frame(self.main_frame, pady=10)
		self.button_validate           = Button(self.validate_frame, text = "Go!", command = self.let_s_go, pady=10)
		self.label_duration_disclaimer = Label(self.validate_frame, text = "Warning: running the full 730 days simulation at once takes up to 10 minutes\non a high-end computer. It may take a very long time on some computers.")

		# Insert text in entries
		self.entry_sw  .insert(0, str(DEFAULT_WIDHT))
		self.entry_sh  .insert(0, str(DEFAULT_HEIGHT))
		self.entry_as  .insert(0, str(DEFAULT_AGENT_COUNT))
		self.entry_ai  .insert(0, str(DEFAULT_AGENT_INFECTED_RATIO))
		self.entry_dic .insert(0, str(DEFAULT_DURATION_INCUBATION))
		self.entry_dif .insert(0, str(DEFAULT_DURATION_INFECTIOUS))
		self.entry_dim .insert(0, str(DEFAULT_DURATION_IMMUNE))
		self.entry_tr  .insert(0, str(int(DEFAULT_TRANSMISSION_RATE*100)))
		self.entry_seed.insert(0, DEFAULT_SEED)

		# Set variables values
		self.random_var.set(1)

	def let_s_go(self):
		"""
		This function is called when the user presses
		the "Go!" button.
		"""

		# Get values from fields
		grid_width = int(self.entry_sw.get())
		grid_height = int(self.entry_sh.get())

		total_agents = int(self.entry_as.get())
		infected_ratio = float(self.entry_ai.get())
		infected_agents = int(total_agents*infected_ratio/100)
		susceptible_agents = total_agents - infected_agents

		incubation_duration = int(self.entry_dic.get())
		infectious_duration = int(self.entry_dif.get())
		immune_duration = int(self.entry_dim.get())

		transmission_rate = int(self.entry_tr.get()) / 100

		verbose = True if self.verbose_var.get() == 1 else False

		# Build random object
		random = rand.Random()
		if self.random_var.get() == 1:
			random.seed(self.entry_seed.get())

		# Build model & simulator
		model = World(grid_width, grid_height, susceptible_agents, infected_agents, incubation_duration, infectious_duration, immune_duration, transmission_rate, random)
		simulator = Simulator(model)
		simulator.setDSDEVS(True)

		if verbose == True:
			simulator.setVerbose(None)

		# Build GUI
		Gui(grid_width, grid_height, susceptible_agents, infected_agents, model, simulator)

	def enable_custom_seed(self):
		"""
		This function is called when the user checks
		the seed radio button "Specific seed"
		"""

		self.entry_seed.config(state="normal")

	def disable_custom_seed(self):
		"""
		This function is called when the user checks
		the seed radio button "Random"
		"""

		self.entry_seed.config(state="disabled")

	def run_launcher(self):
		"""
		This function build the GUI by placing the graphical
		elements, then starts the event loop.
		It has to be run on a previously build Launcher object.
		"""

		# Set window parameters
		self.root.geometry(LAUNCHER_WINDOW_SIZE)
		self.root.title("SEIR Simulator")

		# Add main frame to window
		self.main_frame.pack()

		# Place items within main frame
		self.size_frame.pack()
		self.agents_frame.pack()
		self.duration_frame.pack()
		self.transmission_frame.pack()
		self.seed_frame.pack()
		self.verbose_checkbox.pack()
		self.validate_frame.pack()

		# Place items within frames
		## World size frame
		self.label_size.grid(row=0, column=0, columnspan=4)
		self.label_sw  .grid(row=1, column=0)
		self.entry_sw  .grid(row=1, column=1)
		self.label_sh  .grid(row=1, column=2)
		self.entry_sh  .grid(row=1, column=3)

		## Agents count frame
		self.label_agents.grid(row=0, column=0, columnspan=5)
		self.label_as    .grid(row=1, column=0)
		self.entry_as    .grid(row=1, column=1)
		self.label_ai    .grid(row=1, column=2)
		self.entry_ai    .grid(row=1, column=3)
		self.label_ap    .grid(row=1, column=4)

		## Duration frame
		self.label_duration.grid(row=0, column=0, columnspan=6)
		self.label_dic     .grid(row=1, column=0)
		self.entry_dic     .grid(row=1, column=1)
		self.label_dif     .grid(row=1, column=2)
		self.entry_dif     .grid(row=1, column=3)
		self.label_dim     .grid(row=1, column=4)
		self.entry_dim     .grid(row=1, column=5)

		## Transmission frame
		self.label_transmission.grid(row=0, column=0, columnspan=2)
		self.entry_tr          .grid(row=1, column=0)
		self.label_trp         .grid(row=1, column=1)

		## Seed frame
		self.label_seed           .grid(row=0, column=0, columnspan=3)
		self.radio_noseed         .grid(row=1, column=0)
		self.radio_explicitseed   .grid(row=1, column=1)
		self.entry_seed           .grid(row=1, column=2)
		self.label_seed_disclaimer.grid(row=2, column=0, columnspan=3)

		## Valdate frame
		self.button_validate          .pack()
		self.label_duration_disclaimer.pack()

		# Run
		self.root.mainloop()
