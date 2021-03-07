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

  void Render(Player const player, SDL_Point const &food, std::vector<std::unique_ptr<Obstacle>> const &obstacles);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  /*
  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;*/
};

#endif