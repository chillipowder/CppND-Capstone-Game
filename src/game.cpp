#include "game.h"
#include <iostream>
#include "SDL.h"
#include <unistd.h>


Game::Game()
    : player(),
      engine(dev()),
      random_w(0, static_cast<int>(kScreenHeight -1)),
      random_h(0, static_cast<int>(kScreenHeight -1)) {
  PlaceBonus();
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

  //timestamps for leveling up and time counter 
  auto level_timestamp = std::chrono::system_clock::now();
  auto play_time = std::chrono::system_clock::now();
  std::chrono::seconds playtime;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, player);
    Update();
    renderer.Render(player, bonus, obstacle_vec);

    // update level and create new obstacles after fixed period of time  
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> diff = now - level_timestamp;
    if (diff.count() > 15 * 1000 && player.alive) {
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
      if(player.alive) {
        std::chrono::duration<double, std::milli> diff = now - play_time;
        playtime = std::chrono::duration_cast<std::chrono::seconds>(diff); 
        score++;
      }
      renderer.UpdateWindowTitle(score, frame_count, level, playtime);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::CreateObstacles() {
  switch (level) {
    case 0:
      //std::cout << "case 0 \n";
      for(int i = 0; i < 8; i++) {
        std::unique_ptr<Obstacle> flo (new FirstLvlObs(i * 1200 + 1000, std::chrono::system_clock::now()));
        obstacle_vec.emplace_back(std::move(flo));
      }
      break;
    case 1:
      //std::cout << "case 1 \n";
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
      for(int i = 0; i < 8; i++) {
        obstacle_vec[i].get()->IncreaseSpeed(1.2);
      }
      break;
    case 3:
      //std::cout << "case 3 \n";
      for(int i = 0; i < 3; i++) {
        std::unique_ptr<Obstacle> flo (new NextLvlObs(i * 3000 + 1000, std::chrono::system_clock::now()));
        obstacle_vec.emplace_back(std::move(flo));
      }
      player.speed *= 1.1;
      break;
    /*
    case 4:
      std::cout << "case 4 \n";
      for(int i = 0; i < 16; i++) {
        std::shared_ptr<Obstacle> flo (new Wall(1, std::chrono::system_clock::now()));
        obstacle_vec.emplace_back(std::move(flo));
      }
      break;*/
    default:
      //std::cout << "default case \n";
      for(auto &obs : obstacle_vec)
      {
        obs->IncreaseSpeed(1.25);//1.5
      }
      player.speed *= 1.1;//1.2
      break;
  }

}

void Game::PlaceBonus() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a player item before placing
    // bonus.
    if (!player.PlayerCell(x, y)) {
      bonus.x = x;
      bonus.y = y;
      bonus_center.x = x + 10;
      bonus_center.y = y + 10;
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
    obs->Update();
  }

  // Check if there's bonus over here
  if (player.head_x < bonus_center.x && player.head_rx > bonus_center.x && player.head_y < bonus_center.y && player.head_ry > bonus_center.y)
  {
    score +=10;
    PlaceBonus();
  }
}

int Game::GetScore() const { return score; }
int Game::GetLevel() const { return level; }