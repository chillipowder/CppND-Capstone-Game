#include <iostream>
#include "main.h"
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {

  //Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Renderer renderer;
  Controller controller;
  //Game game(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Game game;
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  //std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}