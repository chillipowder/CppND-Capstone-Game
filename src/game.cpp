#include "game.h"
#include <iostream>
#include "SDL.h"
#include <unistd.h>


Game::Game()
    : player(),
      engine(dev()),
      random_w(0, static_cast<int>(kScreenHeight -1)),
      random_h(0, static_cast<int>(kScreenHeight -1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  
  //create initial obstacles 
  CreateObstacles();
  auto level_timestamp = std::chrono::system_clock::now();

  while (running) {
    frame_start = SDL_GetTicks();
    //std::cout <<"test ob der scheiß flüssiger läuft \n";
    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, player);
    Update();
    renderer.Render(player, food, obstacle_vec);

    // update level and create new obstacles after fixed period of time  
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> diff = now - level_timestamp;
    if (diff.count() > 10 * 1000) {
      std::cout << "leveling up \n";
      level++;
      CreateObstacles();
      level_timestamp = std::chrono::system_clock::now();
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    /*if (frame_duration > 10) {
      std::cout << frame_duration << "\n";
    }*/
    if (frame_duration < target_frame_duration) {
      //std::cout <<"delaying \n";
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::CreateObstacles() {
  switch (level) {
    case 0:
      std::cout << "case 0 \n";
      for(int i = 0; i < 8; i++) {
        std::unique_ptr<Obstacle> flo (new FirstLvlObs(i * 1200 + 1000, std::chrono::system_clock::now()));
        obstacle_vec.emplace_back(std::move(flo));
      }
      break;
    case 1:
      std::cout << "case 1 \n";
      for(int i = 0; i < 8; i++) {
        std::unique_ptr<Obstacle> flo (new FirstLvlObs(i * 1200 + 1000, std::chrono::system_clock::now()));
        obstacle_vec.emplace_back(std::move(flo));
      }
      for (auto &obs : obstacle_vec) {
        obs.get()->IncreaseSpeed(1.5);
      }
      player.speed *= 1.1;
      break;
    case 2:
      std::cout << "case 2 \n";
      for(int i = 0; i < 3; i++) {
        std::unique_ptr<Obstacle> flo (new NextLvlObs(i * 3000 + 1000, std::chrono::system_clock::now()));
        obstacle_vec.emplace_back(std::move(flo));
      }
      player.speed *= 1.1;
      break;
  }

}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a player item before placing
    // food.
    if (!player.PlayerCell(x, y)) {
      food.x = x;
      food.y = y;
      food_center.x = x + 10;
      food_center.y = y + 10;
      return;
    }
  }
}

void Game::Update() {
  if (!player.alive) return;

  player.Update(obstacle_vec);

  //updating Obstacles
  for(auto &obs : obstacle_vec) 
  {
    //std::cout << "game vector size: " << obstacle_vec.size() << "\n";
    //if(obs.pos_x == 2) std::cout << obs.pos_y << "\n";
    obs->Update();
    //std::cout << obs->pos_x << " " << obs->pos_y << "\n";
    //std::cout << obs.speed << "\n";
  }

  // Check if there's food over here
  if (player.head_x < food_center.x && player.head_rx > food_center.x && player.head_y < food_center.y && player.head_ry > food_center.y)
  {
    score++;
    PlaceFood();
    //nach jedem bonus punkt die geschwindigkeit de obstacles erhöhen? 
  }
}

int Game::GetScore() const { return score; }
//int Game::GetSize() const { return player.size; }