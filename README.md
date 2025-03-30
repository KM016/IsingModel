# Assessment 2

## Overview
This project implements Monte Carlo simulations of the Ising model in both one dimension (1D) and two dimensions (2D). The Ising model is used to study the behavior of spin systems at different temperatures (represented by the parameter β). In the 1D model, each spin interacts only with its nearest neighbor. In the 2D model, the system is represented as a grid where each spin interacts with its four immediate neighbors (up, down, left, and right). Monte Carlo methods are used to generate configurations, and statistical averages (e.g. energy, magnetisation) are computed from these configurations.
<br>

## Project Structure

IsingProject/
├── src/
│   ├── main.cpp           # Unified main file for both 1D and 2D simulations
│   ├── IsingModel.cpp     # Implementation of the IsingModel classes (1D and 2D)
│   └── IsingModel.h       # Header file for the IsingModel classes
├── analysis.py            # Python script to analyse simulation results and generate visualisations
├── Makefile               # Build instructions for compiling the C++ code
├── run.sh                 # Shell script to automate simulation runs and analysis
├── .gitignore             # Files and directories to ignore 
├── README.md              # This file
├── data_1D/               # Directory for storing 1D simulation output data
├── data_2D/               # Directory for storing 2D simulation output data 
├── visualisations_1D/     # Directory for storing 1D analysis plots 
└── visualisations_2D/     # Directory for storing 2D analysis plots
<br>

## Building the Project
The project is built using the Makefile. The source files are located in the src/ directory.
- To compile the project, run: make
    - This will generate an executable called IsingSim.
- For testing (running with embedded test routines), use: make test
<br>

## Running the Simulation
The executable supports both 1D and 2D simulations. It accepts the following command-line arguments:

Usage: ./IsingSim <mode> <beta> <n_configs> [n_spins|grid_size]
Mode must be "1D" or "2D".

- mode: Either "1D" or "2D" to specify which simulation to run.
- n_spins: For 1D simulations (optional; default is 100).
- grid_size: For 2D simulations (optional; default is 100).
<br>

## Running Automated Script 
The provided run.sh script automates the simulation and analysis process:
- Compile the project:
    - The script calls make clean and make.
- Run Simulations:
    - For a range of β values (0.0, 0.1, 0.5, 1.0, 2.0, 5.0, 10.0), the script runs both the 1D and 2D simulations.
- Analyse Results:
    - The script uses python analysis.py, which generates visualisations (histograms and trend plots) for both simulation types.
    - NOTE: when running you may want to make n_steps in the 2D part of IsingModel.cpp equal to 100,000 or 10,000 and increase num_configs_2D to match num_configs to save some time. 
<br>

## Analysis and Visualisation
The analysis.py script reads the simulation results from data_1D/ and data_2D/, computes averages, and generates:
- Histograms of energy and magnetisation distributions for various β values.
- Trend plots showing how average energy and average absolute magnetisation vary with β.
- The generated plots are stored in visualisations_1D/ and visualisations_2D/.
<br>

## Classes and Functions
### IsingModel (1D)
- Constructor: IsingModel(double beta, int n_spins = 100)
    - Initialises a 1D Ising model with a given number of spins and temperature factor β.
- initSpins():
    - Randomly sets each spin to +1 or -1.
- simulate(int steps):
    - Runs the Monte Carlo simulation for the specified number of steps.
- totalEnergy():
    - Computes the total energy of the spin configuration.
- totalMagnetisation():
    - Computes the total magnetisation (sum of spins).
- spins_print() and spins_stats():
    - Utility functions to print the spin configuration and corresponding energy and magnetisation.
<br>

### IsingModel2D (2D)
- Constructor: IsingModel2D(double beta, int grid_size = 100)
    - Initialises a 2D Ising model on a grid of size grid_size x grid_size.
- initSpins():
    - Randomly sets each spin in the grid to +1 or -1.
- simulate(int n_steps):
    - Runs the Monte Carlo simulation for the grid using the Metropolis algorithm.
- totalEnergy():
    - Computes the total energy from horizontal and vertical nearest-neighbor interactions.
- totalMagnetisation():
    - Computes the total magnetisation of the grid.
- spins_print() and spins_stats():
    - Utility functions to display the grid configuration and its energy and magnetisation.
<br>

### Main Function (main.cpp)
- Handles both simulation modes ("1D" and "2D") based on command line arguments.
- Sets up output directories, runs simulations, and writes results to text files.
<br>

### Python Analysis (analysis.py)
- analyse_beta_1D(beta):
    - Loads 1D simulation data, computes averages, and generates histograms.
- analyse_beta_2D(beta):
    - Loads 2D simulation data, computes averages, and generates histograms.
- main():
    - Iterates over a range of β values to generate and save trend plots for energy and magnetisation.

### Distribution Tests 
- run: ./run_distTest.sh
- output will be visualisations of test cases with beta = 0 and 10 and a 2x2 test case with beta = 0 and 10
- these visualisations confirm the model is correct as visualisations match theoretical distributions
