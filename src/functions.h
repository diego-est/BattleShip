/* ========================================================================
 *
 *     Filename:  functions.h
 *  Description:  helper functions for main.cpp header file
 *      Version:  0.0.1
 *
 * ======================================================================== */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include <iostream>
#include <vector>
#include <ncurses.h>
#include "classes.h"

/* template print */
auto print = [](const auto& e) { std::cout << e; };
auto println = [](const auto& e) { std::cout << e << std::endl; };

/* screen check */
[[nodiscard]] auto screen_is_valid(size_t x, size_t y) -> bool;

/* validates a specific screen size */
auto validate_screen(WINDOW *win) -> void;

/* show a graphic entity */
auto show(Graphic&) -> void;

/* key parser */
[[nodiscard]] auto parse_key(int ch) -> KeyPress;

/* help page */
auto show_help() -> void;

/* this is the game */
auto start_game(Player, Player) -> void;

/* open settings page */
auto open_options() -> void;

#endif
