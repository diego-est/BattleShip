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
Graphic::Graphic(std::span<const char *> text, std::span<unsigned int> attributes, std::pair<size_t, size_t> coords)
{
    this->text.assign(text.begin(), text.end());
    this->attributes.assign(attributes.begin(), attributes.end());
    this->coords = coords;
}

Graphic::Graphic(std::span<const char *> text, std::span<unsigned int> attributes, size_t rows, size_t cols)
{
    this->text.assign(text.begin(), text.end());
    this->attributes.assign(attributes.begin(), attributes.end());
    this->coords = std::make_pair(rows, cols);
}

/* empty constructor */
Graphic::Graphic()
{
    this->text = std::vector<const char *>{""};
    this->attributes = std::vector<unsigned int>{};
    this->coords = std::make_pair(0, 0);
}

/* non-modifying member functions */
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

/* modifying member functions */
// TODO: these (remove_attribute, add_attribute) are somewhat broken?
auto Graphic::remove_attribute(unsigned int attribute) -> void
{
    auto f = this->attributes.begin();
    auto l = this->attributes.end();
    // static_cast<void>() to discard return value from std::remove()
    static_cast<void>(std::remove(f, l, attribute));
}
auto Graphic::add_attribute(unsigned int attribute) -> void
{
    this->attributes.push_back(attribute);
}

auto Graphic::swap_attributes(unsigned int old_attribute, unsigned int new_attribute) -> void
{
    ra::replace(this->attributes, old_attribute, new_attribute);
}

/* class member setters */
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

/* ==================== Ship class definitions ==================== */
Ship::Ship(std::vector<const char *> vertical, std::vector<const char *> horizontal, std::vector<unsigned int> attributes, std::pair<int, int> coords)
{
    this->vertical = vertical;
    this->horizontal = horizontal;
    this->attributes = attributes;
    this->coords = coords;
}

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
Player::Player(const char *name)
{
    this->name = name;
    this->skin = Normal;
    this->points = 0;
}

/* non-modifying member functions */
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

/* modifying member functions */
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
