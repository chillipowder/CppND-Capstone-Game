#include "player.h"
#include <cmath>
#include <iostream>

void Player::Update(std::vector<std::unique_ptr<Obstacle>> const &obstacles) {

    // Wrap the Player around to the beginning if going off of the screen.
  head_x = fmod(head_x + kScreenWidth, kScreenWidth);
  head_y = fmod(head_y + kScreenHeight, kScreenHeight);

  //check if the player has died by checking if player and obstacle planes overlap 
  head_rx = head_x + 20; 
  head_ry = head_y + 20; 
  //std::cout << head_ry << " " << head_rx << " " << head_y << " " << head_x << " player \n";
  for (auto &obs : obstacles) {
    //std::cout << obs.pos_x << "\n";
    float pos_rx = obs->GetX() + 40; // später austauschen oder direkt in obstacle unterbringen
    float pos_ry = obs->GetY() + 40;
    //std::cout << obs.pos_y << " " << obs.pos_x << " " << pos_ry << " " << pos_rx << " obstacle \n";
    if (!(head_ry <= obs->GetY() || head_rx <= obs->GetX() || head_y >= pos_ry || head_x >= pos_rx))
      alive = false; 
  }
}


//TODO: body entfernen und head umschreiben 
// Inefficient method to check if cell is occupied by player.
bool Player::PlayerCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  
  return false;
}