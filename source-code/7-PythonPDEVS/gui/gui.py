# Tkinter
from tkinter import *
from tkinter import filedialog

# Matplotlib
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt

# PyPDEVS
from pypdevs.infinity import INFINITY

# Current app
from config import *
from monitor import *


class Gui():
	def __init__(self, width, height, susceptible_agents, infected_agents, model, simulator):
		# Model & simulator
		self.model = model
		self.sim = simulator

		# GUI
		self.build_gui(susceptible_agents, infected_agents)
		self.draw_grid(width, height)
		self.draw_agents()

		# Results
		agents = susceptible_agents + infected_agents
		self.monitor = Monitor(agents, model)

	def build_gui(self, susceptible_agents, infected_agents):
		self.gui = Toplevel()
		self.main_frame = Frame(self.gui)

		# Build top bar
		self.top_bar_simu = LabelFrame(self.main_frame)

		self.label_simulate_for = Label(self.top_bar_simu, text = "Simulate for:")
		self.entry_simulate_for = Entry(self.top_bar_simu, width=5)
		self.entry_simulate_for.insert(0, DEFAULT_SIMULATION_DURATION)
		self.label_days = Label(self.top_bar_simu, text = "days")
		self.button_start = Button(self.top_bar_simu, text = "Simulate", command = self.launch_simulation)

		self.top_bar_results = LabelFrame(self.main_frame)
		self.current_time = Label(self.top_bar_results, text = "Current time: 0 days; ")
		self.label_s = Label(self.top_bar_results, text = "S: " + str(susceptible_agents) + "; ")
		self.label_e = Label(self.top_bar_results, text = "E: 0; ")
		self.label_i = Label(self.top_bar_results, text = "I: " + str(infected_agents) + "; ")
		self.label_r = Label(self.top_bar_results, text = "R: 0")
		self.button_results = Button(self.top_bar_results, text = "Draw results", command = self.draw_results)
		self.button_export = Button(self.top_bar_results, text = "Export results", command = self.export_results)

		# Build grid
		self.display_area = Frame(self.main_frame)
		self.grid = Canvas(self.display_area, width=1400, height=900)
		self.v_scroll = Scrollbar(self.display_area, command = self.grid.yview)
		self.h_scroll = Scrollbar(self.display_area, command = self.grid.xview, orient=HORIZONTAL)
		self.grid.configure(xscrollcommand=self.h_scroll.set, yscrollcommand=self.v_scroll.set, scrollregion=self.grid.bbox("all"))

		self.gui.geometry(GUI_WINDOW_SIZE)

		# Pack
		self.main_frame.pack()

		self.top_bar_simu.grid(row = 0, column = 0)
		self.top_bar_results.grid(row = 0, column = 1)
		self.display_area.grid(row = 1, column = 0, columnspan= 2)

		self.label_simulate_for.grid(row = 0, column = 0)
		self.entry_simulate_for.grid(row = 0, column = 1)
		self.label_days.grid(row=0, column = 2)
		self.button_start.grid(row = 0, column = 3)

		self.current_time.grid(row = 0, column = 0)
		self.label_s.grid(row = 0, column = 1)
		self.label_e.grid(row = 0, column = 2)
		self.label_i.grid(row = 0, column = 3)
		self.label_r.grid(row = 0, column = 4)
		self.button_results.grid(row = 0, column = 5)
		self.button_export.grid(row = 0, column = 6)

		self.grid.grid(row = 0, column = 0)
		self.v_scroll.grid(row = 0, column = 1, sticky="ns")
		self.h_scroll.grid(row = 1, column = 0, sticky="ew")

	def draw_line(self, x1, y1, x2, y2):
		self.grid.create_line(x1*GUI_GRID_SIZE + GUI_GRID_OFFSET, y1*GUI_GRID_SIZE + GUI_GRID_OFFSET, x2*GUI_GRID_SIZE + GUI_GRID_OFFSET, y2*GUI_GRID_SIZE + GUI_GRID_OFFSET)

	def clear_agents(self):
		self.grid.delete("agent")

	def draw_text_on_grid(self, x, y, text, tag, color = "black", size = None):
		if size == None:
			self.grid.create_text(x*GUI_GRID_SIZE + GUI_GRID_SIZE/2 + GUI_GRID_OFFSET, \
								  y*GUI_GRID_SIZE + GUI_GRID_SIZE/2 + GUI_GRID_OFFSET, \
								  text = text, \
								  tag  = tag, \
								  fill = color)
		else:
			self.grid.create_text(x*GUI_GRID_SIZE + GUI_GRID_SIZE/2 + GUI_GRID_OFFSET, \
								  y*GUI_GRID_SIZE + GUI_GRID_SIZE/2 + GUI_GRID_OFFSET, \
								  text = text, \
								  tag  = tag, \
								  fill = color, \
								  font = ('Courier', str(size)))

	def draw_agent_on_grid(self, x, y, status):
		color = "blue"    if status == "S" else \
		        "red"     if status == "I" else \
				"magenta" if status == "E" else \
				"yellow"  # status == "R"

		self.draw_text_on_grid(x = x, y = y, text = status, color = color, tag = "agent")

	def draw_grid(self, width, height):
		# Border
		self.draw_line(0,     0,      width, 0)
		self.draw_line(width, 0,      width, height)
		self.draw_line(width, height, 0,     height)
		self.draw_line(0,     height, 0,     0)

		# Vertical lines and indexes
		for i in range(width):
			self.draw_line(i, 0, i, height)
			self.draw_text_on_grid(x = i, y = -1, text = str(i), tag = "vindex", size = 5)

		# Horizontal lines and indexes
		for i in range(height):
			self.draw_line(0, i, width, i)
			self.draw_text_on_grid(x = -1, y = i, text = str(i), tag = "hindex", size = 5)

	def draw_agents(self):
		for agent in self.model.agents:
			(x,y) = agent.state["Position"]
			status = agent.state["Status"]
			self.draw_agent_on_grid(x, y, status)

	def update_gui(self):
		self.clear_agents()
		self.draw_agents()

		results = self.monitor.get_results()

		self.current_time["text"] = "Current time: " + str(int(results['t'][-1])) + " days; "
		self.label_s["text"] = "S: " + str(results['S'][-1]) + "; "
		self.label_e["text"] = "E: " + str(results['E'][-1]) + "; "
		self.label_i["text"] = "I: " + str(results['I'][-1]) + "; "
		self.label_r["text"] = "R: " + str(results['R'][-1])

	def draw_results(self):
		(t, resS, resE, resI, resR) = self.monitor.get_normalized_results()

		plt.figure()
		plt.plot(t, resS, 'b', label="S")
		plt.plot(t, resE, 'm', label="E")
		plt.plot(t, resI, 'r', label="I")
		plt.plot(t, resR, 'y', label="R")
		plt.title("S, E, I and R agents population over time")
		plt.xlabel("Time in days")
		plt.ylabel("Ratio of agents in each state")
		plt.legend()
		plt.show()

	def launch_simulation(self):
		simulate_for = float(self.entry_simulate_for.get())
		current_time = self.sim.termination_time

		if current_time != INFINITY:
			end_time = current_time + simulate_for
		else:
			current_time = 0
			end_time = simulate_for

		for time in range(int(current_time)+1, int(end_time)+1):
			self.sim.setTerminationTime(time)
			self.sim.simulate()
			self.monitor.update_results(self.sim.termination_time)

		self.update_gui()

	def export_results(self):
		save_file = filedialog.asksaveasfile(parent=self.gui, defaultextension=".csv")
		if save_file:
			self.monitor.export_results(save_file)
			save_file.close()
