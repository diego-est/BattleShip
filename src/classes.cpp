/* ========================================================================
 *
 *     Filename:  classes.cpp
 *  Description:  classes for main.cpp
 *      Version:  0.0.1
 *
 * ======================================================================== */
#include "classes.h"

#include <curses.h>

#include <algorithm>
#include <span> // c++20 stuff
#include <string>

#include "functions.h"

namespace ra = std::ranges;

/* ==================== Graphic class definitions ==================== */
/* === graphic constructors === */
/* default */
Graphic::Graphic ()
{
  this->text = std::vector<const char *>{ "" };
  this->attributes = std::vector<unsigned int>{};
  this->coords = { 0, 0 };
}

/* span, span, std::pair */
Graphic::Graphic (std::span<const char *> text, std::span<unsigned int> attributes, std::pair<size_t, size_t> coords)
{
  this->text.assign (text.begin (), text.end ());
  this->attributes.assign (attributes.begin (), attributes.end ());
  this->coords = coords;
}

/* span, span, size_t, size_t */
Graphic::Graphic (std::span<const char *> text, std::span<unsigned int> attributes, size_t rows, size_t cols)
{
  this->text.assign (text.begin (), text.end ());
  this->attributes.assign (attributes.begin (), attributes.end ());
  this->coords = { rows, cols };
}

/* initializer_list, initializer_list, std::pair */
Graphic::Graphic (std::initializer_list<const char *> text, std::initializer_list<unsigned int> attributes, std::pair<size_t, size_t> coords)
{
  this->text.assign (text.begin (), text.end ());
  this->attributes.assign (attributes.begin (), attributes.end ());
  this->coords = coords;
}

/* initializer_list, initializer_list, size_t, size_t */
Graphic::Graphic (std::initializer_list<const char *> text, std::initializer_list<unsigned int> attributes, size_t rows, size_t cols)
{
  this->text.assign (text.begin (), text.end ());
  this->attributes.assign (attributes.begin (), attributes.end ());
  this->coords = { rows, cols };
}

/* === graphic non-modifying member functions === */
[[nodiscard]] auto
Graphic::get_text () const -> std::vector<const char *>
{
  return text;
}

[[nodiscard]] auto
Graphic::get_attributes () const -> std::vector<unsigned int>
{
  return attributes;
}

[[nodiscard]] auto
Graphic::get_coords () const -> std::pair<size_t, size_t>
{
  return coords;
}

/* function to display a graphic using its internal state */
auto
Graphic::show () const -> void
{
  for (const auto &a : this->get_attributes ())
    attron (a);

  auto i = 0lu;
  for (const auto &l : this->get_text ())
    {
      mvwprintw (stdscr, this->get_coords ().first + i, this->get_coords ().second, "%s", l);
      i++;
    }

  for (const auto &a : this->get_attributes ())
    attroff (a);

  refresh ();
}

/* === graphic modifying member functions === */
auto
Graphic::set_text (std::span<const char *> text) -> void
{
  this->text.assign (text.begin (), text.end ());
}

auto
Graphic::set_text (std::vector<const char *> text) -> void
{
  this->text = text;
}

auto
Graphic::set_attributes (std::span<unsigned int> attributes) -> void
{
  this->attributes.assign (attributes.begin (), attributes.end ());
}

auto
Graphic::set_attributes (std::vector<unsigned int> attributes) -> void
{
  this->attributes = attributes;
}

auto
Graphic::set_coords (size_t rows, size_t cols) -> void
{
  this->coords = { rows, cols };
}

auto
Graphic::set_coords (std::pair<size_t, size_t> coords) -> void
{
  this->coords = coords;
}

// TODO: test remove_attribute
/* removes a specific attribute from its vector of attributes */
auto
Graphic::remove_attribute (unsigned int attribute) -> void
{
  auto f = this->attributes.begin ();
  auto l = this->attributes.end ();
  // static_cast<void>() to discard return value from std::remove()
  static_cast<void> (std::remove (f, l, attribute));
}

/* simply pushes an attribute into its attribute vector */
auto
Graphic::add_attribute (unsigned int attribute) -> void
{
  this->attributes.push_back (attribute);
}

/* swaps a specific attribute with another attribute in its attribute vector */
auto
Graphic::swap_attributes (unsigned int old_attribute, unsigned int new_attribute) -> void
{
  ra::replace (this->attributes, old_attribute, new_attribute);
}

/* ==================== Ship class definitions ==================== */
/* === ship constructors === */
/* default */
Ship::Ship ()
{
  this->vertical = std::vector<const char *>{};
  this->horizontal = std::vector<const char *>{};
  this->attributes = std::vector<unsigned int>{};
  this->coords = { 0, 0 };
  this->orientation = Vertical;
}

/* vector, vector, vector, std::pair, orientation */
Ship::Ship (std::vector<const char *> vertical, std::vector<const char *> horizontal, std::vector<unsigned int> attributes, std::pair<int, int> coords, Orientation orientation = Vertical)
{
  this->vertical = vertical;
  this->horizontal = horizontal;
  this->attributes = attributes;
  this->coords = coords;
  this->orientation = orientation;
}

/* initializer_list, initializer_list, initializer_list, size_t, size_t */
Ship::Ship (std::initializer_list<const char *> vertical, std::initializer_list<const char *> horizontal, std::initializer_list<unsigned int> attributes, size_t rows, size_t cols,
            Orientation orientation = Vertical)
{
  this->vertical.assign (vertical.begin (), vertical.end ());
  this->horizontal.assign (horizontal.begin (), horizontal.end ());
  this->attributes.assign (attributes.begin (), attributes.end ());
  this->coords = { rows, cols };
  this->orientation = orientation;
}

/* initializer_list, initializer_list, initializer_list, std::pair, Orientation */
Ship::Ship (std::initializer_list<const char *> vertical, std::initializer_list<const char *> horizontal, std::initializer_list<unsigned int> attributes, std::pair<size_t, size_t> coords,
            Orientation orientation = Vertical)
{
  this->vertical.assign (vertical.begin (), vertical.end ());
  this->horizontal.assign (horizontal.begin (), horizontal.end ());
  this->attributes.assign (attributes.begin (), attributes.end ());
  this->coords = coords;
  this->orientation = orientation;
}

/* std::pair, initializer_list, size_t, size_t, Orientation */
Ship::Ship (std::pair<std::initializer_list<const char *>, std::initializer_list<const char *> > skin_pair, size_t rows, size_t cols, Orientation orientation = Vertical)
{
  this->horizontal.assign (skin_pair.first.begin (), skin_pair.first.end ());
  this->vertical.assign (skin_pair.second.begin (), skin_pair.second.end ());
  this->attributes = std::vector<unsigned int>{ A_BOLD };
  this->coords = { rows, cols };
  this->orientation = orientation;
}

/* === ship non-modifying member functions === */
[[nodiscard]] auto
Ship::get_vert () const -> std::vector<const char *>
{
  return this->vertical;
}

[[nodiscard]] auto
Ship::get_horz () const -> std::vector<const char *>
{
  return this->horizontal;
}

[[nodiscard]] auto
Ship::get_attributes () const -> std::vector<unsigned int>
{
  return attributes;
}

[[nodiscard]] auto
Ship::get_coords () const -> std::pair<size_t, size_t>
{
  return coords;
}

/* shows its internal state */
auto
Ship::show () const -> void
{

  auto lines = this->vertical;
  if (this->orientation == Horizontal)
    lines = this->horizontal;

  for (const auto &a : this->get_attributes ())
    attron (a);

  std::cout << lines.size () << "   " << std::endl;

  auto i = 0lu;
  for (const auto &l : lines)
    {
      mvwprintw (stdscr, this->get_coords ().first + i, this->get_coords ().second, "%s\n", l);
      i++;
    }

  for (const auto &a : this->get_attributes ())
    attroff (a);

  refresh ();
}

/* === ship modifying member functions === */
auto
Ship::set_coords (size_t rows, size_t cols) -> void
{
  this->coords = { rows, cols };
}

auto
Ship::set_orientation (Orientation orientation) -> void
{
  this->orientation = orientation;
}

auto
Ship::set_skin (std::pair<std::span<const char *>, std::span<const char *> > skin_pair) -> void
{
  this->horizontal.assign (skin_pair.first.begin (), skin_pair.first.end ());
  this->vertical.assign (skin_pair.second.begin (), skin_pair.second.end ());
}

/* ==================== Player class definitions ==================== */
/* === player constructors === */
/* default */
Player::Player (const char *name)
{
  /* name and skin are always necessary */
  this->name = name;
  this->skin = Skin::Normal;
  this->points = 0;
  this->colors = Colors::Grayscale;
  this->carrier = Ship ({ { "[XXXXXXX]" }, { "M", "X", "X", "X", "W" } }, 0, 0);
  this->battleship = Ship ({ { "<&&&&&>" }, { "A", "&", "&", "V" } }, 0, 0);
  this->destroyer = Ship ({ { "[===>" }, { "M", "H", "V" } }, 0, 0);
  this->submarine = Ship ({ { "(@}" }, { "n", "U" } }, 0, 0);
  this->patrol = Ship ({ { "{:}" }, { "^", "V" } }, 0, 0);

  this->init_positions ();
}

/* === player non-modifying member getter functions === */
[[nodiscard]] auto
Player::get_name () const -> std::string
{
  return name;
}

[[nodiscard]] auto
Player::get_skin () const -> Skin
{
  return skin;
}

[[nodiscard]] auto
Player::get_points () const -> unsigned int
{
  return points;
}

/* show a specific ship in the player's hand */
auto
Player::show (ShipName name) const -> void
{
  switch (name)
    {
    case Carrier:
      this->carrier.show ();
      break;

    case Battleship:
      this->battleship.show ();
      break;

    case Destroyer:
      this->destroyer.show ();
      break;

    case Submarine:
      this->submarine.show ();
      break;

    case Patrol:
      this->patrol.show ();
      break;
    }
}

/* show all the ships in the player's hand */
auto
Player::show_ships () const -> void
{
  this->carrier.show ();
  this->battleship.show ();
  this->destroyer.show ();
  this->submarine.show ();
  this->patrol.show ();
}

/* === player modifying member setter functions === */
auto
Player::set_name (std::string name) -> void
{
  this->name = name;
}

auto
Player::set_skin (Skin skin) -> void
{
  this->skin = skin;
}

auto
Player::set_points (unsigned int points) -> void
{
  this->points = points;
}

/* initial positions of all the ships */
auto
Player::init_positions () -> void
{
  this->carrier.set_coords (10, 15);
  this->battleship.set_coords (10, 20);
  this->destroyer.set_coords (10, 25);
  this->submarine.set_coords (10, 30);
  this->patrol.set_coords (10, 35);
}

/* updates the Player skin cache */
// TODO: find a way to store const char * in a way that doesn't butcher the text
auto
Player::update_skin_cache () -> void
{
  /* Carrier */
  const auto carrier
      = std::unordered_map<Skin, std::pair<std::initializer_list<const char *>, std::initializer_list<const char *> > >{ { Skin::Normal, { { "[XXXXXXX]" }, { "M", "X", "X", "X", "W" } } },
                                                                                                                         { Skin::Donuts, { { "TODO" }, { "T", "O", "D", "O" } } } };

  /* Battleship */
  const auto battleship = std::unordered_map<Skin, std::pair<std::initializer_list<const char *>, std::initializer_list<const char *> > >{ { Skin::Normal, { { "<&&&&&>" }, { "A", "&", "&", "V" } } },
                                                                                                                                           { Skin::Donuts, { { "TODO" }, { "T", "O", "D", "O" } } } };

  /* Destroyer */
  const auto destroyer = std::unordered_map<Skin, std::pair<std::initializer_list<const char *>, std::initializer_list<const char *> > >{ { Skin::Normal, { { "[===>" }, { "M", "H", "V" } } },
                                                                                                                                          { Skin::Donuts, { { "TODO" }, { "T", "O", "D", "O" } } } };

  /* Submarine */
  const auto submarine = std::unordered_map<Skin, std::pair<std::initializer_list<const char *>, std::initializer_list<const char *> > >{ { Skin::Normal, { { "(@}" }, { "n", "U" } } },
                                                                                                                                          { Skin::Donuts, { { "TODO" }, { "T", "O", "D", "O" } } } };

  /* Patrol */
  const auto patrol = std::unordered_map<Skin, std::pair<std::initializer_list<const char *>, std::initializer_list<const char *> > >{ { Skin::Normal, { { "{:}" }, { "^", "V" } } },
                                                                                                                                       { Skin::Donuts, { { "TODO" }, { "T", "O", "D", "O" } } } };

  /* map of all the ships */
  this->ship_skins.insert ({ ShipName::Carrier, carrier });
  this->ship_skins.insert ({ ShipName::Battleship, battleship });
  this->ship_skins.insert ({ ShipName::Destroyer, destroyer });
  this->ship_skins.insert ({ ShipName::Submarine, submarine });
  this->ship_skins.insert ({ ShipName::Patrol, patrol });
}

/* updates each skin in the class */
// TODO: relies on update_skin_cache() working
auto
Player::update_skins () -> void
{
  this->carrier.set_text (ship_skins.at (ShipName::Carrier).at (this->skin).first);
  this->carrier.set_orientation (Orientation::Vertical);

  this->carrier.set_text (ship_skins.at (ShipName::Carrier).at (this->skin).first);
  this->carrier.set_orientation (Orientation::Vertical);

  this->battleship.set_text (ship_skins.at (ShipName::Battleship).at (this->skin).first);
  this->battleship.set_orientation (Orientation::Vertical);

  this->destroyer.set_text (ship_skins.at (ShipName::Destroyer).at (this->skin).first);
  this->destroyer.set_orientation (Orientation::Vertical);

  this->submarine.set_text (ship_skins.at (ShipName::Submarine).at (this->skin).first);
  this->submarine.set_orientation (Orientation::Vertical);

  this->patrol.set_text (ship_skins.at (ShipName::Patrol).at (this->skin).first);
  this->patrol.set_orientation (Orientation::Vertical);
}
