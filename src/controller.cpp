#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "player.h"


void Controller::HandleInput(bool &running, Player &player) const {
  SDL_Event e;
  if (player.alive) {
    if (keyboardstate[SDL_SCANCODE_UP]) player.head_y -= player.speed;
    if (keyboardstate[SDL_SCANCODE_DOWN]) player.head_y += player.speed;
    if (keyboardstate[SDL_SCANCODE_LEFT]) player.head_x -= player.speed;
    if (keyboardstate[SDL_SCANCODE_RIGHT]) player.head_x += player.speed;
  }
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = false;
      }
    }
}