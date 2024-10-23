#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  //Call generatePath function to find a path to catch the cat
  std::vector<Point2D> path = generatePath(world);
  //Move to the first point on the path if new point is valid
  if (path.size() > 0) return path.front();

  auto side = world->getWorldSideSize() / 2;
  for (;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  }
}
