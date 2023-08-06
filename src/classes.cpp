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
/* default constructor */
Graphic::Graphic()
{
    this->text = std::vector<const char *>{""};
    this->attributes = std::vector<unsigned int>{};
    this->coords = std::make_pair(0, 0);
}

/* constructor using span and std::pair to group coordinates */
Graphic::Graphic(std::span<const char *> text, std::span<unsigned int> attributes, std::pair<size_t, size_t> coords)
{
    this->text.assign(text.begin(), text.end());
    this->attributes.assign(attributes.begin(), attributes.end());
    this->coords = coords;
}

/* constructor using span and two size_t coordinates */
Graphic::Graphic(std::span<const char *> text, std::span<unsigned int> attributes, size_t rows, size_t cols)
{
    this->text.assign(text.begin(), text.end());
    this->attributes.assign(attributes.begin(), attributes.end());
    this->coords = std::make_pair(rows, cols);
}

/* constructor using initializer list and two size_t coordinates */
Graphic::Graphic(std::initializer_list<const char *> text, std::initializer_list<unsigned int> attributes, size_t rows, size_t cols)
{
    this->text.assign(text.begin(), text.end());
    this->attributes.assign(attributes.begin(), attributes.end());
    this->coords = std::make_pair(rows, cols);
}

/* constructor using initializer list and std::pair to group coordinates */
Graphic::Graphic(std::initializer_list<const char *> text, std::initializer_list<unsigned int> attributes, std::pair<size_t, size_t> coords)
{
    this->text.assign(text.begin(), text.end());
    this->attributes.assign(attributes.begin(), attributes.end());
    this->coords = coords;
}

/* non-modifying member getter functions */
[[nodiscard]] auto Graphic::get_text() const -> std::vector<const char *>
{
    return text;
}
[[nodiscard]] auto Graphic::get_attributes() const -> std::vector<unsigned int>
{
    return attributes;
}
[[nodiscard]] auto Graphic::get_coords() const -> std::pair<size_t, size_t>
{
    return coords;
}

/* modifying member setter functions */
auto Graphic::set_text(std::span<const char *> text) -> void
{
    this->text.assign(text.begin(), text.end());
}
auto Graphic::set_attributes(std::span<unsigned int> attributes) -> void
{
    this->attributes.assign(attributes.begin(), attributes.end());
}
auto Graphic::set_coords(size_t rows, size_t cols) -> void
{
    this->coords = std::make_pair(rows, cols);
}
auto Graphic::set_coords(std::pair<size_t, size_t> coords) -> void
{
    this->coords = coords;
}

/* function to display a graphic using its internal state */
auto Graphic::show() const -> void
{
    // set attributes
    for (const auto &a : this->get_attributes())
        attron(a);

    // place characters on graph
    auto i = 0lu;
    for (const auto &l : this->get_text())
    {
        mvwprintw(stdscr, this->get_coords().first + i, this->get_coords().second, "%s", l);
        i++;
    }

    // unset attributes
    for (const auto &a : this->get_attributes())
        attroff(a);

    refresh();
}


// TODO: test remove_attribute
/* removes a specific attribute from its vector of attributes */
auto Graphic::remove_attribute(unsigned int attribute) -> void
{
    auto f = this->attributes.begin();
    auto l = this->attributes.end();
    // static_cast<void>() to discard return value from std::remove()
    static_cast<void>(std::remove(f, l, attribute));
}

/* simply pushes an attribute into its attribute vector */
auto Graphic::add_attribute(unsigned int attribute) -> void
{
    this->attributes.push_back(attribute);
}

/* swaps a specific attribute with another attribute in its attribute vector */
auto Graphic::swap_attributes(unsigned int old_attribute, unsigned int new_attribute) -> void
{
    ra::replace(this->attributes, old_attribute, new_attribute);
}


/* ==================== Ship class definitions ==================== */
/* default constructor */
Ship::Ship()
{
    this->vertical = std::vector<const char *>{};
    this->horizontal = std::vector<const char *>{};
    this->attributes = std::vector<unsigned int>{};
    this->coords = std::make_pair<size_t, size_t>(0, 0);
}

/* constructor using vectors and std::pair to group coordinates */
Ship::Ship(std::vector<const char *> vertical, std::vector<const char *> horizontal, std::vector<unsigned int> attributes, std::pair<int, int> coords)
{
    this->vertical = vertical;
    this->horizontal = horizontal;
    this->attributes = attributes;
    this->coords = coords;
}

/* constructor using initializer lists and two size_t coordinates */
Ship::Ship(std::initializer_list<const char *> vertical, std::initializer_list<const char *> horizontal, std::initializer_list<unsigned int> attributes, size_t rows, size_t cols)
{
    this->vertical.assign(vertical.begin(), vertical.end());
    this->horizontal.assign(horizontal.begin(), horizontal.end());
    this->attributes.assign(attributes.begin(), attributes.end());
    this->coords = std::make_pair(rows, cols);
}

/* constructor using initializer lists and std::pair to group coordinates */
Ship::Ship(std::initializer_list<const char *> vertical, std::initializer_list<const char *> horizontal, std::initializer_list<unsigned int> attributes, std::pair<size_t, size_t> coords)
{
    this->vertical.assign(vertical.begin(), vertical.end());
    this->horizontal.assign(horizontal.begin(), horizontal.end());
    this->attributes.assign(attributes.begin(), attributes.end());
    this->coords = coords;
}
/* constructor using std::pair to group both skin orientations and two size_t coordinates */
Ship::Ship(std::pair<std::initializer_list<const char *>, std::initializer_list<const char *>> skin_pair, size_t rows, size_t cols)
{
    this->horizontal.assign(skin_pair.first.begin(), skin_pair.first.end());
    this->vertical.assign(skin_pair.second.begin(), skin_pair.second.end());
    this->attributes = std::vector<unsigned int>{A_BOLD};
    this->coords = std::make_pair(rows, cols);
}

/* non-modifying member getter functions */
[[nodiscard]] auto Ship::get_vert() const -> std::vector<const char *>
{
    return this->vertical;
}
[[nodiscard]] auto Ship::get_horz() const -> std::vector<const char *>
{
    return this->horizontal;
}
[[nodiscard]] auto Ship::get_attributes() const -> std::vector<unsigned int>
{
    return attributes;
}
[[nodiscard]] auto Ship::get_coords() const -> std::pair<size_t, size_t>
{
    return coords;
}

/* shows its internal state */
auto Ship::show(Orientation orientation) const -> void
{
    auto ship_graphic = Graphic();
    auto attr_v = this->get_attributes();
    auto attrs = std::span<unsigned int>{attr_v};
    ship_graphic.set_attributes(attrs);
    ship_graphic.set_coords(this->coords);
    auto orient_v = std::vector<const char *>{};
    switch (orientation)
    {
    case Vertical:
        orient_v = this->vertical;
        break;

    case Horizontal:
        orient_v = this->horizontal;
        break;
    }
    ship_graphic.set_text(orient_v);
    ::show(ship_graphic);
}

/* ==================== Player class definitions ==================== */
/* name and skin are always necessary */
Player::Player(const char *name, Skin skin)
{
    this->name = name;
    this->skin = skin;
    this->points = 0;
    this->update_skin_cache();
    this->carrier = Ship();
    this->battleship = Ship();
    this->destroyer = Ship();
    this->submarine = Ship();
    this->patrol = Ship();
}

/* non-modifying member getter functions */
[[nodiscard]] auto Player::get_name() const -> std::string
{
    return name;
}
[[nodiscard]] auto Player::get_skin() const -> Skin
{
    return skin;
}
[[nodiscard]] auto Player::get_points() const -> unsigned int
{
    return points;
}

/* modifying member setter functions */
auto Player::set_name(std::string name) -> void
{
    this->name = name;
}
auto Player::set_skin(Skin skin) -> void
{
    this->skin = skin;
}
auto Player::set_points(unsigned int points) -> void
{
    this->points = points;
}

/* updates the Player skin cache */
auto Player::update_skin_cache() -> void
{
    /* Carrier */
    auto carrier = std::map<Skin, std::pair<std::initializer_list<const char *>, std::initializer_list<const char *>>>{};
    carrier[Skin::Normal] = std::make_pair<std::initializer_list<const char *>, std::initializer_list<const char *>>({"[XXXXXXX]"}, {"M", "X", "X", "X", "W"});
    carrier[Skin::Donuts] = std::make_pair<std::initializer_list<const char *>, std::initializer_list<const char *>>({"TODO"}, {"T", "O", "D", "O"});
    carrier[Skin::Inverted] = std::make_pair<std::initializer_list<const char *>, std::initializer_list<const char *>>({"[XXXXXXX]"}, {"M", "X", "X", "X", "W"});

    /* Battleship */
    auto battleship = std::map<Skin, std::pair<std::initializer_list<const char *>, std::initializer_list<const char *>>>{};
    battleship[Skin::Normal] = std::make_pair<std::initializer_list<const char *>, std::initializer_list<const char *>>({"<&&&&&>"}, {"A", "&", "&", "V"});
    battleship[Skin::Donuts] = std::make_pair<std::initializer_list<const char *>, std::initializer_list<const char *>>({"TODO"}, {"T", "O", "D", "O"});
    battleship[Skin::Inverted] = std::make_pair<std::initializer_list<const char *>, std::initializer_list<const char *>>({"<&&&&&>"}, {"A", "&", "&", "V"});

    /* Destroyer */
    auto destroyer = std::map<Skin, std::pair<std::initializer_list<const char *>, std::initializer_list<const char *>>>{};
    destroyer[Skin::Normal] = std::make_pair<std::initializer_list<const char *>, std::initializer_list<const char *>>({""}, {""});
    destroyer[Skin::Donuts] = std::make_pair<std::initializer_list<const char *>, std::initializer_list<const char *>>({"TODO"}, {"T", "O", "D", "O"});

    /* Submarine */
    auto submarine = std::map<Skin, std::pair<std::initializer_list<const char *>, std::initializer_list<const char *>>>{};
    submarine[Skin::Normal] = std::make_pair<std::initializer_list<const char *>, std::initializer_list<const char *>>({""}, {""});
    submarine[Skin::Donuts] = std::make_pair<std::initializer_list<const char *>, std::initializer_list<const char *>>({"TODO"}, {"T", "O", "D", "O"});

    /* Patrol */
    auto patrol = std::map<Skin, std::pair<std::initializer_list<const char *>, std::initializer_list<const char *>>>{};
    patrol[Skin::Normal] = std::make_pair<std::initializer_list<const char *>, std::initializer_list<const char *>>({""}, {""});
    patrol[Skin::Donuts] = std::make_pair<std::initializer_list<const char *>, std::initializer_list<const char *>>({"TODO"}, {"T", "O", "D", "O"});

    /* map of all the ships */
    this->ship_skins[ShipName::Carrier] = carrier;
    this->ship_skins[ShipName::Battleship] = battleship;
    this->ship_skins[ShipName::Destroyer] = destroyer;
    this->ship_skins[ShipName::Submarine] = submarine;
    this->ship_skins[ShipName::Patrol] = patrol;
}
