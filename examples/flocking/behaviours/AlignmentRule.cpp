#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  // If there are boids in the neighborhood, compute the cohesive force
  if (!neighborhood.empty()) {
    // Iterate through the neighborhood of boids
    for (auto i : neighborhood) {
      // Add the current boids velocity to average velocity variable
      averageVelocity += i->getVelocity();
    }
    // If the neighborhood has more than 0, calculate the average velocity
    if (neighborhood.size() != 0) {
      averageVelocity /= neighborhood.size();
    }
  }

  return Vector2f::normalized(averageVelocity);
}