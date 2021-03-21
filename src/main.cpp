#include <iostream>
#include "main.h"
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {

  Renderer renderer;
  Controller controller;
  Game game;
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "You've reached level: " << game.GetLevel() << "\n";
  return 0;
}