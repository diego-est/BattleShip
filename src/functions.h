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

// print helper function
template <class T> void print(T);
// print helper function as above but inserts an endline and clears terminal buffer
template <class T> void println(T);

// interface stuff
void interface();

bool screen_is_valid(int x, int y);

void validate_screen(WINDOW *win);

void show_win(window window);


void attr_remove(std::vector<int>* attr_vec, int attr);
#endif
