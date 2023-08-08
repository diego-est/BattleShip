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

/* === lambda templates === */
auto print = [](const auto& e) { std::cout << e; };
auto println = [](const auto& e) { std::cout << e << std::endl; };

/* open settings page */
auto open_options(Player &, Player &) -> void;

/* key parser */
[[nodiscard]] auto parse_key(const int ch) -> KeyPress;

/* screen check */
[[nodiscard]] auto screen_is_valid(const size_t x, const size_t y) -> bool;

/* show a graphic entity */
auto show(const Graphic &) -> void;

/* help page */
auto show_help() -> void;

/* this is the game */
auto start_game(Player &, Player &) -> void;

/* validates a specific screen size */
auto validate_screen(const WINDOW *win) -> void;

#endif
