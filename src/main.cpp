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

int
main ()
{
  /* screen setup */
  initscr ();
  cbreak ();
  curs_set (0);
  keypad (stdscr, TRUE);
  noecho ();
  validate_screen (stdscr);

  /* create main menu graphics */
  const auto logo_text = { " _               __        ", "|_) _._|__|_| _ (_ |_ o._  ", "|_)(_| |_ |_|(/___)| |||_) ", "                       |   " };
  const auto play_text = { "+-+-+-+-+", "|P|l|a|y|", "+-+-+-+-+" };
  const auto menu_text = { "+-+-+-+-+", "|M|e|n|u|", "+-+-+-+-+" };
  const auto exit_text = { "+-+-+-+-+", "|E|x|i|t|", "+-+-+-+-+" };

  const auto logo_attrs = { A_BOLD };
  const auto play_attrs = { A_BLINK };
  const auto menu_attrs = { A_DIM };
  const auto exit_attrs = { A_DIM };

  auto logo = Graphic (logo_text, logo_attrs, 1, 26);
  auto g_button = Graphic (play_text, play_attrs, 6, 35);
  auto o_button = Graphic (menu_text, menu_attrs, 10, 35);
  auto e_button = Graphic (exit_text, exit_attrs, 14, 35);

  const auto graphics = std::vector<Graphic *>{ &logo, &g_button, &o_button, &e_button };

  /* player logic */
  auto p1 = Player ("Geri", newwin (25, 80, 0, 0));
  auto p2 = Player ("Simon", newwin (25, 80, 0, 0));

  /* game loop */
  auto active_button = 1zu;
  auto last_button = 1zu;
  for (const auto &g : graphics)
    g->show ();
  while (const auto ch = getch ())
    {
      /* handle keyboard events */
      const auto key_press = parse_key (ch);
      switch (key_press)
        {
        case KeyPress::Illegal:
          break;

        case KeyPress::Up:
          active_button = std::clamp (active_button - 1, 1zu, 3zu);
          break;

        case KeyPress::Down:
          active_button = std::clamp (active_button + 1, 1zu, 3zu);
          break;

        case KeyPress::Enter:
          /* launch active_button */
          switch (active_button)
            {
            case 1:
              start_game (p1, p2);
              break;

            case 2:
              open_options (p1, p2);
              break;

            case 3:
              goto Exit;
              break;
            }
          break;

        case KeyPress::h:
          show_help ();
          break;

        case KeyPress::q:
          goto Exit;
          break;

        default:
          break;
        }

      /* button change logic */
      graphics.at (last_button)->swap_attributes (A_BLINK, A_DIM);
      graphics.at (active_button)->swap_attributes (A_DIM, A_BLINK);
      last_button = active_button;

      /* show graphics */
      for (const auto &g : graphics)
        g->show ();
    }

Exit:
  clear ();
  mvprintw (12, 30, "Thanks for playing!\n");
  endwin ();
  refresh ();

  return 0;
}
