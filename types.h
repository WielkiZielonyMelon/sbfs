#pragma once
#include <tuple>
#include <vector>

enum Tile { Corridor, Wall, Player, Box, Storage,
            PlayerOnStorage, BoxOnStorage };

typedef std::tuple<unsigned int, unsigned int> Position;
typedef std::tuple<Position, Tile> PositionOfTile;
typedef std::vector<Position> Solution;
typedef std::vector<PositionOfTile> UndoTiles;

