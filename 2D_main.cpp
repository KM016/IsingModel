#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "IsingModel.h"


int main(int argc, char* argv[]) {

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