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
  curs_set(0);
  keypad(stdscr, TRUE);
  noecho();
  validate_screen(stdscr);

  /* create main menu graphics */
  auto logo_text = std::vector<const char *>{
      " _               __        ", "|_) _._|__|_| _ (_ |_ o._  ",
      "|_)(_| |_ |_|(/___)| |||_) ", "                       |   "};
  auto play_text =
      std::vector<const char *>{"+-+-+-+-+", "|P|l|a|y|", "+-+-+-+-+"};
  auto menu_text =
      std::vector<const char *>{"+-+-+-+-+", "|M|e|n|u|", "+-+-+-+-+"};
  auto exit_text =
      std::vector<const char *>{"+-+-+-+-+", "|E|x|i|t|", "+-+-+-+-+"};

  auto play_attrs = std::vector<unsigned int>{A_BLINK};
  auto menu_attrs = std::vector<unsigned int>{A_DIM};
  auto exit_attrs = std::vector<unsigned int>{A_DIM};
  auto logo_attrs = std::vector<unsigned int>{A_BOLD};

  auto logo = Graphic{stdscr, logo_text, logo_attrs, std::make_pair(1, 26)};
  auto play = Graphic{stdscr, play_text, play_attrs, std::make_pair(6, 35)};
  auto menu = Graphic{stdscr, menu_text, menu_attrs, std::make_pair(10, 35)};
  auto exit = Graphic{stdscr, exit_text, exit_attrs, std::make_pair(14, 35)};

  auto graphics = std::vector<Graphic *>{&logo, &play, &menu, &exit};

  /* show graphics */
  for (const auto &g : graphics) show(*g);

  /* create main menu buttons */
  auto g_button = GameButton{&play};
  auto o_button = OptsButton{&menu};
  auto e_button = ExitButton{&exit};

  auto buttons =
      std::vector<AbstractButton *>{&(g_button), &(o_button), &(e_button)};

  /* game loop */
  auto active_button = 0z;
  auto ch = getch();
  while (ch != 'q') {
    /* handle keyboard events */
    switch (ch) {
      case KEY_UP:
        active_button = active_button == 0 ? 2 : active_button - 1;
        break;
      case KEY_DOWN:
        active_button = active_button == 2 ? 0 : active_button + 1;
        break;
      case 10:
        buttons.at(active_button)->action();
        break;
    }

    /* THIS IS SO HORRID */
    /* TODO: find a way to compact this */
    switch (active_button) {
      case 0:
        std::ranges::replace(o_button.graph->attrs, A_BLINK, A_DIM);
        std::ranges::replace(e_button.graph->attrs, A_BLINK, A_DIM);

        std::ranges::replace(g_button.graph->attrs, A_DIM, A_BLINK);
        break;
      case 1:
        std::ranges::replace(g_button.graph->attrs, A_BLINK, A_DIM);
        std::ranges::replace(e_button.graph->attrs, A_BLINK, A_DIM);

        std::ranges::replace(o_button.graph->attrs, A_DIM, A_BLINK);
        break;
      case 2:
        std::ranges::replace(g_button.graph->attrs, A_BLINK, A_DIM);
        std::ranges::replace(o_button.graph->attrs, A_BLINK, A_DIM);

        std::ranges::replace(e_button.graph->attrs, A_DIM, A_BLINK);
        break;
    }

    /* show graphics */
    for (const auto &g : graphics) show(*g);

    ch = getch();
  }

  endwin();
  refresh();

  return 0;
}
