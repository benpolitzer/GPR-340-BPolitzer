#include "WindRule.h"
#include <imgui.h>
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f WindRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {

  return Vector2f::Vector2(std::cos(windAngle), std::sin(windAngle));
}

bool WindRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valueHasChanged = false;

  if (ImGui::SliderAngle("Wind Direction", &windAngle, 0)) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}