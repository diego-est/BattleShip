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
    auto g_button = Graphic{play_text, play_attrs, std::make_pair(6, 35)};
    auto o_button = Graphic{menu_text, menu_attrs, std::make_pair(10, 35)};
    auto e_button = Graphic{exit_text, exit_attrs, std::make_pair(14, 35)};

    auto graphics = std::vector<Graphic *>{&logo, &g_button, &o_button, &e_button};

    /* player logic */
    auto p1 = Player("Gerald");
    auto p2 = Player("Simon");

    /* game loop */
    auto active_button = 1u;
    auto last_button = 1u;
    while (auto ch = getch())
    {
        /* show graphics */
        for (const auto &g : graphics)
            show(*g);

        /* handle keyboard events */
        auto key_press = parse_key(ch);
        switch (key_press)
        {
        case KeyPress::Illegal:
            goto exit;
            break;

        case KeyPress::Up:
            active_button = active_button == 1 ? 3 : active_button - 1;
            break;

        case KeyPress::Down:
            active_button = active_button == 3 ? 1 : active_button + 1;
            break;

        case KeyPress::Enter:
            /* launch active_button */
            switch (active_button)
            {
            case 1:
                start_game(p1, p2);
                break;

            case 2:
                open_options();
                break;

            case 3:
                key_press = KeyPress::q;
            }
            break;

        case KeyPress::Left:
            break;

        case KeyPress::Right:
            break;

        case KeyPress::h:
            show_help();
            break;

        case KeyPress::q:
            goto exit;
            break;

        case KeyPress::r:
            break;
        }

        /* button change logic */
        graphics.at(last_button)->swap_attributes(A_BLINK, A_DIM);
        graphics.at(active_button)->swap_attributes(A_DIM, A_BLINK);
        last_button = active_button;
    }

exit:

    endwin();
    refresh();

    return 0;
}
