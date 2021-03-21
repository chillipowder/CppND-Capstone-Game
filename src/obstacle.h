#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include "main.h"

class Obstacle {
  public:
    virtual void Update() = 0;
    virtual float GetX() = 0;
    virtual float GetY() = 0;
    virtual void SetX(float f) = 0;
    virtual void IncreaseSpeed(float f) = 0;
    
};

class FirstLvlObs : public Obstacle {
  public:
    FirstLvlObs(int start_time, std::chrono::time_point<std::chrono::system_clock> timestamp)
      : start_time(start_time),
        timestamp(timestamp) {}

    void Update();
    float GetX() {return pos_x;};
    float GetY() {return pos_y;};
    void SetX(float f) {pos_x = f;};
    void IncreaseSpeed(float f) {speed *= f;};

    inline static std::vector<int> obstacle_pos; //static member (globale) Variable für Überblick wo ein Obstacle gesetzt werden kann das von oben kommt 
    float speed{1.f};
    float pos_x{-1}; 
    float pos_y{-40}; // positions the obstacle right above the window (assuming obstacle = 2x2 square)
    int start_time; // in ms
    std::chrono::time_point<std::chrono::system_clock> timestamp;

  private:
   
};

class NextLvlObs : public Obstacle {
  public:
    NextLvlObs(int start_time, std::chrono::time_point<std::chrono::system_clock> timestamp)
    : start_time(start_time), 
      timestamp(timestamp) {}
    void Update();
    float GetX() {return pos_x;};
    float GetY() {return pos_y;};
    void SetX(float f) {pos_x = f;};
    void IncreaseSpeed(float f) {speed *= f;};


    float speed{3.f};
    float pos_x{-40};
    float pos_y{-1};
    int start_time; // in ms
    std::chrono::time_point<std::chrono::system_clock> timestamp;
};

class Wall : public Obstacle {
  public:
    Wall(int start_time, std::chrono::time_point<std::chrono::system_clock> timestamp)
    : start_time(start_time), 
      timestamp(timestamp) {}
    void Update();
    float GetX() {return pos_x;};
    float GetY() {return pos_y;};
    void SetX(float f) {pos_x = f;};
    void IncreaseSpeed(float f) {speed *= f;};

    bool blocked{false};
    inline static std::vector<std::shared_ptr<Wall>> blocks;
    float speed{1.5f};
    float pos_x{0};
    float pos_y{-40};
    int start_time; // in ms
    std::chrono::time_point<std::chrono::system_clock> timestamp;
};
#endif