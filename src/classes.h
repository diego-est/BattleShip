/* ========================================================================
 *
 *     Filename:  classes.h
 *  Description:  class declarations for main.cpp
 *      Version:  0.0.1
 *
 * ======================================================================== */

#ifndef CLASSES_H_
#define CLASSES_H_
#include <vector>
#include <string>
#include <iostream>
#include "ncurses.h"

/* Gameplay skins */
enum Skin {
  Normal,
  Donuts,
  Inverted,
};

/* class to store various information about text to be displayed */
class Graphic {
  std::vector<const char *> text;
  std::vector<unsigned int> attributes;
  std::pair<int, int> coords;

  public:
  Graphic(std::vector<const char *>, std::vector<unsigned int>, std::pair<int, int>);

  /* non-modifying member functions */
  auto get_text() const -> std::vector<const char *>;
  auto get_attributes() const -> std::vector<unsigned int>;
  auto get_coords() const -> std::pair<int, int>;

  /* modifying member functions */
  auto remove_attribute(unsigned int) -> void;
  auto add_attribute(unsigned int) -> void;
  auto swap_attributes(unsigned int, unsigned int) -> void;
};

/* player class */
class Player {
  std::string name;
  Skin skin;
  unsigned int points;

  public:
  Player(const char *name);

  /* non-modifying member functions */
  auto get_name() const -> std::string;
  auto get_skin() const -> Skin;
  auto get_points() const -> unsigned int;

  /* modifying member functions */
  auto set_name(std::string) -> void;
  auto set_skin(Skin) -> void;
  auto set_points(unsigned int) -> void;
};

/* Button abstract class (to be derived) */
class AbstractButton {
  Graphic * graph;
  public:
    auto get_graph() const -> Graphic *;
    /* the syntax of all time */
    virtual auto action() const -> void = 0;
};

/* main menu exit button */
class ExitButton : public AbstractButton {
    Graphic * graph;
  public:
    auto action() const -> void override;
    ExitButton(Graphic *);
    ~ExitButton();

};

/* settings button */
class OptsButton : public AbstractButton {
    Graphic * graph;
  public:
    auto action() const -> void override;
    auto show_player(Player player) const -> void;
    OptsButton(Graphic *);
    ~OptsButton();
};

/* game button */
class GameButton : public AbstractButton {
    Graphic * graph;
  public:
    auto action() const -> void override;
    GameButton(Graphic *);
    ~GameButton();
};

#endif
