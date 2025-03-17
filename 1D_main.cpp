#include <iostream>
#include <fstream>
#include <ctime>
#include "IsingModel.h"

#include <iomanip> 
#include <sstream>

int main(int argc, char* argv[]){
    // Check command line arguments
    if (argc < 3){
        std::cerr << "Usage: " << argv[0] << " <beta> <n_configs>" << std::endl;
        return 1;
    }

    // Parameters
    const double beta = std::atof(argv[1]); 
    const int num_configs = std::atoi(argv[2]);
    const int n_spins = (argc >= 4) ? std::atoi(argv[3]) : 100;

    // Create output directory
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1) << beta; 
    std::string folder = "data_1D/beta_" + stream.str();
    system(("mkdir -p " + folder).c_str());

    // Output file
    std::string filename = folder + "/results.txt";
    std::ofstream outfile(filename);
    outfile << "Energy\tMagnetisation\n";


    // Simulation
    const int steps = 100000;
    for (int config = 0; config < num_configs; ++config) {
        IsingModel model(beta, n_spins);
        model.simulate(steps);
        outfile << model.totalEnergy() << "\t" 
                << model.totalMagnetisation() << "\n";
    }

    // Close output file and let user know where the results are
    outfile.close();
    std::cout << "Results written to " << filename << std::endl;
    return 0;
}