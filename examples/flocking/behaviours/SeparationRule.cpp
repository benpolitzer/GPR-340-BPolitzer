#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  float desiredDistance = desiredMinimalDistance;
  if (!neighborhood.empty()) {
    for (auto i : neighborhood) {
      // Ignore itself
      if (i->getPosition().x == boid->getPosition().x && i->getPosition().y == boid->getPosition().y) {
        continue;
      }

      Vector2f dir = {boid->getPosition().x - i->getPosition().x , boid->getPosition().y - i->getPosition().y};
      float dist = sqrt(dir.x * dir.x + dir.y * dir.y);
      dir = dir.normalized();
      if (desiredMinimalDistance >= dist) {
        continue;
      }
      Vector2f hat = {dir.x / dist, dir.y / dist};
      float strength = 1.5 / dist;
      separatingForce.x += hat.x * strength;
      separatingForce.y += hat.y * strength;
    }
  }
  //separatingForce = Vector2f::normalized(separatingForce);

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
