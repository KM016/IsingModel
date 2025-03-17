#include "IsingModel.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>

// 1D Ising model

IsingModel::IsingModel(double beta, int n_spins) 
    : N(n_spins), beta(beta), spins(n_spins), 
      rng(std::random_device{}()), uniform_dist(0.0, 1.0) {
    if (N <= 0) throw std::invalid_argument("System size must be > 0");
    initSpins();
}

// Initialise spins randomly each spin is either +1 or -1
void IsingModel::initSpins() {
    std::uniform_int_distribution<int> dist(0, 1);
    for (int i = 0; i < N; ++i) {
        spins[i] = dist(rng) * 2 - 1; 
    }
}

// Change in energy from flipping spin i
double IsingModel::delta_E(int i) const {
    int left = (i > 0) ? spins[i-1] : 0;      
    int right = (i < N-1) ? spins[i+1] : 0;  
    return 2 * J * spins[i] * (left + right);
}

// Simulate the system for steps
void IsingModel::simulate(int steps) {
    for (int i = 0; i < steps; ++i) {
        int idx = std::uniform_int_distribution<int>(0, N-1)(rng);
        double dE = delta_E(idx);
        if (dE < 0 || uniform_dist(rng) < exp(-beta * dE)) {
            spins[idx] *= -1;
        }
    }
}

// Calculate total energy
double IsingModel::totalEnergy() const {
    double energy = 0;
    for (int i = 0; i < N-1; i++) { 
        energy += -J * spins[i] * spins[i+1];
    }
    return energy;
}

// Calculate total magnetisation
double IsingModel::totalMagnetisation() const{
    double mag = 0;
    for (int i = 0; i < N; i++){
        mag += spins[i];
    }
    return mag;
}

// Get spin configuration
const std::vector<int>& IsingModel::getSpin() const{
    return spins;
}

// Print spin configuration
void IsingModel::spins_print() {
    for (size_t i = 0; i < spins.size(); i++) {
        if (spins[i] > 0) {
            std::cout << "+";
        } else {
            std::cout << "-";
        }
    }
    printf("\n");
}

// Print spin energy and magnetisation
void IsingModel::spins_stats() {
    double energy = totalEnergy();
    double magnetisation = totalMagnetisation();

    std::cout << "Energy: " << energy << "  Magnetization: " << magnetisation << std::endl;
}