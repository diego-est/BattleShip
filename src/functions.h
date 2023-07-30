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

// interface stuff
bool screen_is_valid(int x, int y);

void validate_screen(WINDOW *win);

void show(Graphic&);
#endif
