#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <fstream>

#include "metropolis.hpp"

using namespace ParticleSimulator;

// const float kB = 1.380649 * pow(10, -23);
const float  kB = 1.0;

Metropolis::Metropolis(int numParticles, float sideLength, float particleDensity, float temperature, int numSteps) {
    
    numTimeSteps = numSteps;
    
    N = numParticles;
    L = sideLength;
    n = particleDensity;
    T = temperature;

    beta = 1 / (kB * T);

    totalCount = 0;
    rejectedCount = 0;

    // Potential parameters
    U0 = 2.6796;
    
    // Included in header file
    // C = {144.3760,  37.2100, -36.1911, 7.2900};
    // A = {0.1405, 0.1960, 0.4200};

    srand(time(NULL));

    SimulationUtilities::initializeParticles(particles, N, L);
}

void Metropolis::runSimulation() {
     for (int i = 0; i < numTimeSteps; i++) {
        updateParticles();

        saveToCSV("results.csv");

        if (i % 100 == 0) {
            std::cout << "Total energy: " << calculateHamiltonian() << " - " << (float) i / numTimeSteps << "% done, " << "Rejection rate: " << (float) rejectedCount / totalCount << std::endl;
        }
    }
}

void Metropolis::saveToCSV(std::string fileName) {
    std::ofstream myfile;
    myfile.open (fileName, std::ios::app);

    for (int i = 0; i < N; i++) {
        if (i == 0) {
            myfile << particles[i].x << "," << particles[i].y; 
        } else { 
            myfile << "," << particles[i].x << "," << particles[i].y; 
        }
    }
    myfile << "\n";

    myfile.close();
}

void Metropolis::updateParticles() {
    // Sequential update
    SimulationUtilities::Particle placeholderParticle;

    float energyBefore;
    float energyAfter;
    float deltaEnergy;

    float totDeltaEnergy = 0;

    for (int i = 0; i < N; i++) {
        energyBefore = calculateHamiltonian();
        placeholderParticle = particles[i];
        particles[i] = getCandidateMove(i);
        energyAfter = calculateHamiltonian();

        deltaEnergy = energyAfter - energyBefore;
        totDeltaEnergy += deltaEnergy;
        
        // Calculate acceptance porbability and generate random number to see if new state will be commited
        acceptanceProb = calculateAcceptanceProbability(deltaEnergy);

        if (deltaEnergy > 0 || SimulationUtilities::getRandomNumber(1.0) >  acceptanceProb) {
            // Move unsuccesful, returning to the last state
            particles[i] = placeholderParticle;
            rejectedCount++;
        }
        totalCount++;
    }
}

float Metropolis::calculateHamiltonian() {
    float E = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j) {
                E += calculateIntraparticlePotential(
                    SimulationUtilities::getDistanceBetweenParticles(particles[i], particles[j], L)
                );
            }
        }
    }
    return E;
}

float Metropolis::calculateIntraparticlePotential(float r) {
    float U = 0;

    if (r <= 0.15) {
        U = U0 - C[0] * pow((r + 0.15), 4.0);
    } else {
        for (int i = 0; i < 3; i++) {
            U += C[i + 1] * std::cyl_bessel_k(0, r / A[i]);
        }
    }

    return U;
}

float Metropolis::calculateAcceptanceProbability(float deltaEnergy) {
    if (exp(- beta * deltaEnergy) > 1.0) {
        return 1.0;
    }
    return exp(- beta * deltaEnergy);
}

SimulationUtilities::Particle Metropolis::getCandidateMove(int particleIndex) {
    float rejectionRateCompensation = 0.01;

    float xRand = SimulationUtilities::getRandomNumber(2 * sqrt((float) 1/n)) - sqrt((float) 1/n);
    float yRand = SimulationUtilities::getRandomNumber(2 * sqrt((float) 1/n)) - sqrt((float) 1/n);

    SimulationUtilities::Particle particle;
    particle.x = particles[particleIndex].x + rejectionRateCompensation * xRand;
    particle.y = particles[particleIndex].y + rejectionRateCompensation * yRand;
    particle.id = particles[particleIndex].id;

    // Move the particle inside the unit box
    if (particle.x > L) {
        particle.x -= L;
    } else if (particle.x < 0 ) {
        particle.x += L;
    }
    if (particle.y > L) {
        particle.y -= L;
    } else if (particle.y < 0 ) {
        particle.y += L;
    }

    return particle;
}