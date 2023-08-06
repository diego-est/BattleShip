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

/* checks if screen is valid */
// TODO: update values as screen gets resized
[[nodiscard]] auto screen_is_valid(const std::pair<std::size_t, std::size_t> size) -> bool
{
    return (size.first >= 25 && size.second >= 80);
}

/* validates a screen size */
// TODO: update values as screen gets resized
auto validate_screen(const WINDOW *win) -> void
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
               size.second, size.first);
        refresh();
        mvgetch(0, 0);
        clear();
        getmaxyx(win, y, x);
        size = std::make_pair(y, x);
    }

    refresh();
}

/* function to display a window at a set position with a set number of
 * attributes
 */
auto show(const Graphic &graph) -> void
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
[[nodiscard]] auto parse_key(const int ch) -> KeyPress
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

[[nodiscard]] auto ship_skin(const ShipName name, const Skin skin, const Orientation orientation) -> std::vector<const char *>
{
    /* Carrier */
    auto carrier = std::map<Skin, std::pair<const char *, std::vector<const char *>>>{};
    carrier[Skin::Normal] = std::make_pair("[XXXXXXX]", std::vector{"M", "X", "X", "X", "W"});
    carrier[Skin::Donuts] = std::make_pair("TODO", std::vector{"T", "O", "D", "O"});
    carrier[Skin::Inverted] = std::make_pair("[XXXXXXX]", std::vector{"M", "X", "X", "X", "W"});

    /* Battleship */
    auto battleship = std::map<Skin, std::pair<const char *, std::vector<const char *>>>{};
    battleship[Skin::Normal] = std::make_pair("<&&&&&>", std::vector{"A", "&", "&", "V"});
    battleship[Skin::Donuts] = std::make_pair("", std::vector{""});

    /* Destroyer */
    auto destroyer = std::map<Skin, std::pair<const char *, std::vector<const char *>>>{};
    /* Submarine */
    auto submarine = std::map<Skin, std::pair<const char *, std::vector<const char *>>>{};
    /* Patrol */
    auto patrol = std::map<Skin, std::pair<const char *, std::vector<const char *>>>{};

    /* map of all the ships */
    auto mp = std::map<ShipName, std::map<Skin, std::pair<const char *, std::vector<const char *>>>>{};

    switch (orientation)
    {
    case Orientation::Vertical:
        return mp[name][skin].second;
        break;
    case Orientation::Horizontal:
        return std::vector{mp[name][skin].first};
        break;
    }
}

/* this is the actual game */
auto start_game([[maybe_unused]] Player &p1, [[maybe_unused]] Player &p2) -> void
{
    clear();

    auto primary_text = {"    Primary Grid   ", "  A B C D E F G H I J", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    auto primary_attrs = {A_NORMAL};
    auto primary_labels = Graphic(primary_text, primary_attrs, 2, 10);

    auto tracking_text = {"   Tracking Grid   ", "  A B C D E F G H I J", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    auto tracking_attrs = {A_NORMAL};
    auto tracking_labels = Graphic(tracking_text, tracking_attrs, 2, 50);

    auto board_text = {". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .",
                       ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . ."};

    auto board_attrs = {A_DIM};
    auto board_primary = Graphic(board_text, board_attrs, 4, 12);
    auto board_tracking = Graphic(board_text, board_attrs, 4, 52);

    /*
    auto carrier_horz = ship_skin(Carrier, p1.get_skin(), Horizontal);
    auto carrier_vert = ship_skin(Carrier, p1.get_skin(), Vertical);
    auto carrier_attrs = {A_BOLD};
    auto carrier = Ship(carrier_vert, carrier_horz, carrier_attrs, 16, 15);

    auto battleship_horz = ship_skin(Battleship, p1.get_skin(), Horizontal);
    auto battleship_vert = ship_skin(Battleship, p1.get_skin(), Vertical);
    auto battleship_attrs = {A_BOLD};
    auto battleship = Ship(battleship_vert, battleship_horz, battleship_attrs, 16, 25);

    auto destroyer_horz = {"[===>"};
    auto destroyer_vert = {"M", "H", "V"};
    auto destroyer_attrs = {A_BOLD};
    auto destroyer = Ship(destroyer_vert, destroyer_horz, destroyer_attrs, 16, 35);

    auto submarine_horz = {"(@)"};
    auto submarine_vert = {"n", "U"};
    auto submarine_attrs = {A_BOLD};
    auto submarine = Ship(submarine_vert, submarine_horz, submarine_attrs, 16, 45);

    auto patrol_horz = {"{:}"};
    auto patrol_vert = {"^", "V"};
    auto patrol_attrs = {A_BOLD};
    auto patrol = Ship(patrol_vert, patrol_horz, patrol_attrs, 16, 55);
    */

    box(stdscr, 0, 0);
    refresh();

    // TODO: show labels for each ship
    show(primary_labels);
    show(tracking_labels);
    show(board_primary);
    show(board_tracking);
    /*
    carrier.show(Vertical);
    battleship.show(Vertical);
    destroyer.show(Vertical);
    submarine.show(Vertical);
    patrol.show(Vertical);
    */
    refresh();

    getch();
    clear();
}

/* game settings page */
auto open_options(Player &p1, Player &p2) -> void
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

    auto p1_graphic = Graphic{p1_text, p1_attrs, std::make_pair(5, 5)};

    box(stdscr, 0, 0);
    wrefresh(opts_win);
    refresh();

    show(p1_graphic);
    wrefresh(opts_win);
    refresh();
    getch();
    delwin(opts_win);
    clear();
}
