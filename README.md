# Sokoban

The game is played on a board of squares, where each square is a floor or a wall. Some floor squares contain boxes, and some floor squares are marked as storage locations.

![Menu](/ressources/menu.png)

## Rules

The player is confined to the board, and may move horizontally or vertically onto empty squares (never through walls or boxes). The player can also move into a box, which pushes it into the square beyond. Boxes may not be pushed into other boxes or walls, and they cannot be pulled. The number of boxes is equal to the number of storage locations. The puzzle is solved when all boxes are at storage locations.

- Player can push a box by moving into it wish push it into the square beyond.
- Box can't be pulled or pushed throw walls.
- You should push all Boxs to the storage locations (green dots)
- when you finish the boxs you WIN!

## Dependencies
This program use the graphic library **SDL 1.2** and his additional package **SDL image**

### Ubuntu:
- `sudo apt-get install libsdl-dev`
- `sudo apt-get install libsdl-image1.2-dev`

### Mac OS:
- `brew install sdl`
- `brew install sdl_image`

## Compile
- Run `make`

## Usage
- Execute `./Sokuban`

## Gameplay
- **Arrows**: Move horizontally or verticaly into empty squares
- **Esc**: Quit

![Gameplay](/ressources/gameplay.png)

## Level Editor
- **Mouse Right  Click**: Make the mouse pointed square empty (you can hold click and slide in the window)
- **Num 1**: Choose `Wall` spirit square
- **Num 2**: Choose `Box` spirit square
- **Num 3**: Choose `Storage location` spirit square
- **Num 4**: Choose `Player` spirit square
- **s**: Save the level

## Owner
- Oussama Belouche 1337


[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/makes-people-smile.svg)](https://forthebadge.com)

