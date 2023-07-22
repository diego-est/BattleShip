/* ========================================================================
 *
 *     Filename:  classes.cpp
 *  Description:  classes for main.cpp
 *      Version:  0.0.1
 *
 * ======================================================================== */
#include "classes.h"

#include <curses.h>

#include "functions.h"

ExitButton::ExitButton(Graphic* g) { graph = g; }

OptionsButton::OptionsButton(Graphic* g) { graph = g; }

GameButton::GameButton(Graphic* g) { graph = g; }
/*
// enum to represent currently open set of windows
enum Group {
  Menu,
  Game,
};

 holds information about the current Mode of the program
// class Mode

holds information about the current state of a single board
class Board {
  std::vector<int> primary;
  std::vector<int> track;

 public:
  size_t size;

  // constructor
  Board() {
    size = 10;
    primary.reserve(size * size);
    std::fill(primary.begin(), primary.end(), 1);
    track.reserve(size * size);
    std::fill(track.begin(), track.end(), 0);
  }
};

holds information about the current state of a ship
class Ship {
  int hp;
  std::vector<bool> hits;

 public:
  std::string horizontal;
  std::string vertical;
};
*/
