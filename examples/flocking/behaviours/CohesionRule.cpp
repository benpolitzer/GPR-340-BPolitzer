#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();
  if (!neighborhood.empty()) {
    for (auto i : neighborhood) {
      // Ignore itself
      if (i->getPosition().x == boid->getPosition().x && i->getPosition().y == boid->getPosition().y) {
        continue;
      }

      Vector2f dir = {i->getPosition().x - boid->getPosition().x , i->getPosition().y - boid->getPosition().y};
      float dist = sqrt(dir.x * dir.x + dir.y * dir.y);
      if (1.0f >= dist) {
        continue;
      }
      Vector2f hat = {dir.x / dist, dir.y / dist};
    }
  }
  separatingForce = Vector2f::normalized(separatingForce);

  return separatingForce;
}