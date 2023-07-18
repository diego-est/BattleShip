/* ========================================================================
 *
 *     Filename:  functions.cpp
 *  Description:  helper functions for main.cpp
 *      Version:  0.0.1
 *
 * ======================================================================== */
#include "functions.h"

#include <algorithm>

#include "classes.h"

/* template print */
template <typename T>
void print(T e) {
  std::cout << e;
}

/* template print, also clears stdout buffer */
template <typename T>
void println(T e) {
  std::cout << e << std::endl;
}

/* checks if screen is valid */
bool screen_is_valid(int x, int y) { return (x >= 80 && y >= 25); }

/* validates a screen size */
void validate_screen(WINDOW *win) {
  int y, x;
  getmaxyx(win, y, x);

  while (!screen_is_valid(x, y)) {
    printw(
        "Terminal screen too small.\n"
        "Minimum size must be 80 columns, 25 rows.\n"
        "Your screen is %d columns, %d rows.\n"
        "Press any key to retry.\n\n",
        x, y);
    refresh();
    getch();
    getmaxyx(win, y, x);
  }

  refresh();
}

// remove attributes from attribute vector
void attr_remove(std::vector<int> *attr_vec, int attr) {
  auto item_pos = std::find(attr_vec->begin(), attr_vec->end(), attr);

  if (item_pos != attr_vec->end()) attr_vec->erase(item_pos);
}

/* function to display a window at a set position with a set number of
 * attributes */
void show_win(window window) {
  // set attributes
  for (const auto &attr : window.attrs) attron(attr);

  // place characters on window
  int i = 0;
  for (const auto &graphic : window.graphic) {
    mvwprintw(window.win, window.coords.first + i, window.coords.second, "%s",
              graphic);
    i++;
  }

  // unset attributes
  for (const auto &attr : window.attrs) attroff(attr);
}
