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
#include <span>
#include <iostream>
#include "ncurses.h"

/* Gameplay skins */
enum Skin {
  Normal,
  Donuts,
  Inverted,
};

/* accepted keyboard events */
enum [[nodiscard]] KeyPress {
  Illegal,
  Up,
  Down,
  Left,
  Right,
  h,
  q,
  r,
  Enter,
};

/* Orientation for ships */
enum Orientation {
  Vertical,
  Horizontal
};

/* class to store various information about text to be displayed */
class Graphic {
  std::vector<const char *> text;
  std::vector<unsigned int> attributes;
  std::pair<size_t, size_t> coords;

  public:
  Graphic(std::span<const char *>, std::span<unsigned int>, std::pair<size_t, size_t>);
  Graphic(std::span<const char *>, std::span<unsigned int>, size_t, size_t);
  Graphic();

  /* non-modifying member functions */
  [[nodiscard]] auto get_text() const -> std::vector<const char *>;
  [[nodiscard]] auto get_attributes() const -> std::vector<unsigned int>;
  [[nodiscard]] auto get_coords() const -> std::pair<size_t, size_t>;

  /* modifying member functions */
  auto remove_attribute(unsigned int) -> void;
  auto add_attribute(unsigned int) -> void;
  auto swap_attributes(unsigned int, unsigned int) -> void;
  auto set_text(std::span<const char *>) -> void;
  auto set_attributes(std::span<unsigned int>) -> void;
  auto set_coords(size_t, size_t) -> void;
  auto set_coords(std::pair<size_t, size_t>) -> void;
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
class AbstractButton : public Graphic {
  public:
    /* the syntax of all time */
    virtual auto action() const -> void = 0;
    AbstractButton(std::span<const char *> text, std::span<unsigned int> attributes, std::pair<size_t, size_t> coords);
    AbstractButton(std::span<const char *> text, std::span<unsigned int> attributes, size_t rows, size_t cols);
    AbstractButton();
};

class Ship : public Graphic {
  std::vector<const char *> vertical;
  std::vector<const char *> horizontal;
  std::vector<unsigned int> attributes;
  std::pair<size_t, size_t> coords;

  public:
  Ship(std::vector<const char *>, std::vector<const char *>, std::vector<unsigned int>, std::pair<int, int>);

  /* non-modifying member functions */
  [[nodiscard]] auto get_vert() const -> std::vector<const char *>;
  [[nodiscard]] auto get_horz() const -> std::vector<const char *>;
  [[nodiscard]] auto get_attributes() const -> std::vector<unsigned int>;
  [[nodiscard]] auto get_coords() const -> std::pair<size_t, size_t>;
  auto show(Orientation) const -> void;

  /* modifying member functions */
  auto remove_attribute(unsigned int) -> void;
  auto add_attribute(unsigned int) -> void;
  auto swap_attributes(unsigned int, unsigned int) -> void;
  auto set_coords(size_t, size_t) -> void;
  auto set_coords(std::pair<size_t, size_t>) -> void;
};

#endif
