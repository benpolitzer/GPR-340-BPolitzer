#include "BoundedAreaRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f BoundedAreaRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f force = Vector2f::zero();
  auto windowSize = this->world->engine->window->size();

  // Calculate the distance to each edge
  float leftDist = boid->getPosition().x - desiredDistance;
  float rightDist = (windowSize.x - boid->getPosition().x) - desiredDistance;
  float topDist = boid->getPosition().y - desiredDistance;
  float bottomDist = (windowSize.y - boid->getPosition().y) - desiredDistance;

  // Calculate the force to apply based on distances
  if (leftDist < 0) {
    force.x -= leftDist;  // Push towards the right if too close to the left
  }
  if (rightDist < 0) {
    force.x += rightDist;  // Push towards the left if too close to the right
  }
  if (topDist < 0) {
    force.y -= topDist;  // Push towards the bottom if too close to the top
  }
  if (bottomDist < 0) {
    force.y += bottomDist;  // Push towards the top if too close to the bottom
  }

  return force;
}

bool BoundedAreaRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  auto size = this->world->engine->window->size();
  auto widthWindows = size.x;
  auto heightWindows = size.y;
  bool valueHasChanged = false;

  // We cap the max separation as the third of the min of the width.height
  auto minHeightWidth = std::min(widthWindows, heightWindows);

  if (ImGui::SliderInt("Desired Distance From Borders", &desiredDistance, 0.0f, (int)(minHeightWidth / 3), "%i")) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}

void BoundedAreaRule::draw(const Boid& boid, SDL_Renderer* renderer) const {
  FlockingRule::draw(boid, renderer);
  auto size = this->world->engine->window->size();
  auto dist = (float)desiredDistance;

  // Draw a rectangle on the map
  Polygon::DrawLine(renderer, Vector2f(dist, dist), Vector2f(size.x - dist, dist), Color::Gray);                    // TOP
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, dist), Vector2f(size.x - dist, size.y - dist), Color::Gray);  // RIGHT
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, size.y - dist), Vector2f(dist, size.y - dist), Color::Gray);  // Bottom
  Polygon::DrawLine(renderer, Vector2f(dist, size.y - dist), Vector2f(dist, dist), Color::Gray);                    // LEFT
}