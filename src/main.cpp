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

namespace ra = std::ranges;

int main()
{
    /* screen setup */
    initscr();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    noecho();
    validate_screen(stdscr);

    /* create main menu graphics */
    auto logo_text = std::vector<const char *>{" _               __        ", "|_) _._|__|_| _ (_ |_ o._  ", "|_)(_| |_ |_|(/___)| |||_) ", "                       |   "};
    auto play_text = std::vector<const char *>{"+-+-+-+-+", "|P|l|a|y|", "+-+-+-+-+"};
    auto menu_text = std::vector<const char *>{"+-+-+-+-+", "|M|e|n|u|", "+-+-+-+-+"};
    auto exit_text = std::vector<const char *>{"+-+-+-+-+", "|E|x|i|t|", "+-+-+-+-+"};

    auto play_attrs = std::vector<unsigned int>{A_BLINK};
    auto menu_attrs = std::vector<unsigned int>{A_DIM};
    auto exit_attrs = std::vector<unsigned int>{A_DIM};
    auto logo_attrs = std::vector<unsigned int>{A_BOLD};

    auto logo = Graphic{logo_text, logo_attrs, std::make_pair(1, 26)};
    auto play = Graphic{play_text, play_attrs, std::make_pair(6, 35)};
    auto menu = Graphic{menu_text, menu_attrs, std::make_pair(10, 35)};
    auto exit = Graphic{exit_text, exit_attrs, std::make_pair(14, 35)};

    auto graphics = std::vector<Graphic *>{&logo, &play, &menu, &exit};

    /* show graphics */
    for (const auto &g : graphics)
        show(*g);

    /* create main menu buttons */
    auto g_button = GameButton(&play);
    auto o_button = OptsButton(&menu);
    auto e_button = ExitButton(&exit);

    auto buttons = std::vector<AbstractButton *>{&(g_button), &(o_button), &(e_button)};

    /* game loop */
    auto active_button = 0;
    auto last_button = 0;
    auto ch = getch();
    while (ch != 'q')
    {
        /* handle keyboard events */
        switch (ch)
        {
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
        switch (active_button)
        {
        case 0:
            g_button.get_graph()->swap_attributes(A_DIM, A_BLINK);
            break;
        case 1:
            o_button.get_graph()->swap_attributes(A_DIM, A_BLINK);
            break;
        case 2:

            if (e_button.get_graph() == NULL)
                std::cout << "this is null" << std::endl;
            std::cout << "outside function" << std::endl;
            e_button.get_graph()->remove_attribute(A_DIM);
            std::cout << "before adding";
            e_button.get_graph()->add_attribute(A_BLINK);
            break;
        }
        std::cout << "before last_button" << std::endl;
        switch (last_button)
        {
        case 0:
            g_button.get_graph()->swap_attributes(A_BLINK, A_DIM);
            break;
        case 1:
            o_button.get_graph()->swap_attributes(A_BLINK, A_DIM);
            break;
        case 2:
            e_button.get_graph()->swap_attributes(A_BLINK, A_DIM);
            break;
        }

        /* show graphics */
        for (const auto &g : graphics)
            show(*g);

        last_button = active_button;
        ch = getch();
    }

    endwin();
    refresh();

    return 0;
}
