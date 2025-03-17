#ifndef ISING_MODEL_H
#define ISING_MODEL_H

#include <vector>
#include <random>

// 1D Ising model class
class IsingModel {
private:
    int N;      // number of spins                     
    const double J = 1.0;       // default to 1
    double beta;                
    std::vector<int> spins;     // spin configuration  
    std::mt19937 rng;       // random number generator           
    std::uniform_real_distribution<double> uniform_dist;        // uniform distribution 

    double delta_E(int i) const;        // change in energy from flipping spin i 

public:
    IsingModel(double beta, int n_spins = 100);     // constructor
    void initSpins();       // initialise spins randomly           
    void simulate(int steps);       // simulate the system for steps   
    double totalEnergy() const;     // calculate total energy   
    double totalMagnetisation() const;      // calculate total magnetisation 
    void spins_print();     // print spin configuration         
    void spins_stats();     // print spin energy and magnetisation

    
    const std::vector<int>& getSpin() const;        // get spin configuration
    std::vector<int>& getSpin() { return spins; }       // get spin configuration non const 
};

// 2D Ising model class
class IsingModel2D {
    private:
        int L;      // grid size                 
        const double J = 1.0;       
        double beta;                
        std::vector<std::vector<int>> spins;        // spin configuration 
        std::mt19937 rng;       // random number generator           
        std::uniform_real_distribution<double> uniform_dist;        // uniform distribution
    
        double delta_E(int x, int y) const;     // change in energy from flipping spin at (x, y) 
    
    public:
        IsingModel2D(double beta, int grid_size = 100);     // constructor
        void initSpins();           // initialise spins randomly     
        void simulate(int n_steps);     // simulate the system for n_steps 
        double totalEnergy() const;     // calculate total energy
        double totalMagnetisation() const;      // calculate total magnetisation
        void spins_print() const;       // print spin configuration  
        void spins_stats() const;       // print spin energy and magnetisation   
        
        const std::vector<std::vector<int>>& getSpins() const;      // get spin configuration
        std::vector<std::vector<int>>& getSpins() { return spins; }    // get spin configuration non const
    };

#endif