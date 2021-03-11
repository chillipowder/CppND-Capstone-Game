#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>
#include "SDL.h"
#include "player.h"
#include "obstacle.h"

class Renderer {
 public:
  Renderer();
  ~Renderer();

  void Render(Player const player, SDL_Point const &bonus, std::vector<std::shared_ptr<Obstacle>> const &obstacles);
  void UpdateWindowTitle(int score, int fps, int level, std::chrono::seconds playtime);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
};

#endif