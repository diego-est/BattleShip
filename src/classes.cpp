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

/* ExitButton functionality */
ExitButton::ExitButton(Graphic *g) { graph = g; }
ExitButton::~ExitButton() { std::cout << "Deleted Exit button" << std::endl; };

void ExitButton::action() {
  endwin();
  refresh();
  std::cout << "exited succesfully" << std::endl;
  exit(0);
}

/* OptsButton functionality */
OptsButton::OptsButton(Graphic *g) { graph = g; }
OptsButton::~OptsButton() { std::cout << "Deleted Opts button" << std::endl; };

void OptsButton::action() { std::cout << "opened options" << std::endl; }

/* GameButton functionality */
GameButton::GameButton(Graphic *g) { graph = g; }
GameButton::~GameButton() { std::cout << "Deleted Game button" << std::endl; };

void GameButton::action() { std::cout << "opened game" << std::endl; }
