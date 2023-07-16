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
#include <ncurses.h>
#include <string>
#include <vector>

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
