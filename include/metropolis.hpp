#include <vector> 

#include "utils.hpp"

namespace ParticleSimulator {
    class Metropolis {

        public:
            int numTimeSteps;

            int N;
            float L;
            float n;
            float T;
            float beta;

            float acceptanceProb;

            float totalCount = 0;
            float rejectedCount = 0;

            // Potential parameters
            float U0;
            
            float C[4] = {144.3760,  37.2100, -36.1911, 7.2900};
            // float C1;
            // float C2;
            // float C3;

            float A[3] = {0.1405, 0.1960, 0.4200};
            // float A2;s

            SimulationUtilities::Particle particles [30];

            Metropolis(int numParticles, float sideLength, float particleDensity, float temperature, int numSteps);
            // Constructor for the class

            void runSimulation();

            void updateParticles();

            void saveToCSV(std::string fileName);


        private:
            float calculateAcceptanceProbability(float energyDelta);

            float calculateHamiltonian();
            // Calculating the Hamiltonian (total energy) of the current 

            float calculateIntraparticlePotential(float);
            // Calculating the potential between two particles

           SimulationUtilities::Particle getCandidateMove(int);
           // Generates a candidate move within a 2/sqrt(n) box
    };
}