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
auto screen_is_valid(int x, int y) -> bool
{
    return (x >= 80 && y >= 25);
}

/* validates a screen size */
auto validate_screen(WINDOW *win) -> void
{
    int y, x;
    getmaxyx(win, y, x);

    while (!screen_is_valid(x, y))
    {
        printw("Terminal screen too small.\n"
               "Minimum size must be 80 columns, 25 rows.\n"
               "Your screen is %d columns, %d rows.\n"
               "Press any key to retry.\n\n",
               x, y);
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
    auto i = 0;
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
