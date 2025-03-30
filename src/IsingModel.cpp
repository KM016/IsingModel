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

    std::cout << "Energy: " << energy << "  Magnetisation: " << magnetisation << std::endl;
}




// 2D Ising Model
IsingModel2D::IsingModel2D(double beta, int grid_size) 
    : L(grid_size), beta(beta), spins(L, std::vector<int>(L)),
      rng(std::random_device{}()), uniform_dist(0.0, 1.0) {
    if (L <= 0) throw std::invalid_argument("Grid size must be > 0");
    initSpins();
}

// Initialise spins randomly each spin is either +1 or -1
void IsingModel2D::initSpins() {
    std::uniform_int_distribution<int> dist(0, 1);
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            spins[i][j] = dist(rng) * 2 - 1; 
        }
    }
}

// Change in energy from flipping spin at (x, y)
double IsingModel2D::delta_E(int x, int y) const {
    int current = spins[x][y];
    int left  = spins[(x - 1 + L) % L][y];
    int right = spins[(x + 1) % L][y];
    int up    = spins[x][(y - 1 + L) % L];
    int down  = spins[x][(y + 1) % L];
    return 2 * J * current * (left + right + up + down);
}


// Simulate the system for n_steps
void IsingModel2D::simulate(int n_steps) {
    for (int i = 0; i < n_steps; ++i) {
        int x = std::uniform_int_distribution<int>(0, L-1)(rng);
        int y = std::uniform_int_distribution<int>(0, L-1)(rng);
        double dE = delta_E(x, y);
        if (dE < 0 || uniform_dist(rng) < std::exp(-beta * dE)) {
            spins[x][y] *= -1;
        }
    }
}

// Calculate total energy
double IsingModel2D::totalEnergy() const {
    double energy = 0.0;
    for (int x = 0; x < L; ++x) {
        for (int y = 0; y < L; ++y) {
            energy += -J * spins[x][y] * spins[(x + 1) % L][y];
            energy += -J * spins[x][y] * spins[x][(y + 1) % L];
        }
    }
    return energy;
}


// Calculate total magnetisation
double IsingModel2D::totalMagnetisation() const {
    double mag = 0.0;
    for (const auto& row : spins) {
        for (int s : row) mag += s;
    }
    return mag;
}

// Get spin configuration
const std::vector<std::vector<int>>& IsingModel2D::getSpins() const {
    return spins;
}

// Print spin configuration
void IsingModel2D::spins_print() const {
    for (const auto& row : spins) {
        for (int s : row) {
            std::cout << (s > 0 ? "+" : "-") << " ";
        }
        std::cout << std::endl;
    }
}

// Print spin energy and magnetisation
void IsingModel2D::spins_stats() const {
    std::cout << "Energy: " << totalEnergy() 
              << "  Magnetisation: " << totalMagnetisation() << std::endl;
}