/* ========================================================================
 *
 *     Filename:  functions.cpp
 *  Description:  helper functions for main.cpp
 *      Version:  0.0.1
 *
 * ======================================================================== */
#include "functions.h"

#include <curses.h>

#include <algorithm>
#include <map>
#include <utility>
#include <vector>

#include "classes.h"

/* game settings page */
auto
open_options ([[maybe_unused]] Player &p1, [[maybe_unused]] Player &p2) -> void
{
  clear ();
  auto max_x = 0;
  auto max_y = 0;
  getmaxyx (stdscr, max_y, max_x);
  auto opts_win = newwin (1, 1, max_y, max_x);
  getmaxyx (opts_win, max_y, max_x);

  auto p1_text = std::vector<const char *>{ "   ___  __                    ___", "  / _ \\/ /__ ___ _____ ____  <  /", " / ___/ / _ `/ // / -_) __/  / / ", "/_/  /_/\\_,_/\\_, /\\__/_/    /_/  ",
                                            "            /___/                " };

  auto p1_attrs = std::vector<unsigned int>{ A_NORMAL };

  auto p1_graphic = Graphic (p1_text, p1_attrs, 5, 5);

  box (stdscr, 0, 0);
  wrefresh (opts_win);
  refresh ();

  p1_graphic.show ();
  wrefresh (opts_win);
  refresh ();
  getch ();
  delwin (opts_win);
  clear ();
}

/* key parser */
[[nodiscard]] auto
parse_key (const int ch) -> KeyPress
{
  switch (ch)
    {
    case KEY_UP:
      return KeyPress::Up;
      break;
    case KEY_DOWN:
      return KeyPress::Down;
      break;
    case KEY_LEFT:
      return KeyPress::Left;
      break;
    case KEY_RIGHT:
      return KeyPress::Right;
      break;
    case KEY_ENTER:
    case 10:
      return KeyPress::Enter;
      break;
    case 'h':
      return KeyPress::h;
      break;
    case 'q':
      return KeyPress::q;
      break;
    case 'r':
      return KeyPress::r;
      break;
    default:
      return KeyPress::Illegal;
      break;
    }
}

/* checks if screen is valid */
[[nodiscard]] auto
screen_is_valid (const int rows, const int cols) -> bool
{
  return (rows >= 25 && cols >= 80);
}

/* function to display a window at a set position with a set number of attributes */
[[deprecated]] auto
show (const Graphic &graph) -> void
{
  // set attributes
  for (const auto &a : graph.get_attributes ())
    attron (a);

  // place characters on graph
  auto i = 0lu;
  for (const auto &l : graph.get_text ())
    {
      mvprintw (graph.get_coords ().first + i, graph.get_coords ().second, "%s", l);
      i++;
    }

  // unset attributes
  for (const auto &a : graph.get_attributes ())
    attroff (a);

  refresh ();
}

auto
show_help () -> void
{
  clear ();
  mvprintw (4, 4, "message");
  while (const auto ch = getch ())
    {
      const auto key_press = parse_key (ch);
      switch (key_press)
        {
        case KeyPress::q:
          clear ();
          return;
          break;

        case KeyPress::Up:
          break;

        case KeyPress::Down:
          break;

        case KeyPress::Left:
          break;

        case KeyPress::Right:
          break;

        default:
          break;
        }
    }
  clear ();
}

/* this is the actual game */
auto
start_game (Player &p1, Player &p2) -> void
{
  box (p1.get_win (), 0, 0);
  p1.show_boards ();
  mvwprintw (p1.get_win (), 1, 37, "%u - %u", p1.get_points (), p2.get_points ());
  mvwprintw (p1.get_win (), 2, 33, "Place your ships!");
  wrefresh (p1.get_win ());

  /* place carrier */
  auto row = 4zu;
  auto col = 12zu;
  auto orientation = p1.get_ship (Carrier).get_orient ();
  p1.ship_coords (Carrier, row, col);
  p1.show (Carrier);
  while (const auto ch = getch ())
    {

      const auto key_press = parse_key (ch);
      switch (key_press)
        {
        case KeyPress::Up:
          row = row == 4 ? 4 : row - 1;
          break;

        case KeyPress::Down:
          if (orientation == Vertical)
            row = row == 9 ? 9 : row + 1;
          else
            row = row == 13 ? 13 : row + 1;
          break;

        case KeyPress::Left:
          col = col == 12 ? 12 : col - 2;
          break;

        case KeyPress::Right:
          if (orientation == Horizontal)
            col = col == 22 ? 22 : col + 2;
          else
            col = col == 30 ? 30 : col + 2;
          break;

        case KeyPress::r:
          if (col >= 24 && orientation == Vertical)
            continue;
          else if (row >= 10 && orientation == Horizontal)
            continue;
          else
            orientation = orientation == Vertical ? Horizontal : Vertical;
          break;

        case KeyPress::h:
          show_help ();
          break;

        case KeyPress::q:
          clear ();
          return;
          break;

        case KeyPress::Enter:
          goto NextShip;
          break;

        default:
          break;
        }

      p1.ship_coords (Carrier, row, col);
      p1.ship_orient (Carrier, orientation);
      p1.show_boards ();
      p1.show (Carrier);
      wrefresh (p1.get_win ());
    }
NextShip:
  clear ();
}

/* validates a screen size */
auto
validate_screen (const WINDOW *win) -> void
{
  auto rows = getmaxy (win);
  auto cols = getmaxx (win);

  while (!screen_is_valid (rows, cols))
    {
      printw ("Terminal screen too small.\n"
              "Minimum size must be 80 columns, 25 rows.\n"
              "Your screen is %d rows, %d columns.\n"
              "Press any key to retry.\n\n",
              rows, cols);
      refresh ();
      mvgetch (0, 0);
      clear ();
      getmaxyx (win, rows, cols);
    }

  refresh ();
}
