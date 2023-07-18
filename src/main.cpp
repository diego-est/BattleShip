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

#include "classes.h"
#include "functions.h"

int main() {
  /* screen setup */
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  validate_screen(stdscr);

  std::vector<const char *> title = {
      " _               __        ", "|_) _._|__|_| _ (_ |_ o._  ",
      "|_)(_| |_ |_|(/___)| |||_) ", "                       |   "};

  std::vector<const char *> play_text = {"+-+-+-+-+", "|P|l|a|y|", "+-+-+-+-+"};
  std::vector<const char *> menu_text = {"+-+-+-+-+", "|M|e|n|u|", "+-+-+-+-+"};
  std::vector<const char *> exit_text = {"+-+-+-+-+", "|E|x|i|t|", "+-+-+-+-+"};

  std::vector<int> play_attrs = {A_BLINK};
  std::vector<int> menu_attrs = {A_DIM};
  std::vector<int> exit_attrs = {A_DIM};
  std::vector<int> logo_attrs = {A_BOLD};

  window logo = {stdscr, title, logo_attrs, std::make_pair(1, 26)};

  window play_button = {stdscr, play_text, play_attrs, std::make_pair(6, 35)};
  window menu_button = {stdscr, menu_text, menu_attrs, std::make_pair(10, 35)};
  window exit_button = {stdscr, exit_text, exit_attrs, std::make_pair(14, 35)};

  Base menu = logo;

  menu.add(play_button);
  menu.add(menu_button);
  menu.add(exit_button);

  menu.show();

  refresh();

  // window buttons[3] = {play_button, menu_button, exit_button};

  // int active_button = 0;
  // int last_button;

  // int ch = getch();
  // while (ch != 'q') {
  //   last_button = active_button;
  //   switch (ch) {
  //     case KEY_UP:
  //       active_button = active_button == 2 ? 0 : active_button + 1;
  //       break;
  //     case KEY_DOWN:
  //       active_button = active_button == 0 ? 2 : active_button - 1;
  //       break;
  //   }

  //  attr_remove(&buttons[last_button].attrs, A_BLINK);
  //  buttons[last_button].attrs.push_back(A_DIM);

  //  attr_remove(&buttons[active_button].attrs, A_DIM);
  //  buttons[active_button].attrs.push_back(A_BLINK);

  //  menu.show();
  //  refresh();
  //  ch = getch();
  //}
  getch();
  endwin();
  refresh();

  return 0;
}
