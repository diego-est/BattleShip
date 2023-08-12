# BattleShip
## Classes
### `Graphic`
1. Purpose:
  - Hold all the required information needed to display a simple graphic on the screen.
2. Public Methods:
  - Value returning:
    - `[[nodiscard]] auto get_win() const -> WINDOW *`
    - `[[nodiscard]] auto get_text() const -> std::vector<const char *>`
    - `[[nodiscard]] auto get_attributes() const -> std::vector<unsigned int>`
    - `[[nodiscard]] auto get_coords() const -> std::pair<size_t, size_t>`
  - Void:
    - `auto show() const -> void`
    - `auto set_win(WINDOW *) -> void`
    - `auto set_text(std::span<const char *>) -> void`
    - `auto set_text(std::initializer_list<unsigned int>) -> void`
### `Ship : Graphic`
1. Purpose:
  - Hold extra information needed to display an entire ship entity.
2. Public Methods:
  - Value returning:
  - Void:
### `Player`
1. Purpose:
  - Hold and manage information pertaining to a specific player.
2. Public Methods:
  - Value returning:
  - Void:

## Assets

Logo:
```
 _               __        
|_) _._|__|_| _ (_ |_ o._  
|_)(_| |_ |_|(/___)| |||_) 
                       |   
```

[Hasbro instructions](https://www.hasbro.com/common/instruct/BattleShip_(2002).PDF)

Sample grid:
```
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
```
## Ships
- Carrier: 5
```
  [XXXXXXX] o o o o M
  o o o o o o o o o X
  o o o o o o o o o X
  o o o o o o o o o X
  o o o o o o o o o W
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
```
- Battleship: 4
```
  <&&&&&> o o o o o A
  o o o o o o o o o &
  o o o o o o o o o &
  o o o o o o o o o V
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
```
- Destroyer: 3
```
  [===> o o o o o o M
  o o o o o o o o o H
  o o o o o o o o o V
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
```
- Submarine: 2
```
  (@) o o o o o o o n
  o o o o o o o o o U
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
```
- Patrol Boat: 2
```
  {:} o o o o o o o ^
  o o o o o o o o o V
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
  o o o o o o o o o o
```
