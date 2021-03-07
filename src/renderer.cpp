#include "renderer.h"
#include <iostream>
#include <string>
#include <random>

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

void Renderer::Render(Player const player, SDL_Point const &bonus, std::vector<std::unique_ptr<Obstacle>> const &obstacles) {
  SDL_Rect block;
  SDL_Rect obstacle_block;
  block.w = kScreenWidth / kGridWidth;
  block.h = kScreenHeight / kGridHeight;
  obstacle_block.w = (kScreenWidth / kGridWidth) * 2;
  obstacle_block.h = (kScreenHeight / kGridHeight) * 2;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render bonus points in always changing colors 
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> uni(0, 255);
  auto rnd_int = uni(rng);
  auto rnd_int2 = uni(rng);
  auto rnd_int3 = uni(rng);

  //SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  SDL_SetRenderDrawColor(sdl_renderer, rnd_int, rnd_int2, rnd_int3, 125);/*
  block.x = bonus.x * block.w; 
  block.y = bonus.y * block.h;*/
  block.x = bonus.x; 
  block.y = bonus.y;
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

void Renderer::UpdateWindowTitle(int score, int fps, int level) {
  std::string title{"Player Score: " + std::to_string(score) + " FPS: " + std::to_string(fps) + " Level: " + std::to_string(level)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
