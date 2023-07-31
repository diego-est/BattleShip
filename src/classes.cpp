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

#include "functions.h"

namespace ra = std::ranges;

Graphic::Graphic(std::vector<const char *> text, std::vector<unsigned int> attributes, std::pair<int, int> coords)
{
    this->text = text;
    this->attributes = attributes;
    this->coords = coords;
}

/* non-modifying member functions */
auto Graphic::get_text() const -> std::vector<const char *>
{
    return text;
}
auto Graphic::get_attributes() const -> std::vector<unsigned int>
{
    return attributes;
}
auto Graphic::get_coords() const -> std::pair<int, int>
{
    return coords;
}

/* modifying member functions */
auto Graphic::remove_attribute(unsigned int attribute) -> void
{
    std::cout << "inside function";
    auto f = this->attributes.begin();
    auto l = this->attributes.end();
    /* static_cast<void>() to discard return value from std::remove() */
    // static_cast<void>(std::remove(f, l, attribute));

    f = std::find(f, l, attribute);
    this->attributes.erase(f);
}

auto Graphic::add_attribute(unsigned int attribute) -> void
{
    this->attributes.push_back(attribute);
}

auto Graphic::swap_attributes(unsigned int old_attribute, unsigned int new_attribute) -> void
{
    /* static_cast<void>() to discard return value from std::remove() */
    std::cout << "before removing";
    this->remove_attribute(old_attribute);
    std::cout << "before adding" << std::endl;
    this->add_attribute(new_attribute);
    // ra::replace(this->attributes, old_attribute, new_attribute);
    //  static_cast<void>(ra::replace(this->attributes, old_attribute, new_attribute));
}

/* AbstractButton functionality */
auto AbstractButton::get_graph() const -> Graphic *
{
    if (this->graph == NULL)
        exit(1);
    else
        return this->graph;
}

/* ExitButton functionality */
ExitButton::ExitButton(Graphic *graph)
{
    if (graph != NULL)
        this->graph = graph;
}
ExitButton::~ExitButton()
{
    std::cout << "Deleted Exit button" << std::endl;
}

auto ExitButton::action() const -> void
{
    clear();
    endwin();
    refresh();
    std::cout << "exited succesfully" << std::endl;
    exit(0);
}

/* OptsButton functionality */
OptsButton::OptsButton(Graphic *graph)
{
    if (graph != NULL)
        this->graph = graph;
}
OptsButton::~OptsButton()
{
    std::cout << "Deleted Opts button" << std::endl;
}

auto OptsButton::action() const -> void
{
    clear();
    auto max_x = 0;
    auto max_y = 0;
    getmaxyx(stdscr, max_y, max_x);
    auto opts_win = newwin(1, 1, max_y, max_x);
    getmaxyx(opts_win, max_y, max_x);

    auto p1_text = std::vector<const char *>{"   ___  __                    ___", "  / _ \\/ /__ ___ _____ ____  <  /", " / ___/ / _ `/ // / -_) __/  / / ", "/_/  /_/\\_,_/\\_, /\\__/_/    /_/  ",
                                             "            /___/                "};

    auto p1_attrs = std::vector<unsigned int>{A_NORMAL};

    auto p1 = Graphic{p1_text, p1_attrs, std::make_pair(5, 5)};

    box(stdscr, 0, 0);
    wrefresh(opts_win);
    refresh();

    show(p1);
    wrefresh(opts_win);
    refresh();
    getch();
    delwin(opts_win);
    clear();
}

/* GameButton functionality */
GameButton::GameButton(Graphic *graph)
{
    if (graph != NULL)
        this->graph = graph;
}
GameButton::~GameButton()
{
    std::cout << "Deleted Game button" << std::endl;
}

auto GameButton::action() const -> void
{
    std::cout << "opened game" << std::endl;
}

Player::Player(const char *name)
{
    this->name = name;
    this->skin = Normal;
    this->points = 0;
}

/* non-modifying member functions */
auto Player::get_name() const -> std::string
{
    return name;
}
auto Player::get_skin() const -> Skin
{
    return skin;
}
auto Player::get_points() const -> unsigned int
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

auto OptsButton::show_player(Player player) const -> void
{
    auto name_attrs = std::vector<unsigned int>{A_NORMAL};
    auto name_text = std::vector<const char *>{player.get_name().c_str()};
    auto name = Graphic(name_text, name_attrs, std::make_pair<int, int>(7, 20));
}
