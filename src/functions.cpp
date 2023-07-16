/* ========================================================================
 *
 *     Filename:  functions.cpp
 *  Description:  helper functions for main.cpp
 *      Version:  0.0.1
 *
 * ======================================================================== */
#include "functions.h"

// template print
template <typename T> void print(T e) { std::cout << e; }

// template print, also clears stdout buffer
template <typename T> void println(T e) { std::cout << e << std::endl; }

// prints basic interface
void interface() {
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
}

// checks if screen is valid
bool screen_is_valid(int x, int y) { return (x >= 80 && y >= 25); }

void validate_screen(WINDOW *win) {
  int y, x;
  getmaxyx(win, y, x);

  while (!screen_is_valid(x, y)) {
    printw("Terminal screen too small.\n"
           "Minimum size must be 80 columns, 25 rows.\n"
           "Your screen is %d columns, %d rows.\n"
           "Hit enter to retry.\n\n",
           x, y);
    refresh();
    getch();
    getmaxyx(win, y, x);
  }

  refresh();
}
