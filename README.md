# CPPND: Capstone Game 

The purpose of this game is to keep the blue square player alive as long as possible by not hitting any of the orange obstacles. Points are awarded for every second of being alive. Additional points can be gained by collecting the rainbow squares. Level ups are time triggered. After each level up the speed increases and new obstacles might appear. 

## General Structure

The project is divided into several files and classes that take care of the various tasks. 

### main.cpp
The main function creates the necessary renderer, controller and game objects. Those are then used in the Game.Run() loop. 

### game.cpp
The game.cpp file contains the main loop Game.Run() of the Game in which all states are updated.
In addition to calling the individual update functions of the renderer, the controller and the game itself, the mechanism is included to ensure 
that every loop has the time of execution in order to keep the desired frame rate.    
Furthermore level updates including all changes such as new obstacles that come with it are included in the loop. 

### player.cpp
The player.cpp contains all player related methods such as if the player has hit an obstacle or if it has left the screen and needs to be put on the other side of the screen 

### controller.cpp
The controller.cpp method observes the keyboard states and changes the players position accordingly

### renderer.cpp
The renderer file contains all methods that are needed in order to display all objects on the screen 

### obstacle.cpp
In the obstacle.cpp methods the individual obstacle states are managed. 

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Game`.