#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f cohesionForce;
  
  // If there are boids in the neighborhood, compute the cohesive force
  if (!neighborhood.empty()) {
    for (auto i : neighborhood) {
      // Ignore the current boid
      if (i->getPosition().x == boid->getPosition().x && i->getPosition().y == boid->getPosition().y) {
        continue;
      }
      
      // Calculate the direction vector from the current boid to the neighbor boid
      Vector2f dir = {i->getPosition().x - boid->getPosition().x , 
          i->getPosition().y - boid->getPosition().y};
      
      // Compute the Euclidean distance between the two boids
      float dist = sqrt(dir.x * dir.x + dir.y * dir.y);
      // Don't influence boids that are within a certain distance from the current boid
      if (1.0f >= dist) {
        continue;
      }

      // Normalize the direction vector to get the unit vector
      Vector2f unit = {dir.x / dist, dir.y / dist};

      // Computes the cohesive force strength which is inversely proportional to the distance
      float strength = 1.0f;
      
      // Accumulate the weighted cohesive force in the respective direction
      cohesionForce.x += unit.x * strength;
      cohesionForce.y += unit.y * strength;
    }
    // Normalize the accumulated cohesive force to make sure it has a unit magnitude
    cohesionForce = Vector2f::normalized(cohesionForce);

    return cohesionForce;
  }
  return Vector2f::zero();
}