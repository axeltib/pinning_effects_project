#include <array>
#include <iostream>

#include "utils.hpp"

void SimulationUtilities::initializeParticles(SimulationUtilities::Particle * particles, int numParticles, float squareLength) {
    // Evenly distribute using Halton sequence in base 2 and 3
    double x;
    double y;

    double f;

    int j;

    for (int i = 0; i < numParticles; i++) {
        x = 0;
        y = 0;
        f = 1;
        j = i;

        while (j > 0){
            f = f / 2;
            x = x + f * (j%2);
            j = j / 2;
        }
        
        f = 1;
        j = i;
        while (j > 0){
            f = f / 3;
            y = y + f * (j%3);
            j = j / 3;
        }

        particles[i].x = x * squareLength;
        particles[i].y = y * squareLength;
        particles[i].id = i;
    }

}

