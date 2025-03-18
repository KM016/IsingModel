#!/bin/bash

# Compile the code
make clean
make

# Define parameters
betas=(0.0 10.0)
num_configs=10000  # Configurations per beta
n_spins=3        # Number of spins for 1D simulation
grid_size=2   # Grid size for 2D simulation

# looping through each beta and simulating
for beta in "${betas[@]}"; do
    ./IsingModel 1D $beta $num_configs $n_spins
    ./IsingModel 2D $beta $num_configs $grid_size
done

# Analysing results results
python analysis.py

# letting user know when all is done 
echo "All distribution tests completed!"