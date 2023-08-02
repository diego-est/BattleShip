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

/* Graphic class definitions */
Graphic::Graphic(std::vector<const char *> text, std::vector<unsigned int> attributes, std::pair<int, int> coords)
{
    this->text = text;
    this->attributes = attributes;
    this->coords = coords;
}

/* empty constructor */
Graphic::Graphic()
{
    this->text = std::vector<const char *>{""};
    this->attributes = std::vector<unsigned int>{};
    this->coords = std::make_pair(0, 0);
}

/* non-modifying member functions */
// clang-format off
auto Graphic::get_text() const -> std::vector<const char *>         { return text; }
auto Graphic::get_attributes() const -> std::vector<unsigned int>   { return attributes; }
auto Graphic::get_coords() const -> std::pair<int, int>             { return coords; }
// clang-format on

/* modifying member functions */
// TODO: these are somewhat broken
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

/* class member setters */
// clang-format off
auto Graphic::set_text(std::vector<const char *> text) -> void              { this->text = text; }
auto Graphic::set_attributes(std::vector<unsigned int> attributes) -> void  { this->attributes = attributes; }
auto Graphic::set_coords(int row, int col) -> void                          { this->coords = std::make_pair(row, col); }
auto Graphic::set_coords(std::pair<int, int> coords) -> void                { this->coords = coords; }


/* AbstractButton class definitions */
auto AbstractButton::get_graph() const -> Graphic *
{
    if (this->graph == NULL) exit(1);
    else return this->graph;
}


/* ExitButton : AbstractButton class definitions */
ExitButton::ExitButton(Graphic *graph)
{
    if (graph != NULL) this->graph = graph;
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


/* OptsButton : AbstractButton class definitions */
// clang-format off
OptsButton::OptsButton(Graphic *graph)
{
    if (graph != NULL) this->graph = graph;
}

OptsButton::~OptsButton()
{
    std::cout << "Deleted Opts button" << std::endl;
}
// clang-format on

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

auto OptsButton::show_player(Player player) const -> void
{
    auto name_attrs = std::vector<unsigned int>{A_NORMAL};
    auto name_text = std::vector<const char *>{player.get_name().c_str()};
    auto name = Graphic(name_text, name_attrs, std::make_pair<int, int>(7, 20));
}

/* GameButton class definitions */
// clang-format off
GameButton::GameButton(Graphic *graph)
{
    if (graph != NULL) this->graph = graph;
}

GameButton::~GameButton()
{
    std::cout << "Deleted Game button" << std::endl;
}
// clang-format on

auto GameButton::action() const -> void
{
    clear();

    auto p1_primary_text = std::vector<const char *>{"    Primary Grid   ", "  A B C D E F G H I J", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    auto p1_primary_attrs = std::vector<unsigned int>{A_NORMAL};
    auto p1_primary_labels = Graphic{p1_primary_text, p1_primary_attrs, std::make_pair(2, 10)};

    auto p1_tracking_text = std::vector<const char *>{"   Tracking Grid   ", "  A B C D E F G H I J", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    auto p1_tracking_attrs = std::vector<unsigned int>{A_NORMAL};
    auto p1_tracking_labels = Graphic{p1_tracking_text, p1_tracking_attrs, std::make_pair(2, 50)};

    auto board_text = std::vector<const char *>{". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .",
                                                ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . .", ". . . . . . . . . ."};
    auto board_attrs = std::vector<unsigned int>{A_DIM};
    auto board_primary = Graphic{board_text, board_attrs, std::make_pair(4, 12)};
    auto board_tracking = Graphic{board_text, board_attrs, std::make_pair(4, 52)};

    auto carrier_horz = std::vector<const char *>{"[XXXXXXX]"};
    auto carrier_vert = std::vector<const char *>{"M", "X", "X", "X", "W"};
    auto carrier_attrs = std::vector<unsigned int>{A_BOLD};
    auto carrier = Ship(carrier_vert, carrier_horz, carrier_attrs, std::make_pair(16, 15));

    auto battleship_horz = std::vector<const char *>{"<&&&&&>"};
    auto battleship_vert = std::vector<const char *>{"A", "&", "&", "V"};
    auto battleship_attrs = std::vector<unsigned int>{A_BOLD};
    auto battleship = Ship(battleship_vert, battleship_horz, battleship_attrs, std::make_pair(16, 25));

    auto destroyer_horz = std::vector<const char *>{"[===>"};
    auto destroyer_vert = std::vector<const char *>{"M", "H", "V"};
    auto destroyer_attrs = std::vector<unsigned int>{A_BOLD};
    auto destroyer = Ship(destroyer_vert, destroyer_horz, destroyer_attrs, std::make_pair(16, 35));

    auto submarine_horz = std::vector<const char *>{"(@)"};
    auto submarine_vert = std::vector<const char *>{"n", "U"};
    auto submarine_attrs = std::vector<unsigned int>{A_BOLD};
    auto submarine = Ship(submarine_vert, submarine_horz, submarine_attrs, std::make_pair(16, 45));

    auto patrol_horz = std::vector<const char *>{"{:}"};
    auto patrol_vert = std::vector<const char *>{"^", "V"};
    auto patrol_attrs = std::vector<unsigned int>{A_BOLD};
    auto patrol = Ship(patrol_vert, patrol_horz, patrol_attrs, std::make_pair(16, 55));

    box(stdscr, 0, 0);
    refresh();

    show(p1_primary_labels);
    show(p1_tracking_labels);
    show(board_primary);
    show(board_tracking);
    carrier.show(Vertical);
    battleship.show(Vertical);
    destroyer.show(Vertical);
    submarine.show(Vertical);
    patrol.show(Vertical);
    refresh();

    getch();
    clear();
}

Ship::Ship(std::vector<const char *> vertical, std::vector<const char *> horizontal, std::vector<unsigned int> attributes, std::pair<int, int> coords)
{
    this->vertical = vertical;
    this->horizontal = horizontal;
    this->attributes = attributes;
    this->coords = coords;
}

auto Ship::get_vert() const -> std::vector<const char *>
{
    return this->vertical;
}
auto Ship::get_horz() const -> std::vector<const char *>
{
    return this->horizontal;
}

auto Ship::show(Orientation orientation) const -> void
{
    auto ship_graphic = Graphic();
    ship_graphic.set_attributes(this->attributes);
    ship_graphic.set_coords(this->coords);
    switch (orientation)
    {
    case Vertical:
        ship_graphic.set_text(this->vertical);
        break;

    case Horizontal:
        ship_graphic.set_text(this->horizontal);
        break;
    }
    ::show(ship_graphic);
}

/* Player class definitions */
Player::Player(const char *name)
{
    this->name = name;
    this->skin = Normal;
    this->points = 0;
}

/* non-modifying member functions */
// clang-format off
auto Player::get_name() const -> std::string    { return name; }
auto Player::get_skin() const -> Skin           { return skin; }
auto Player::get_points() const -> unsigned int { return points; }

/* modifying member functions */
auto Player::set_name(std::string name) -> void         { this->name = name; }
auto Player::set_skin(Skin skin) -> void                { this->skin = skin; }
auto Player::set_points(unsigned int points) -> void    { this->points = points; }
// clang-format on
