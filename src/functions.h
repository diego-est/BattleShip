/* ========================================================================
 *
 *     Filename:  functions.cpp
 *  Description:  helper functions for main.cpp
 *      Version:  0.0.1
 *
 * ======================================================================== */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include <iostream>

// print helper function
template <class T> void print(T e) { std::cout << e; }
// print helper function as above but inserts an endline and clears terminal buffer
template <class T> void println(T e) { std::cout << e << std::endl; }
#endif
