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
#include <memory>
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

  /* create main menu graphics */
  std::vector<const char *> logo_text = {
      " _               __        ", "|_) _._|__|_| _ (_ |_ o._  ",
      "|_)(_| |_ |_|(/___)| |||_) ", "                       |   "};
  std::vector<const char *> play_text = {"+-+-+-+-+", "|P|l|a|y|", "+-+-+-+-+"};
  std::vector<const char *> menu_text = {"+-+-+-+-+", "|M|e|n|u|", "+-+-+-+-+"};
  std::vector<const char *> exit_text = {"+-+-+-+-+", "|E|x|i|t|", "+-+-+-+-+"};

  std::vector<int> play_attrs = {A_BLINK};
  std::vector<int> menu_attrs = {A_DIM};
  std::vector<int> exit_attrs = {A_DIM};
  std::vector<int> logo_attrs = {A_BOLD};

  Graphic logo = {stdscr, logo_text, logo_attrs, std::make_pair(1, 26)};
  Graphic play = {stdscr, play_text, play_attrs, std::make_pair(6, 35)};
  Graphic menu = {stdscr, menu_text, menu_attrs, std::make_pair(10, 35)};
  Graphic exit = {stdscr, exit_text, exit_attrs, std::make_pair(14, 35)};

  std::vector<Graphic *> graphics = {&logo, &play, &menu, &exit};

  for (const auto &g : graphics) show(g);
  refresh();

  /* create main menu buttons */
  GameButton g_button(&play);
  OptionsButton o_button(&menu);
  ExitButton e_button(&exit);

  std::vector<AbstractButton *> buttons = {&g_button, &o_button, &e_button};

  /* game loop */
  size_t active_button = 0;
  size_t last_button = 0;
  int ch = getch();
  bool selected = false;
  while (ch != 'q') {
    /* handle keyboard events */
    switch (ch) {
      case KEY_UP:
        if (active_button == 0)
          active_button = 2;
        else {
          active_button--;
        }

        swap_attrs(buttons.at(active_button)->graph->attrs, A_DIM, A_BLINK);
        swap_attrs(buttons.at(last_button)->graph->attrs, A_BLINK, A_DIM);

        break;
      case KEY_DOWN:
        if (active_button == 2)
          active_button = 0;
        else {
          active_button++;
        }
        swap_attrs(buttons.at(active_button)->graph->attrs, A_DIM, A_BLINK);
        swap_attrs(buttons.at(last_button)->graph->attrs, A_BLINK, A_DIM);
        break;
      case 10:
        buttons[active_button]->action();
        break;
    }

    for (const auto &g : graphics) show(g);
    refresh();

    ch = getch();
    last_button = active_button;
  }
  getch();

  endwin();
  refresh();

  return 0;
}
