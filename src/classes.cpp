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
#include <ranges>
#include <span>
#include <string>

#include "functions.h"

namespace ra = std::ranges;

/* ==================== Graphic class definitions ==================== */
/* === graphic constructors === */
/* default */
Graphic::Graphic ()
{
  this->win = stdscr;
  this->text = std::vector<const char *>{ "" };
  this->attributes = std::vector<unsigned int>{};
  this->coords = { 0, 0 };
}

/* span, span, std::pair */
Graphic::Graphic (std::span<const char *> text, std::span<unsigned int> attributes, std::pair<size_t, size_t> coords, WINDOW *win)
{
  this->win = win;
  this->text.assign (text.begin (), text.end ());
  this->attributes.assign (attributes.begin (), attributes.end ());
  this->coords = coords;
}

/* initializer_list, initializer_list, std::pair */
Graphic::Graphic (std::initializer_list<const char *> text, std::initializer_list<unsigned int> attributes, size_t rows, size_t cols, WINDOW *win)
{
  this->win = win;
  this->text = text;
  this->attributes = attributes;
  this->coords = { rows, cols };
}

/* span, span, size_t, size_t */
Graphic::Graphic (std::span<const char *> text, std::span<unsigned int> attributes, size_t rows, size_t cols, WINDOW *win)
{
  this->win = win;
  this->text.assign (text.begin (), text.end ());
  this->attributes.assign (attributes.begin (), attributes.end ());
  this->coords = { rows, cols };
}

/* initializer_list, initializer_list, size_t, size_t */
Graphic::Graphic (std::initializer_list<const char *> text, std::initializer_list<unsigned int> attributes, std::pair<size_t, size_t> coords, WINDOW *win)
{
  this->win = win;
  this->text = text;
  this->attributes = attributes;
  this->coords = coords;
}

/* === graphic non-modifying member functions === */
[[nodiscard]] auto
Graphic::get_text () const -> std::vector<const char *>
{
  return this->text;
}

[[nodiscard]] auto
Graphic::get_attributes () const -> std::vector<unsigned int>
{
  return this->attributes;
}

[[nodiscard]] auto
Graphic::get_coords () const -> std::pair<size_t, size_t>
{
  return this->coords;
}
[[nodiscard]] auto
Graphic::get_win () const -> WINDOW *
{
  return this->win;
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
      mvwprintw (this->get_win (), this->get_coords ().first + i, this->get_coords ().second, "%s", l);
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
Graphic::set_text (std::initializer_list<const char *> text) -> void
{
  this->text = text;
}

auto
Graphic::set_attributes (std::span<unsigned int> attributes) -> void
{
  this->attributes.assign (attributes.begin (), attributes.end ());
}

auto
Graphic::set_attributes (std::initializer_list<unsigned int> attributes) -> void
{
  this->attributes = attributes;
}

auto
Graphic::set_coords (size_t rows, size_t cols) -> void
{
  this->coords = { rows, cols };
}

auto
Graphic::set_win (WINDOW *win) -> void
{
  this->win = win;
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
  this->win = stdscr;
  this->vertical = std::vector<const char *>{};
  this->horizontal = std::vector<const char *>{};
  this->attributes = std::vector<unsigned int>{};
  this->coords = { 0, 0 };
  this->orientation = Vertical;
  this->hits = {};
  this->size = this->vertical.size ();
}

/* span, pair, orientation */
Ship::Ship (std::span<const char *> vertical, std::span<const char *> horizontal, std::span<unsigned int> attributes, std::pair<size_t, size_t> coords, Orientation orientation)
{
  this->win = stdscr;
  this->vertical.assign (vertical.begin (), vertical.end ());
  this->horizontal.assign (horizontal.begin (), horizontal.end ());
  this->attributes.assign (attributes.begin (), attributes.end ());
  this->coords = coords;
  this->orientation = orientation;
  this->size = this->vertical.size ();
  this->hits = std::vector (this->size, Hit::Ok);
}

/* span, pair, orientation */
Ship::Ship (std::span<const char *> vertical, std::span<const char *> horizontal, std::span<unsigned int> attributes, size_t rows, size_t cols, Orientation orientation)
{
  this->win = stdscr;
  this->vertical.assign (vertical.begin (), vertical.end ());
  this->horizontal.assign (horizontal.begin (), horizontal.end ());
  this->attributes.assign (attributes.begin (), attributes.end ());
  this->coords = { rows, cols };
  this->orientation = orientation;
  this->size = this->vertical.size ();
  this->hits = std::vector (this->size, Hit::Ok);
}

/* initializer_list, initializer_list, initializer_list, std::pair, Orientation */
Ship::Ship (std::initializer_list<const char *> vertical, std::initializer_list<const char *> horizontal, std::initializer_list<unsigned int> attributes, std::pair<size_t, size_t> coords,
            Orientation orientation)
{
  this->win = stdscr;
  this->vertical = vertical;
  this->horizontal = horizontal;
  this->attributes = attributes;
  this->coords = coords;
  this->orientation = orientation;
  this->size = this->vertical.size ();
  this->hits = std::vector (this->size, Hit::Ok);
}

/* initializer_list, initializer_list, initializer_list, size_t, size_t */
Ship::Ship (std::initializer_list<const char *> vertical, std::initializer_list<const char *> horizontal, std::initializer_list<unsigned int> attributes, size_t rows, size_t cols,
            Orientation orientation)
{
  this->win = stdscr;
  this->vertical = vertical;
  this->horizontal = horizontal;
  this->attributes = attributes;
  this->coords = { rows, cols };
  this->orientation = orientation;
  this->size = this->vertical.size ();
  this->hits = std::vector (this->size, Hit::Ok);
}

/* std::pair, initializer_list, size_t, size_t, Orientation */
Ship::Ship (std::pair<std::initializer_list<const char *>, std::initializer_list<const char *> > skin_pair, size_t rows, size_t cols, Orientation orientation)
{
  this->win = stdscr;
  this->horizontal = skin_pair.first;
  this->vertical = skin_pair.second;
  this->attributes = std::vector<unsigned int>{ A_BOLD };
  this->coords = { rows, cols };
  this->orientation = orientation;
  this->size = this->vertical.size ();
  this->hits = std::vector (this->size, Hit::Ok);
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
Ship::get_orient () const -> Orientation
{
  return this->orientation;
}

[[nodiscard]] auto
Ship::get_hp () const -> long
{
  return std::count (this->hits.cbegin (), this->hits.cend (), Hit::Ok);
}

/* shows its internal state */
auto
Ship::show () const -> void
{
  auto lines = this->get_vert ();
  if (this->get_orient () == Orientation::Horizontal)
    lines = this->get_horz ();

  for (const auto &a : this->get_attributes ())
    attron (a);

  auto i = 0zu;
  for (const auto &l : lines)
    {
      mvwaddstr (this->get_win (), this->get_coords ().first + i, this->get_coords ().second, l);
      i++;
    }

  for (const auto &a : this->get_attributes ())
    attroff (a);

  wrefresh (this->get_win ());
}

/* === ship modifying member functions === */

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
Player::Player (const char *name, WINDOW *win)
{
  /* name and skin are always necessary */
  this->win = win;
  this->name = name;
  this->skin = Skin::Normal;
  this->points = 0zu;
  this->colors = Colors::Grayscale;
  this->carrier = Ship ({ "M", "X", "X", "X", "W" }, { "[XXXXXXX]" }, {}, 0, 0);

  this->battleship = Ship ({ "A", "&", "&", "V" }, { "<&&&&&>" }, {}, 0, 0);

  this->destroyer = Ship ({ "M", "H", "V" }, { "[===>" }, {}, 0, 0);

  this->submarine_1 = Ship ({ "n", "U" }, { "(@}" }, {}, 0, 0);
  this->submarine_2 = Ship ({ "n", "U" }, { "(@}" }, {}, 0, 0);

  this->patrol_1 = Ship ({ "^", "V" }, { "{:}" }, {}, 0, 0);
  this->patrol_2 = Ship ({ "^", "V" }, { "{:}" }, {}, 0, 0);
  this->carrier.set_win (this->win);
  this->battleship.set_win (this->win);
  this->destroyer.set_win (this->win);
  this->submarine_1.set_win (this->win);
  this->submarine_2.set_win (this->win);
  this->patrol_1.set_win (this->win);
  this->patrol_2.set_win (this->win);

  this->init_positions ();
}

/* === player non-modifying member getter functions === */
[[nodiscard]] auto
Player::get_win () const -> WINDOW *
{
  return this->win;
}

[[nodiscard]] auto
Player::get_name () const -> std::string
{
  return this->name;
}

[[nodiscard]] auto
Player::get_skin () const -> Skin
{
  return this->skin;
}

[[nodiscard]] auto
Player::get_points () const -> unsigned int
{
  return this->points;
}

/* show a specific ship in the player's hand */
auto
Player::get_ship (ShipName name) const -> Ship
{
  switch (name)
    {
    case Carrier:
      return this->carrier;
      break;

    case Battleship:
      return this->battleship;
      break;

    case Destroyer:
      return this->destroyer;
      break;

    case Submarine_1:
      return this->submarine_1;
      break;

    case Submarine_2:
      return this->submarine_2;
      break;

    case Patrol_1:
      return this->patrol_1;
      break;

    case Patrol_2:
      return this->patrol_2;
      break;
    }
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

    case Submarine_1:
      this->submarine_1.show ();
      break;

    case Submarine_2:
      this->submarine_2.show ();
      break;

    case Patrol_1:
      this->patrol_1.show ();
      break;

    case Patrol_2:
      this->patrol_2.show ();
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
  this->submarine_1.show ();
  this->submarine_2.show ();
  this->patrol_1.show ();
  this->patrol_2.show ();
}

auto
Player::show_boards () const -> void
{
  clear ();
  /* show boards */
  const auto primary_text = { "    Primary Grid   ", "  A B C D E F G H I J", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
  const auto primary_attrs = { A_NORMAL };
  const auto primary_labels = Graphic (primary_text, primary_attrs, 2, 10, this->get_win ());

  const auto tracking_text = { "   Tracking Grid   ", "  A B C D E F G H I J", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
  const auto tracking_attrs = { A_NORMAL };
  const auto tracking_labels = Graphic (tracking_text, tracking_attrs, 2, 50, this->get_win ());

  const auto board_text = { ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .",
                            ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . ." };

  const auto board_attrs = { A_DIM };
  const auto board_primary = Graphic (board_text, board_attrs, 4, 12, this->get_win ());
  const auto board_tracking = Graphic (board_text, board_attrs, 4, 52, this->get_win ());

  const auto labels = { primary_labels, tracking_labels, board_primary, board_tracking };
  for (const auto &l : labels)
    l.show ();

  box (this->get_win (), 0, 0);
  mvwprintw (this->get_win (), 0, 2, "This is %s's Board", this->get_name ().c_str ());
  mvwprintw (this->get_win (), 24, 53, "Hit q to quit, h for help");
  mvwprintw (this->get_win (), 16, 5, "Carrier:\tBattleship:\tDestroyer:\tSubmarines:\tPatrol Boats:");
  this->show_ships_status ();
  wrefresh (this->get_win ());
}

auto
Player::show_ships_status () const -> void
{
  mvwprintw (this->get_win (), 18, 5, "HP: [%ld/5]", this->carrier.get_hp ());

  mvwprintw (this->get_win (), 18, 16, "HP: [%ld/4]", this->battleship.get_hp ());

  mvwprintw (this->get_win (), 18, 32, "HP: [%ld/3]", this->destroyer.get_hp ());

  mvwprintw (this->get_win (), 18, 48, "HP: [%ld/2]", this->submarine_1.get_hp ());

  mvwprintw (this->get_win (), 20, 48, "HP: [%ld/2]", this->submarine_2.get_hp ());

  mvwprintw (this->get_win (), 18, 64, "HP: [%ld/2]", this->patrol_1.get_hp ());

  mvwprintw (this->get_win (), 20, 64, "HP: [%ld/2]", this->patrol_2.get_hp ());
}

/* === player modifying member setter functions === */
auto
Player::set_win (WINDOW *win) -> void
{
  this->win = win;
}

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
  this->carrier.set_coords (18, 5);
  this->carrier.add_attribute (A_BLINK);

  this->battleship.set_coords (18, 16);
  this->battleship.add_attribute (A_BOLD);

  this->destroyer.set_coords (18, 32);
  this->destroyer.add_attribute (A_BOLD);

  this->submarine_1.set_coords (18, 48);
  this->submarine_1.add_attribute (A_BOLD);

  this->submarine_2.set_coords (18, 52);
  this->submarine_2.add_attribute (A_BOLD);

  this->patrol_1.set_coords (18, 65);
  this->patrol_1.add_attribute (A_BOLD);

  this->patrol_2.set_coords (18, 69);
  this->patrol_2.add_attribute (A_BOLD);
}

auto
Player::ship_coords (ShipName name, size_t row, size_t col) -> void
{
  switch (name)
    {
    case ShipName::Carrier:
      this->carrier.set_coords (row, col);
      break;

    case ShipName::Battleship:
      this->battleship.set_coords (row, col);
      break;

    case ShipName::Destroyer:
      this->destroyer.set_coords (row, col);
      break;

    case ShipName::Submarine_1:
      this->submarine_1.set_coords (row, col);
      break;

    case ShipName::Submarine_2:
      this->submarine_2.set_coords (row, col);
      break;

    case ShipName::Patrol_1:
      this->patrol_1.set_coords (row, col);
      break;

    case ShipName::Patrol_2:
      this->patrol_2.set_coords (row, col);
      break;
    }
}

auto
Player::ship_orient (ShipName name, Orientation orientation) -> void
{
  switch (name)
    {
    case ShipName::Carrier:
      this->carrier.set_orientation (orientation);
      break;

    case ShipName::Battleship:
      this->battleship.set_orientation (orientation);
      break;

    case ShipName::Destroyer:
      this->destroyer.set_orientation (orientation);
      break;

    case ShipName::Submarine_1:
      this->submarine_1.set_orientation (orientation);
      break;

    case ShipName::Submarine_2:
      this->submarine_2.set_orientation (orientation);
      break;

    case ShipName::Patrol_1:
      this->patrol_1.set_orientation (orientation);
      break;

    case ShipName::Patrol_2:
      this->patrol_2.set_orientation (orientation);
      break;
    }
}
auto
Player::place_ship (ShipName name) -> void
{
  /* place carrier */
  auto row = 4zu;
  auto col = 12zu;
  auto orientation = this->get_ship (name).get_orient ();
  this->ship_coords (name, row, col);
  this->show (name);
  while (const auto ch = getch ())
    {

      const auto key_press = parse_key (ch);
      switch (key_press)
        {
        case KeyPress::Up:
          row = row == 4 ? 4 : row - 1;
          break;

        case KeyPress::Down:
          if (orientation == Vertical)
            row = row == 9 ? 9 : row + 1;
          else
            row = row == 13 ? 13 : row + 1;
          break;

        case KeyPress::Left:
          col = col == 12 ? 12 : col - 2;
          break;

        case KeyPress::Right:
          if (orientation == Horizontal)
            col = col == 22 ? 22 : col + 2;
          else
            col = col == 30 ? 30 : col + 2;
          break;

        case KeyPress::r:
          if (col >= 24 && orientation == Vertical)
            continue;
          else if (row >= 10 && orientation == Horizontal)
            continue;
          else
            orientation = orientation == Vertical ? Horizontal : Vertical;
          break;

        case KeyPress::h:
          show_help ();
          break;

        case KeyPress::q:
          clear ();
          return;
          break;

        case KeyPress::Enter:
          return;
          break;

        default:
          break;
        }

      this->ship_coords (name, row, col);
      this->ship_orient (name, orientation);
      this->show_boards ();
      this->show (name);
      wrefresh (this->get_win ());
    }
}
