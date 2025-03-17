#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "IsingModel.h"


#ifdef TEST
void run2DTests() {
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
#endif


int main(int argc, char* argv[]) {

    // Run tests if TEST is defined
    #ifdef TEST
        run2DTests();
        return 0;
    #endif

    // Check command line arguments
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <beta> <num_configs> <grid_size>\n";
        return 1;
    }

    // Parameters
    const double beta = std::atof(argv[1]);
    const int num_configs = std::atoi(argv[2]);
    const int grid_size = std::atoi(argv[3]);

    // Create output directory
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1) << beta;
    std::string folder = "data_2D/beta_" + stream.str();
    system(("mkdir -p " + folder).c_str());

    // Output file
    std::string filename = folder + "/results.txt";
    std::ofstream outfile(filename);
    outfile << "Energy\tMagnetisation\n";

    // Simulation parameters
    const int n_steps = 1000;  // Steps per configuration

    // Run simulations
    IsingModel2D model(beta, grid_size);
    for (int config = 0; config < num_configs; ++config) {
        model.simulate(n_steps);
        outfile << model.totalEnergy() << "\t" << model.totalMagnetisation() << "\n";
    }

    // Close output file and let user know where the results are
    outfile.close();
    std::cout << "Results written to " << filename << std::endl;
    return 0;
}