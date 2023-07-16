/* ========================================================================
 *
 *     Filename:  classes.cpp
 *  Description:  classes for main.cpp
 *      Version:  0.0.1
 *
 * ======================================================================== */
#include "classes.h"

class State {
  std::vector<std::pair<char, int>> keybinds;
};

class Game {
  State mode;
};

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

class Ship {
  int hp;
  std::vector<bool> hits;

public:
  std::string horizontal;
  std::string vertical;
};
