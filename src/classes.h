/* ========================================================================
 *
 *     Filename:  classes.h
 *  Description:  class declarations for main.cpp
 *      Version:  0.0.1
 *
 * ======================================================================== */

#pragma once
#include <vector>
#include <string>
#include <span>
#include <unordered_map>
#include <iostream>
#include "ncurses.h"

/* === enums === */
/* Gameplay skins */
enum Skin {
  Normal,
  Donuts,
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
  Submarine_1,
  Submarine_2,
  Patrol_1,
  Patrol_2
};

/* Colorschemes for skins */
enum Colors {
  Inverted,
  Grayscale,
};

/* Whether a specific part of a ship is hit or not */
enum Hit : bool {
  Ok,
  Damage,
};


/* ====== graphic class declaration ====== */
class Graphic {
  /* === member fields === */
  WINDOW *win;
  std::vector<const char *> text;
  std::vector<unsigned int> attributes;
  std::pair<size_t, size_t> coords;
  public:
  /* === constructors === */
  Graphic();
  Graphic(std::span<const char *>, std::span<unsigned int>, std::pair<size_t, size_t>, WINDOW* win = stdscr);
  Graphic(std::span<const char *>, std::span<unsigned int>, size_t, size_t, WINDOW*win = stdscr);
  Graphic(std::initializer_list<const char *> text, std::initializer_list<unsigned int> attributes, std::pair<size_t, size_t> coords, WINDOW *win);
  Graphic(std::initializer_list<const char *> text, std::initializer_list<unsigned int> attributes, size_t rows, size_t cols, WINDOW *win = stdscr);


  /* === non-modifying member functions === */
  [[nodiscard]] auto get_win() const -> WINDOW *;
  [[nodiscard]] auto get_text() const -> std::vector<const char *>;
  [[nodiscard]] auto get_attributes() const -> std::vector<unsigned int>;
  [[nodiscard]] auto get_coords() const -> std::pair<size_t, size_t>;
  auto show() const -> void;


  /* === modifying member functions === */
  auto set_win(WINDOW *) -> void;
  auto set_text(std::span<const char *>) -> void;
  auto set_text(std::initializer_list<const char *>) -> void;
  auto set_attributes(std::span<unsigned int>) -> void;
  auto set_attributes(std::initializer_list<unsigned int>) -> void;
  auto set_coords(size_t, size_t) -> void;
  auto remove_attribute(unsigned int) -> void;
  auto add_attribute(unsigned int) -> void;
  auto swap_attributes(unsigned int, unsigned int) -> void;

};

/* =================== ship class declaration =================== */
class Ship : public Graphic {
  /* === member fields === */
  WINDOW *win;
  std::vector<const char *> vertical;
  std::vector<const char *> horizontal;
  std::vector<unsigned int> attributes;
  std::pair<size_t, size_t> coords;
  Orientation orientation;
  std::vector<Hit> hits;
  size_t size;
  public:
  /* === constructors === */
  Ship();
  Ship(std::span<const char *>, std::span<const char *>, std::span<unsigned int>, std::pair<size_t, size_t>, Orientation orientation = Orientation::Vertical);
  Ship(std::span<const char *>, std::span<const char *>, std::span<unsigned int>, size_t, size_t, Orientation orientation = Orientation::Vertical);
  Ship(std::initializer_list<const char *>, std::initializer_list<const char *>, std::initializer_list<unsigned int>, size_t, size_t, Orientation orientation = Orientation::Vertical);
  Ship(std::initializer_list<const char *>, std::initializer_list<const char *>, std::initializer_list<unsigned int>, std::pair<size_t, size_t>, Orientation orientation = Orientation::Vertical);
  Ship(std::pair<std::span<const char *>, std::span<const char *>>, size_t, size_t, Orientation orientation = Orientation::Vertical);
  Ship(std::pair<std::initializer_list<const char *>, std::initializer_list<const char *>>, size_t, size_t, Orientation orientation = Orientation::Vertical);


  /* === non-modifying member functions === */
  [[nodiscard]] auto get_vert() const -> std::vector<const char *>;
  [[nodiscard]] auto get_horz() const -> std::vector<const char *>;
  [[nodiscard]] auto get_orient() const -> Orientation;
  [[nodiscard]] auto get_hp() const -> long;
  auto show() const -> void;


  /* === modifying member functions === */
  auto set_skin(std::span<const char *>, std::span<const char *>) -> void;
  auto set_skin(std::initializer_list<const char *>, std::initializer_list<const char *>) -> void;
  auto set_skin(std::pair<std::span<const char *>, std::span<const char *>>) -> void;
  auto set_orientation (Orientation) -> void;
};


/* =================== player class declaration =================== */
class Player {
  /* === member fields === */
  WINDOW *win;
  std::string name;
  Skin skin;
  Colors colors;
  unsigned int points;
  Ship carrier;
  Ship battleship;
  Ship destroyer;
  Ship submarine_1;
  Ship submarine_2;
  Ship patrol_1;
  Ship patrol_2;
  std::unordered_map<ShipName, std::unordered_map<Skin, std::pair< std::initializer_list<const char *>, std::initializer_list<const char *>>>> ship_skins;
  public:
  /* === constructors === */
  Player(const char *name, WINDOW *win = stdscr);


  /* === non-modifying member functions === */
  [[nodiscard]] auto get_win() const -> WINDOW *;
  [[nodiscard]] auto get_name() const -> std::string;
  [[nodiscard]] auto get_skin() const -> Skin;
  [[nodiscard]] auto get_colors() const -> Colors;
  [[nodiscard]] auto get_points() const -> unsigned int;
  [[nodiscard]] auto get_ship(ShipName) const -> Ship;
  auto show(ShipName) const -> void;
  auto show_ships() const -> void;
  auto show_ships_status() const -> void;
  auto info_ships() const -> void;
  auto show_boards() const -> void;


  /* === modifying member functions === */
  auto set_win(WINDOW *) -> void;
  auto set_name(std::string) -> void;
  auto set_skin(Skin) -> void;
  auto set_points(unsigned int) -> void;
  auto init_positions() -> void;
  auto ship_coords(ShipName, size_t, size_t) -> void;
  auto ship_orient(ShipName, Orientation) -> void;
  auto place_ship(ShipName) -> void;
};
