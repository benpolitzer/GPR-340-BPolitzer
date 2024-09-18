#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  for (size_t i = 0; i < world.SideSize(); i++) {
    for (size_t j = 0; j < world.SideSize(); j++) {

        Point2D point(i, j);
        int neighbours = CountNeighbors(world, point);
        // Underpopulation
        if (world.Get(point) && neighbours < 2) {
            world.SetNext(point, false);  
        } 
        // Survives
        else if (world.Get(point) && (neighbours == 2 || neighbours == 3)) {
           world.SetNext(point, true);
        } 
        // Overpopulation
        else if (world.Get(point) && neighbours > 3) {
           world.SetNext(point, false);
        } 
        // Reproduction
        else if (!world.Get(point) && neighbours == 3) {
           world.SetNext(point, true);
        }
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
 
   int sum = 0;

  // Checking cardinal directions
  if (world.Get(point + point.RIGHT)) {
    sum++;
  }
  if (world.Get(point + point.LEFT)) {
    sum++;
  }
  if (world.Get(point + point.UP)) {
    sum++;
  }
  if (world.Get(point + point.DOWN)) {
    sum++;
  }
  // Adding two directions to check diagonal positions
  if (world.Get(point + point.UP + point.RIGHT)) {
    sum++;
  }
  if (world.Get(point + point.UP + point.LEFT)) {
    sum++;
  } 
  if (world.Get(point + point.DOWN + point.RIGHT)) {
    sum++;
  }
  if (world.Get(point + point.DOWN + point.LEFT)) {
    sum++;
  }

  return sum;
}
