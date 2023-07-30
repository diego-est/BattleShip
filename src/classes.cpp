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
  clear();
  endwin();
  refresh();
  std::cout << "exited succesfully" << std::endl;
  exit(0);
}

/* OptsButton functionality */
OptsButton::OptsButton(Graphic *g) { graph = g; }
OptsButton::~OptsButton() { std::cout << "Deleted Opts button" << std::endl; };

void OptsButton::action() {
  clear();
  auto max_x = 0;
  auto max_y = 0;
  getmaxyx(stdscr, max_y, max_x);
  auto opts_win = newwin(1, 1, max_y, max_x);
  getmaxyx(opts_win, max_y, max_x);
  auto p1_text =
      std::vector<const char *>{"+-+-+-+-+", "|P|l|a|y|", "+-+-+-+-+"};
  auto p1_attrs = std::vector<unsigned int>{A_BOLD};
  auto logo = Graphic{opts_win, p1_text, p1_attrs, std::make_pair(5, 5)};

  box(opts_win, 0, 0);
  wrefresh(opts_win);
  refresh();

  show(logo);
  wrefresh(opts_win);
  refresh();
  getch();
  delwin(opts_win);
}

/* GameButton functionality */
GameButton::GameButton(Graphic *g) { graph = g; }
GameButton::~GameButton() { std::cout << "Deleted Game button" << std::endl; };

void GameButton::action() { std::cout << "opened game" << std::endl; }
