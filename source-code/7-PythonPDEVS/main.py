import sys

if __name__ == '__main__':

	arguments = sys.argv[1:]

	if len(arguments) == 0:
		###
		# No arguments: launch GUI.

		# Only include this module if we use the GUI to allow running the
		# command-line version without installing graphical requirements.
		from gui.launcher import *

		launcher = Launcher()
		launcher.run_launcher()

	else:
		###
		# Command-line execution

		import command_line as cmd

		cmd.execute_command_line(arguments)
