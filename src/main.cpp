/* ========================================================================
 *
 *     Filename:  main.cpp
 *  Description:  BattleShip game
 *      Version:  0.0.1
 *
 * ======================================================================== */
#include <ncurses.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "functions.h"

int main() {
  /* screen setup */
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  validate_screen(stdscr);

  getch();
  endwin();
  refresh();

  return 0;
}
