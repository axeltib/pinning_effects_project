#include <vector>

namespace SimulationUtilities
{   
    struct Particle {
        // Used to represent a particle in the simulation
        float x;
        float y;
        int id;
    };

    float getRandomNumber(float scale);

    void initializeParticles(Particle * particles, int numParticles, float squareLength);    

    float getDistanceBetweenParticles(Particle particle1, Particle particle2, float L);
    // Calculates the distance between two particles using periodic boundary condition determined by L

} // namespace SimulationUtilities
