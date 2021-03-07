#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Player Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, kScreenWidth,
                                kScreenHeight, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Player const player, SDL_Point const &food, std::vector<std::unique_ptr<Obstacle>> const &obstacles) {
  SDL_Rect block;
  SDL_Rect obstacle_block;
  block.w = kScreenWidth / kGridWidth;
  block.h = kScreenHeight / kGridHeight;
  obstacle_block.w = (kScreenWidth / kGridWidth) * 2;
  obstacle_block.h = (kScreenHeight / kGridHeight) * 2;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);/*
  block.x = food.x * block.w; 
  block.y = food.y * block.h;*/
  block.x = food.x; 
  block.y = food.y;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render obstacles
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x80, 0x00, 0xFF);
  for(auto &obs : obstacles)  {
    //std::cout << obs.pos_x << " obs pos x \n";
    /*
    obstacle_block.x = obs.pos_x * (obstacle_block.w / 2);
    obstacle_block.y = obs.pos_y * (obstacle_block.h / 2);*/
    obstacle_block.x = obs->GetX() ;
    obstacle_block.y = obs->GetY() ;
    SDL_RenderFillRect(sdl_renderer, &obstacle_block);
  }

  // Render player's body
  /*
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : player.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }*/

  // Render player's head
  // player is on a 32x32 grid whereas the screen is a 640² grid. the x val can only accept vals btw 0-31 and must therefore be multiplied by 32 (width||height)
  // in order to be placed correctly on screen.
  //block.x = static_cast<int>(player.head_x) * block.w; // old vintage look 
  //block.y = static_cast<int>(player.head_y) * block.h;
  /*
  block.x = player.head_x * block.w; //smooth sailing with floats
  block.y = player.head_y * block.h;*/
  block.x = player.head_x; //smooth sailing with floats
  block.y = player.head_y;
  if (player.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Player Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
