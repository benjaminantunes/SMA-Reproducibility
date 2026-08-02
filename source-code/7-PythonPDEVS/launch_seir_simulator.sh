#!/usr/bin/bash

if [ ! -d "./.venv" ]; then
  echo "Virtual environment has not been set up."
  echo "Setting up python venv."

  python -m venv .venv
  source ./.venv/bin/activate

  python -m pip install setuptools
  python -m pip install matplotlib
  python -m pip install tk
  python -m pip install git+https://github.com/cfoucher-laas/PythonPDEVS.git@fix_DEVS.py

  deactivate

  echo "Virtual environment successully defined."
fi

source ./.venv/bin/activate

echo "Launching simulator"
python main.py
echo "Simulator exited"

deactivate
