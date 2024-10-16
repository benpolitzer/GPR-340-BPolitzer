#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {

  if (!stack.empty()) {
    //Current node or top of the stack
    Point2D current = stack.back();

    //Marking current node as visited
    visited[current.x][current.y] = true;
    w->SetNodeColor(current, Color::Red);

    //Gets all visitable neighbors of current node
    std::vector<Point2D> neighbours = getVisitables(w, current);

    //If there exists any unvisited neighbors
    if (neighbours.size() > 0) {
      Point2D target;

      //Choose the neighbor if it is the only one of the current node
      if (neighbours.size() == 1) {
        target = neighbours.front();
      }
      //Choose random neighbors if there are multiple for the current node
      else {
        Random rand;
        target = neighbours[rand.Range(0, neighbours.size() - 1)];
      }
        
      //Left of the current node
      if (target == stack.back().Left()) {
        w->SetWest(stack.back(), false);         //Remove west or east wall
        w->SetEast(stack.back().Left(), false);  
      }
      //Right of the current node
      else if (target == stack.back().Right()) {
        w->SetEast(stack.back(), false);         //Remove west or east wall
        w->SetWest(stack.back().Right(), false);
      }
      //Above the current node
      else if (target == stack.back().Up()) {
        w->SetNorth(stack.back(), false);       // Remove north and south
        w->SetSouth(stack.back().Up(), false);
      }
      //Below the current node
      else if (target == stack.back().Down()) {
        w->SetSouth(stack.back(), false);         // Remove south and north wall
        w->SetNorth(stack.back().Down(), false); 
      }

      //Push target node onto stack to backtrack later
      stack.push_back(target);

      return true;
    }
    //If there are no unvisited neighbors, begin backtracking
    else {
      w->SetNodeColor(stack.back(), Color::Black);  
      stack.pop_back();                             

      return true;
    }
  }
  //If stack is empty, pick a new random starting point
  else {
    stack.push_back(randomStartPoint(w));
  }

  return false;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  ///Check///

  // Left
  if ((p.Left().x >= -sideOver2) && (p.Left().x <= sideOver2) && (p.Left().y <= sideOver2) && (p.Left().y >= -sideOver2)) {
    if (!visited[p.Left().x][p.Left().y]) {
      visitables.push_back(p.Left());
    }
  }
  //Right
  if ((p.Right().x >= -sideOver2) && (p.Right().x <= sideOver2) && (p.Right().y <= sideOver2) && (p.Right().y >= -sideOver2)) {
    if (!visited[p.Right().x][p.Right().y]) {
      visitables.push_back(p.Right());
    }
  }
  //Down
  if ((p.Down().x >= -sideOver2) && (p.Down().x <= sideOver2) && (p.Down().y <= sideOver2) && (p.Down().y >= -sideOver2)) {
    if (!visited[p.Down().x][p.Down().y]) {
      visitables.push_back(p.Down());
    }
  }
  // Up
  if ((p.Up().x >= -sideOver2) && (p.Up().x <= sideOver2) && (p.Up().y <= sideOver2) && (p.Up().y >= -sideOver2)) {
    if (!visited[p.Up().x][p.Up().y]) {
      visitables.push_back(p.Up());
    }
  }

  ///End Check///
  return visitables;  //Returns list of visitable neighbors
}