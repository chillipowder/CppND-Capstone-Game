#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>
#include "SDL.h"
#include "obstacle.h"

class Player {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight, kNormal };

  Player()
      : head_x(kScreenWidth / 2),
        head_y(kScreenHeight / 2) {}

  void Update(std::vector<std::unique_ptr<Obstacle>> const &obstacles);

  bool PlayerCell(int x, int y);

  Direction direction = Direction::kNormal;

  float speed{3.f};
  bool alive{true};
  float head_x;
  float head_y;
  float head_rx; // right lower corner x coord
  float head_ry; // right lower corner y coord
  
 private:

  bool growing{false};

};

#endif