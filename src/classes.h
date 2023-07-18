/* ========================================================================
 *
 *     Filename:  classes.h
 *  Description:  class declarations for main.cpp
 *      Version:  0.0.1
 *
 * ======================================================================== */

#ifndef CLASSES_H_
#define CLASSES_H_
#include <vector>
#include <string>
#include "ncurses.h"

// window struct
struct window {
  WINDOW* win;
  std::vector<const char *> graphic;
  std::vector<int> attrs;
  std::pair<int, int> coords;
};

// Base class
class Base {
  std::vector<window> windows;

  public:
  Base(window window);
  void show();
  void add(window window);
};

#endif
