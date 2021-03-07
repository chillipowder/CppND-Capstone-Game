#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "player.h"
/*
void Controller::ChangeDirection(Player &player, Player::Direction input,
                                 Player::Direction opposite) const {
  if (player.direction != opposite || player.size == 1) player.direction = input;
  return;
}*/

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
/*
void Controller::HandleInput(bool &running, Player &player) const {
  SDL_Event e;
  const Uint8 *keyboardstate = SDL_GetKeyboardState(NULL);
  if (keyboardstate[SDL_SCANCODE_UP]) std::cout << "Up" << "\n";
  while (SDL_PollEvent(&e)) {
    //if (keyboardstate[SDLK_UP]) std::cout << "Up" << "\n";
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          player.head_y--;                     
          break;

        case SDLK_DOWN:
          player.head_y++;
          break;

        case SDLK_LEFT:
          player.head_x--;
          break;

        case SDLK_RIGHT:
          player.head_x++;
          break;
      }
    }
  }
}
*/