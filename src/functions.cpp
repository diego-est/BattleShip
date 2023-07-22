/* ========================================================================
 *
 *     Filename:  functions.cpp
 *  Description:  helper functions for main.cpp
 *      Version:  0.0.1
 *
 * ======================================================================== */
#include "functions.h"

#include <algorithm>
#include <vector>

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

// remove attribute ints from attribute vector
void attr_remove(std::vector<int> &attr_vec, int attr) {
  std::cout << "removing..." << std::endl;
  std::erase_if(attr_vec, [&](int x) { return x == attr; });
  std::cout << "removed succesfully" << std::endl;
}

void swap_attrs(std::vector<int> &attr_vec, int old_attr, int new_attr) {
  std::cout << "AAAAAAAAAA" << std::endl;
  std::replace(attr_vec.begin(), attr_vec.end(), old_attr, new_attr);
  std::cout << "BBBBBBBBBB" << std::endl;
}

/* function to display a window at a set position with a set number of
 * attributes
 */
void show(Graphic *graph) {
  // set attributes
  for (const auto &attr : graph->attrs) attron(attr);

  // place characters on graph
  int i = 0;
  for (const auto &graphic : graph->graphic) {
    mvwprintw(graph->win, graph->coords.first + i, graph->coords.second, "%s",
              graphic);
    i++;
  }

  // unset attributes
  for (const auto &attr : graph->attrs) attroff(attr);
}

void close() {
  endwin();
  refresh();
}

char into_game() { return ' '; }

char into_menu() { return ' '; }

char exit_all() {
  std::cout << "help" << std::endl;
  return 'q';
}
