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
template <typename T> void print(T e);

// print helper function as above but inserts an endline and clears terminal buffer
template <typename T> void println(T e);

// interface stuff
void interface();

bool screen_is_valid(int x, int y);

void validate_screen(WINDOW *win);

void show(Graphic*);

char into_game();

char into_menu();

char exit_all();
#endif
