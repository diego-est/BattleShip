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
#include <map>
#include <iostream>
#include "ncurses.h"

/* =========== enums =========== */
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
  s,
  Enter = 10,
  a,
  b,
  c,
  d,
  e,
  f,
  g,
  i,
  j,
  k,
  l,
  m,
  n,
  o,
  p,
  t,
  u,
  v,
  w,
  x,
  y,
  z,
};

/* Orientation for ships */
enum Orientation {
  Vertical,
  Horizontal
};

/* Name for ships */
enum ShipName {
  Carrier,
  Battleship,
  Destroyer,
  Submarine,
  Patrol,
};


/* =================== class to store various information about text to be displayed =================== */
class Graphic {
  std::vector<const char *> text;
  std::vector<unsigned int> attributes;
  std::pair<size_t, size_t> coords;

  public:
  /* constructors */
  Graphic(std::span<const char *>, std::span<unsigned int>, std::pair<size_t, size_t>);
  Graphic(std::span<const char *>, std::span<unsigned int>, size_t, size_t);
  Graphic(std::initializer_list<const char *> text, std::initializer_list<unsigned int> attributes, size_t rows, size_t cols);
  Graphic(std::initializer_list<const char *> text, std::initializer_list<unsigned int> attributes, std::pair<size_t, size_t> coords);
  Graphic();

  /* non-modifying member functions */
  [[nodiscard]] auto get_text() const -> std::vector<const char *>;
  [[nodiscard]] auto get_attributes() const -> std::vector<unsigned int>;
  [[nodiscard]] auto get_coords() const -> std::pair<size_t, size_t>;
  auto show() const -> void;

  /* modifying member functions */
  auto remove_attribute(unsigned int) -> void;
  auto add_attribute(unsigned int) -> void;
  auto swap_attributes(unsigned int, unsigned int) -> void;
  auto set_text(std::span<const char *>) -> void;
  auto set_attributes(std::span<unsigned int>) -> void;
  auto set_coords(size_t, size_t) -> void;
  auto set_coords(std::pair<size_t, size_t>) -> void;
};


/* =================== class to store text information and ship information =================== */
class Ship : public Graphic {
  std::vector<const char *> vertical;
  std::vector<const char *> horizontal;
  std::vector<unsigned int> attributes;
  std::pair<size_t, size_t> coords;

  public:
  /* constructors */
  Ship();
  Ship(std::vector<const char *>, std::vector<const char *>, std::vector<unsigned int>, std::pair<int, int>);
  Ship(std::initializer_list<const char *> vertical, std::initializer_list<const char *> horizontal, std::initializer_list<unsigned int> attributes, std::pair<size_t, size_t> coords);
  Ship(std::initializer_list<const char *> vertical, std::initializer_list<const char *> horizontal, std::initializer_list<unsigned int> attributes, size_t rows, size_t cols);
  Ship(std::pair<std::initializer_list<const char *>, std::initializer_list<const char *>> skin_pair, size_t rows, size_t cols);

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
  auto set_skin(std::pair<std::span<const char *>, std::span<const char *>> skin_pair) -> void;
};


/* =================== player class (one for each player, two total) =================== */
class Player {
  std::string name;
  Skin skin;
  unsigned int points;
  Ship carrier;
  Ship battleship;
  Ship destroyer;
  Ship submarine;
  Ship patrol;
  std::map<ShipName, std::map<Skin, std::pair< std::initializer_list<const char *>, std::initializer_list<const char *>>>> ship_skins;

  public:
  /* constructors */
  Player(const char *name, Skin skin = Skin::Normal);

  /* non-modifying member functions */
  [[nodiscard]] auto get_name() const -> std::string;
  [[nodiscard]] auto get_skin() const -> Skin;
  [[nodiscard]] auto get_points() const -> unsigned int;

  /* modifying member functions */
  auto set_name(std::string) -> void;
  auto set_skin(Skin) -> void;
  auto set_points(unsigned int) -> void;
  auto update_skin_cache() -> void;
};

#endif
