#include "utils.hpp"

namespace ParticleSimulator {
    class Metropolis {
        public:
            void initializeSimulator(
                SimulationUtilities::Particle *particles, 
                int numParticles, 
                int particleDensity, 
                float temperature
            );

            void updateParticles();
    };
}