#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  // The desired minimal distance the boid should maintain from its neighbors
  float desiredDistance = desiredMinimalDistance;

  // If there are boids in the neighborhood, compute the separating force
  if (!neighborhood.empty()) {
    for (auto i : neighborhood) {
      // Ignore the current boid
      if (i->getPosition().x == boid->getPosition().x && i->getPosition().y == boid->getPosition().y) {
        continue;
      }

      // Calculate the direction vector from the current boid to the neighbor boid
      Vector2f dir = {boid->getPosition().x - i->getPosition().x , 
          boid->getPosition().y - i->getPosition().y};
      
      // Compute the Euclidean distance between the two boids
      float dist = sqrt(dir.x * dir.x + dir.y * dir.y);

      // Skip this neighbor if it's within the desired minimal distance
      if (desiredMinimalDistance >= dist) {
        continue;
      }

      // Normalize the direction vector to get the unit vector
      Vector2f unit = {dir.x / dist, dir.y / dist};

      // Compute the separating force, inversely proportional to the distance
      float strength = 1.5 / dist;

      // Accumulate the weighted separating force in the respective direction
      separatingForce.x += unit.x * strength;
      separatingForce.y += unit.y * strength;
    }
  }
  // Normalize the accumulated cohesive force to make sure it has a unit magnitude
  separatingForce = Vector2f::normalized(separatingForce);

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
