#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <vector>
#include "IsingModel.h"

#ifdef TEST

// 1D Test Function
void runTests1D() {
    std::cout << "=== 1D TESTING MODE ===" << std::endl;
    
    // Test all 8 states for a 3-spin system
    std::vector<std::vector<int>> test_states = {
        {+1, +1, +1}, {+1, +1, -1}, {+1, -1, +1}, {+1, -1, -1},
        {-1, +1, +1}, {-1, +1, -1}, {-1, -1, +1}, {-1, -1, -1}
    };

    IsingModel model(0.0, 3); // Using beta = 0 for testing

    for (const auto& state : test_states) {
        model.getSpin() = state;
        std::cout << "State: ";
        model.spins_print();
        model.spins_stats();
        std::cout << "-----------------" << std::endl;
    }
}


// 2D Test Function
void runTests2D() {
    std::cout << "=== 2D TESTING MODE ===" << std::endl;

    // Test 1
    IsingModel2D modeltest1(0.0, 2);
    modeltest1.getSpins() = {
        {+1, +1},
        {+1, +1}
    };
    modeltest1.spins_print();
    std::cout << "Expected Energy: -4\n";
    modeltest1.spins_stats();

    // Test 2
    std::cout << "-----------------\n";
    IsingModel2D modeltest2(0.0, 2);
    modeltest2.getSpins() = {
        {+1, -1},
        {-1, +1}
    };
    modeltest2.spins_print();
    std::cout << "Expected Energy: 4\n";
    modeltest2.spins_stats();


    // Test 3
    std::cout << "-----------------\n";
    IsingModel2D modeltest3(0.0, 2);
    modeltest3.getSpins() = {
        {+1, +1},
        {+1, -1}
    };
    modeltest3.spins_print();
    std::cout << "Expected Energy: 0\n";
    modeltest3.spins_stats();

    // Test 4
    std::cout << "-----------------\n";
    IsingModel2D modeltest4(0.0, 3);
    modeltest4.getSpins() = {
        {+1, +1, +1},
        {+1, +1, -1},
        {+1, +1, +1}
    };
    modeltest4.spins_print();
    std::cout << "Expected Energy: -6\n";
    modeltest4.spins_stats();

    // Test 5
    std::cout << "-----------------\n";
    IsingModel2D modeltest5(0.0, 3);
    modeltest5.getSpins() = {
        {+1, +1, +1},
        {+1, +1, +1},
        {+1, +1, +1}
    };
    modeltest5.spins_print();
    std::cout << "Expected Energy: -12\n"; 
    modeltest5.spins_stats();

    // Test 6
    std::cout << "-----------------\n";
    IsingModel2D modeltest6(0.0, 3);
    modeltest6.getSpins() = {
        {+1, -1, +1},
        {-1, +1, -1},
        {+1, -1, +1}
    };
    modeltest6.spins_print();
    std::cout << "Expected Energy: 12\n";
    modeltest6.spins_stats();
    std::cout << "-----------------\n";
}
#endif // TEST

int main(int argc, char* argv[]){
    // If the first argument is "TEST", run the test routines.
    if (argc >= 2 && std::string(argv[1]) == "TEST") {
        #ifdef TEST
            std::cout << "Running tests..." << std::endl;
            runTests1D();
            std::cout << std::endl;
            runTests2D();
        #endif

        return 0;
    }

    // Simulation usage: ./IsingSim <mode> <beta> <n_configs> [n_spins|grid_size]
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <mode> <beta> <n_configs> [n_spins|grid_size]\n"
                  << "Mode must be \"1D\" or \"2D\"." << std::endl;
        return 1;
    }

    // Parse command line arguments
    std::string mode = argv[1];
    double beta = std::atof(argv[2]);
    int num_configs = std::atoi(argv[3]);

    // 1D Simulation procedure
    if (mode == "1D") {
        // For 1D simulation, the optional parameter is number of spins (default: 100)
        int n_spins = (argc >= 5) ? std::atoi(argv[4]) : 100;
        const int steps = 100000; // steps for 1D

        // Create output directory and file for 1D simulation results
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(1) << beta; 
        std::string folder = "data_1D/beta_" + stream.str();
        system(("mkdir -p " + folder).c_str());
        std::string filename = folder + "/results.txt";
        std::ofstream outfile(filename);
        if (!outfile) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return 1;
        }
        outfile << "Energy\tMagnetisation\n";

        // Run simulation for each configuration
        for (int config = 0; config < num_configs; ++config) {
            IsingModel model(beta, n_spins);
            model.simulate(steps);
            outfile << model.totalEnergy() << "\t" 
                    << model.totalMagnetisation() << "\n";
        }
        outfile.close();
        std::cout << "1D simulation results written to " << filename << std::endl;
    }

    // 2D Simulation procedure
    else if (mode == "2D") {
        // For 2D simulation, the optional parameter is grid size (default: 100)
        int grid_size = (argc >= 5) ? std::atoi(argv[4]) : 100;
        const int n_steps = 10000000; // Monte Carlo steps for 2D

        // Create output directory and file for 2D simulation results
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(1) << beta;
        std::string folder = "data_2D/beta_" + stream.str();
        system(("mkdir -p " + folder).c_str());
        std::string filename = folder + "/results.txt";
        std::ofstream outfile(filename);
        if (!outfile) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return 1;
        }
        outfile << "Energy\tMagnetisation\n";

        // Run simulation for each configuration
        for (int config = 0; config < num_configs; ++config) {
            IsingModel2D model(beta, grid_size); // reinitialise model for each configuration
            model.simulate(n_steps);
            outfile << model.totalEnergy() << "\t" 
                    << model.totalMagnetisation() << "\n";
        }
        outfile.close();
        std::cout << "2D simulation results written to " << filename << std::endl;
    }
    return 0;
}
