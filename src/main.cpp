/* ========================================================================
 *
 *     Filename:  main.cpp
 *  Description:  BattleShip game
 *      Version:  0.0.1
 *
 * ======================================================================== */
#include "functions.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

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

int main() {
  Board board;
  Ship carrier;
  carrier.horizontal = "[XXXXXXX]";
  carrier.vertical = "MXXXW";

  // interface

  const char *logo = "\t\t _               __        \n"
                     "\t\t|_) _._|__|_| _ (_ |_ o._  \n"
                     "\t\t|_)(_| |_ |_|(/___)| |||_) \n"
                     "\t\t                       |   \n";
  const char *info =
      "\033[0;40mHit \033[1;31mr\033[0;40m to reset, "
      "\033[1;31ml\033[0;40m to load "
      "scores file, \033[1;31mh\033[0;40m for help              "
      "                                                \033[0m\n";

  std::vector<std::string> tracking = {
      "0000000000", "0000000000", "0000000000", "0000000000", "0000000000",
      "0000000000", "0000000000", "0000000000", "0000000000", "0000000000"};

  std::cout << logo;
  for (const auto &s : tracking)
    println(s);
  std::cout << info;

  return 0;
}
