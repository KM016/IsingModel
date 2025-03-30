#!/bin/bash

# Compile the code
make clean
make

# Define parameters
betas=(0.0 0.1 0.5 1.0 2.0 5.0 10.0)
num_configs=10000  # Configurations per beta
num_configs_2D=100 # Configurations per beta for 2D
n_spins=100        # Number of spins for 1D simulation
grid_size=100   # Grid size for 2D simulation

# looping through each beta and simulating
for beta in "${betas[@]}"; do
    ./IsingModel 1D $beta $num_configs $n_spins
    ./IsingModel 2D $beta $num_configs_2D $grid_size
done

# Analysing results results
python analysis.py

# letting user know when all is done 
echo "All simulations and analysis completed!"