#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"

class Controller {
 public:
  void HandleInput(bool &running, Player &player) const;

 private:
  
  const Uint8 *keyboardstate = SDL_GetKeyboardState(NULL);
};

#endif