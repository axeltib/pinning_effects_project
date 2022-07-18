

namespace SimulationUtilities
{   
    struct Particle {
        // Used to represent a particle in the simulation
        float x;
        float y;
        int id;
    };

    void initializeParticles(Particle * particles, int numParticles, float squareLength);    
} // namespace SimulationUtilities
