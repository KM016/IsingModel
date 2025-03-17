#!/bin/bash

# Compile the code
make clean
make

# Define parameters
betas=(0.0 0.1 0.5 1.0 2.0 5.0 10.0)
num_configs=1000  # Configurations per beta

# looping through each beta and simulating
for beta in "${betas[@]}"; do
    ./IsingSim1D $beta $num_configs
done

# Analysing results results
python 1D_analyse.py

# letting user know when all is done 
echo "All simulations and analysis completed!"