//  Monte carlo simulation
#include <iostream>
#include <math.h>
#include <array>

#include "metropolis.hpp"
#include "utils.hpp"

using namespace ParticleSimulator;
// using namespace SimulationUtilities;

int main() {

    /*
    // Initializing particles
    double n;           // Density of particles
    double L;           // Length of unit squares  
    const int N = 20;   // Number of particles

    n = 12;
    L = sqrt(N / n);
    */

    const int N = 20;

    float L;
    double n;

    n = 12;
    L = sqrt(N / n);

    // Initialize the particles
    SimulationUtilities::Particle particles[N]; 

    SimulationUtilities::initializeParticles(particles, N, L);
    
    for (int i = 0; i < N; i++) {
        std::cout << "(" << particles[i].x << ", " << particles[i].y << ")" << std::endl;
    }

    return 0;
}