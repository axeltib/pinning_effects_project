//  Monte carlo simulation
#include <iostream>
#include <math.h>
#include <array>
#include <string.h>

#include "metropolis.hpp"
// #include "utils.hpp"

// using namespace ParticleSimulator;
// using namespace SimulationUtilities;

int main() {
    int numSteps = 10000;

    int N = 30;
    float n = 10;
    float T = 0.1;

    float L = sqrt((float) N/n);

    ParticleSimulator::Metropolis simulator(N,  L, n, T, numSteps);
    
    simulator.runSimulation();

    std::cout << "Simulation finished. " << std::endl;
    return 0;
}