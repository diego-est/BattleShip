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
#include <utility>
#include <vector>

#include "classes.h"

/* checks if screen is valid */
// TODO: update values as screen gets resized
[[nodiscard]] auto screen_is_valid(std::pair<std::size_t, std::size_t> size) -> bool
{
    return (size.first >= 25 && size.second >= 80);
}

/* validates a screen size */
auto validate_screen(WINDOW *win) -> void
{
    auto y = getmaxy(win);
    auto x = getmaxx(win);
    auto size = std::make_pair(y, x);

    while (!screen_is_valid(size))
    {
        printw("Terminal screen too small.\n"
               "Minimum size must be 80 columns, 25 rows.\n"
               "Your screen is %d columns, %d rows.\n"
               "Press any key to retry.\n\n",
               size.first, size.second);
        refresh();
        mvgetch(0, 0);
        clear();
        getmaxyx(win, y, x);
    }

    refresh();
}

/* function to display a window at a set position with a set number of
 * attributes
 */
auto show(Graphic &graph) -> void
{
    // set attributes
    for (const auto &a : graph.get_attributes())
        attron(a);

    // place characters on graph
    auto i = 0lu;
    for (const auto &l : graph.get_text())
    {
        mvwprintw(stdscr, graph.get_coords().first + i, graph.get_coords().second, "%s", l);
        i++;
    }

    // unset attributes
    for (const auto &a : graph.get_attributes())
        attroff(a);

    refresh();
}

auto show_help() -> void
{
    // TODO: add help menu
}

/* key parser */
[[nodiscard]] auto parse_key(int ch) -> KeyPress
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

/* this is the actual game */
auto start_game([[maybe_unused]] Player player_1, [[maybe_unused]] Player player_2) -> void
{
    clear();

    auto p1_primary_text = std::vector<const char *>{"    Primary Grid   ", "  A B C D E F G H I J", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    auto p1_primary_attrs = std::vector<unsigned int>{A_NORMAL};
    auto p1_primary_labels = Graphic{p1_primary_text, p1_primary_attrs, std::make_pair(2, 10)};

    auto p1_tracking_text = std::vector<const char *>{"   Tracking Grid   ", "  A B C D E F G H I J", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    auto p1_tracking_attrs = std::vector<unsigned int>{A_NORMAL};
    auto p1_tracking_labels = Graphic{p1_tracking_text, p1_tracking_attrs, std::make_pair(2, 50)};

    auto board_text = std::vector<const char *>{". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .",
                                                ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . ."};
    auto board_attrs = std::vector<unsigned int>{A_DIM};
    auto board_primary = Graphic{board_text, board_attrs, std::make_pair(4, 12)};
    auto board_tracking = Graphic{board_text, board_attrs, std::make_pair(4, 52)};

    auto carrier_horz = std::vector<const char *>{"[XXXXXXX]"};
    auto carrier_vert = std::vector<const char *>{"M", "X", "X", "X", "W"};
    auto carrier_attrs = std::vector<unsigned int>{A_BOLD};
    auto carrier = Ship(carrier_vert, carrier_horz, carrier_attrs, std::make_pair(16, 15));

    auto battleship_horz = std::vector<const char *>{"<&&&&&>"};
    auto battleship_vert = std::vector<const char *>{"A", "&", "&", "V"};
    auto battleship_attrs = std::vector<unsigned int>{A_BOLD};
    auto battleship = Ship(battleship_vert, battleship_horz, battleship_attrs, std::make_pair(16, 25));

    auto destroyer_horz = std::vector<const char *>{"[===>"};
    auto destroyer_vert = std::vector<const char *>{"M", "H", "V"};
    auto destroyer_attrs = std::vector<unsigned int>{A_BOLD};
    auto destroyer = Ship(destroyer_vert, destroyer_horz, destroyer_attrs, std::make_pair(16, 35));

    auto submarine_horz = std::vector<const char *>{"(@)"};
    auto submarine_vert = std::vector<const char *>{"n", "U"};
    auto submarine_attrs = std::vector<unsigned int>{A_BOLD};
    auto submarine = Ship(submarine_vert, submarine_horz, submarine_attrs, std::make_pair(16, 45));

    auto patrol_horz = std::vector<const char *>{"{:}"};
    auto patrol_vert = std::vector<const char *>{"^", "V"};
    auto patrol_attrs = std::vector<unsigned int>{A_BOLD};
    auto patrol = Ship(patrol_vert, patrol_horz, patrol_attrs, std::make_pair(16, 55));

    box(stdscr, 0, 0);
    refresh();

    // TODO: show labels for each ship
    show(p1_primary_labels);
    show(p1_tracking_labels);
    show(board_primary);
    show(board_tracking);
    carrier.show(Vertical);
    battleship.show(Vertical);
    destroyer.show(Vertical);
    submarine.show(Vertical);
    patrol.show(Vertical);
    refresh();

    getch();
    clear();
}

/* game settings page */
auto open_options() -> void
{
    clear();
    auto max_x = 0;
    auto max_y = 0;
    getmaxyx(stdscr, max_y, max_x);
    auto opts_win = newwin(1, 1, max_y, max_x);
    getmaxyx(opts_win, max_y, max_x);

    auto p1_text = std::vector<const char *>{"   ___  __                    ___", "  / _ \\/ /__ ___ _____ ____  <  /", " / ___/ / _ `/ // / -_) __/  / / ", "/_/  /_/\\_,_/\\_, /\\__/_/    /_/  ",
                                             "            /___/                "};

    auto p1_attrs = std::vector<unsigned int>{A_NORMAL};

    auto p1 = Graphic{p1_text, p1_attrs, std::make_pair(5, 5)};

    box(stdscr, 0, 0);
    wrefresh(opts_win);
    refresh();

    show(p1);
    wrefresh(opts_win);
    refresh();
    getch();
    delwin(opts_win);
    clear();
}
