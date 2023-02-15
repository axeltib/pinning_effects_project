#include <iostream>
#include <math.h>

#include "utils.hpp"


void SimulationUtilities::initializeParticles(SimulationUtilities::Particle * particles, int numParticles, float squareLength) {
    // Evenly distribute using Halton sequence in base 2 and 3
    double x;
    double y;

    double f;

    int j;

    for (int i = 0; i < numParticles; i++) {
        // x = 0;
        // y = 0;
        // f = 1;
        // j = i;

        // while (j > 0){
        //     f = f / 2;
        //     x = x + f * (j%2);
        //     j = j / 2;
        // }
        
        // f = 1;
        // j = i;
        // while (j > 0){
        //     f = f / 3;
        //     y = y + f * (j%3);
        //     j = j / 3;
        // }

        particles[i].x = (float) rand()/RAND_MAX  * squareLength;
        particles[i].y = (float) rand()/RAND_MAX  * squareLength;
        particles[i].id = i;
    }

}

float SimulationUtilities::getDistanceBetweenParticles(SimulationUtilities::Particle particle1, SimulationUtilities::Particle particle2, float L) {
    float dx;
    float dy;

    dx = abs(particle2.x - particle1.x);
    dy = abs(particle2.y - particle1.y);

    if (dx > L / 2) {
        dx = L - dx;
    }
    if (dy > L / 2) {
        dy = L - dy;
    }

    return sqrt(dx*dx + dy*dy);
}

float SimulationUtilities::getRandomNumber(float scale) {
    float genVal = (float) rand()/RAND_MAX;
    return scale * genVal;
}
