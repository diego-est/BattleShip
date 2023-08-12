/* ========================================================================
 *
 *     Filename:  functions.h
 *  Description:  helper functions for main.cpp header file
 *      Version:  0.0.1
 *
 * ======================================================================== */

#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>
#include "classes.h"

/* === lambda templates === */
auto
print(const auto& e) -> void
{
  std::cout << e;
}

auto
println(const auto& e) -> void
{
  std::cout << e << std::endl;
}

/* open settings page */
auto open_options([[maybe_unused]] Player &, [[maybe_unused]] Player &) -> void;

/* key parser */
[[nodiscard]] auto parse_key(const int ch) -> KeyPress;

/* screen check */
[[nodiscard]] auto screen_is_valid(const int rows, const int cols) -> bool;

/* show a graphic entity */
[[deprecated]] auto show(const Graphic &) -> void;

/* help page */
auto show_help() -> void;

/* this is the game */
auto start_game([[maybe_unused]] Player &, [[maybe_unused]] Player &) -> void;

/* validates a specific screen size */
auto validate_screen(const WINDOW *win) -> void;
