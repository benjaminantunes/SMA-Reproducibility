# Automatically configure and run

A script is provided to automatically configure and run the simulator provided you have a bash shell available.
It will use a python virtual environment in which all dependencies are installed, then run the GUI.
Just run the following command in the simulator root folder:

```bash
./launch_seir_simulator.sh
```

# Manual configuration and run

Manually running the simulator allows you to provide parameters (see the [Command line](#Provide_arguments_using_command_line) section below).

It is recomanded to work in a Python virtual environment.

You can also run the above script once so that the virtual environment is created with all required dependencies.
This allow you to skip the configuration and go straight to the execution commands.
Be sure to activate the venv before running commands.

NOTE: if using Ubuntu, you may require to change the below `python` commands to `python3`.

## Setting up a venv

In the root folder of the simulator, run the following command:

```bash
python -m venv .venv
```
After the environment has been set up, you'll need to activate it.
Activating the environment is required every time you want to run the simulator from a new shell, or after the environment has been deactivated.
```bash
source ./.venv/bin/activate
```
When you are done with the simulator, you can deactivate the environment:
```bash
deactivate
```

## Install Dependencies

This simulator must be run in Python 3 and requires PythonPDEVS.
Aditionnaly, the following external modules are required to use the GUI:
- Matplotlib
- Tkinter

If you use a virtual environment, make sure to activate it before running the following commands.
If you choose not to work in a virtual environment, you will probably have to add a `--user` argument to all installation commands.

### PythonPDEVS

Use the following commands to clone and install PythonPDEVS:
``` bash
python -m pip install setuptools
python -m pip install git+https://github.com/cfoucher-laas/PythonPDEVS.git@fix_DEVS.py
```

### GUI dependencies

These dependencies are only required if you use the GUI version of the simulator.

Install Matplotlib and Tkinter:
``` bash
python -m pip install matplotlib
python -m pip install tk
```

## Execution

### Using the GUI

Launch the following command:

``` bash
python main.py
```

### Provide arguments using command line

To run without GUI with the default values, run with the following argument:

```bash
python main.py -d
```

To see all available parameters, run with the following argument:

```bash
python main.py -h
```
