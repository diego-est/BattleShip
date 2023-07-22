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
#include <iostream>
#include "ncurses.h"

class Graphic {
  public:
  WINDOW* win;
  std::vector<const char *> graphic;
  std::vector<int> attrs;
  std::pair<int, int> coords;
};

struct Event;

class AbstractButton {
  public:
  Graphic* graph;
  virtual void action() = 0;
};

class ExitButton : public AbstractButton {
  public:
    Graphic* graph;
    void action() override {
      endwin();
      refresh();
      std::cout << "exited succesfully" << std::endl;
      exit(0);
    }
    ExitButton(Graphic*);

};
class OptionsButton : public AbstractButton {
  public:
    Graphic* graph;
    void action() override {
      std::cout << "opened options" << std::endl;
    }
    OptionsButton(Graphic*);
};

class GameButton : public AbstractButton {
  public:
    Graphic* graph;
    void action() override {
            std::cout << "opened game" << std::endl;
    }
    GameButton(Graphic*);
};

// Base class
/*
class Base {
  std::vector<window> windows;

  public:
  Base(window window);
  void show();
  void add(window window);
};
*/

#endif
