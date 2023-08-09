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
// TODO: update values as screen gets resized
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
      mvwprintw (stdscr, graph.get_coords ().first + i, graph.get_coords ().second, "%s", l);
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
  // TODO: add help menu
}

/* this is the actual game */
auto
start_game ([[maybe_unused]] Player &p1, [[maybe_unused]] Player &p2) -> void
{
  clear ();

  auto primary_text = { "    Primary Grid   ", "  A B C D E F G H I J", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
  auto primary_attrs = { A_NORMAL };
  auto primary_labels = Graphic (primary_text, primary_attrs, 2, 10);

  auto tracking_text = { "   Tracking Grid   ", "  A B C D E F G H I J", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
  auto tracking_attrs = { A_NORMAL };
  auto tracking_labels = Graphic (tracking_text, tracking_attrs, 2, 50);

  auto board_text = { ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .",
                      ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . ." };

  auto board_attrs = { A_DIM };
  auto board_primary = Graphic (board_text, board_attrs, 4, 12);
  auto board_tracking = Graphic (board_text, board_attrs, 4, 52);

  auto labels = { primary_labels, tracking_labels, board_primary, board_tracking };

  // TODO: show labels for each ship
  for (const auto &l : labels)
    l.show ();

  p1.show_ships ();

  box (stdscr, 0, 0);
  refresh ();

  getch ();
  clear ();
}

/* validates a screen size */
// TODO: update values as screen gets resized
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
