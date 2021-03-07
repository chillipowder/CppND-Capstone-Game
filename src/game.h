#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>
#include <vector>
#include "main.h"
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "player.h"
#include "obstacle.h"

class Game {
 public:
  Game();
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  //int GetSize() const;

 private:
  int level{0};
  Player player;
  std::vector<std::unique_ptr<Obstacle>> obstacle_vec;

  SDL_Point food;
  SDL_Point food_center;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void CreateObstacles();
  void PlaceFood();
  void Update();
};

#endif