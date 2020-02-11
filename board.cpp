#include <iostream>
#include <tuple>
#include <vector>

#include "board.h"
#include "types.h"

using std::cout;
using std::endl;
using std::get;
using std::vector;

void Board::print(void) {
    for (auto row: map) {
        for (auto tile: row) {
            cout << static_cast<int>(tile);
        }
        cout << endl;
    }
}

bool Board::operator==(const Board& o) const {
    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int col = 0; col < cols; ++col) {
            if (map[row][col] != o[row][col]) {
                return false;
            }
        }
    }

    return true;
}

bool Board::isSolved() const {
    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int col = 0; col < cols; ++col) {
            if (map[row][col] == Box) {
                return false;
            }
        }
    }

    return true;
}

Position Board::findPlayerPosition() const {
    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int col = 0; col < cols; ++col) {
            if (map[row][col] == Tile::Player) {
                return Position(row, col);
            }
        }
    }

    throw;
}

vector<Position> Board::getLegalMoves(Position position) const {
    auto rowFrom = get<0>(position);
    auto colFrom = get<1>(position);

    vector<Position> candidates;
    if (rowFrom > 0) {
        candidates.push_back(Position(rowFrom - 1, colFrom));
    }
    if (rowFrom < getRows() - 1) {
        candidates.push_back(Position(rowFrom + 1, colFrom));
    }
    if (colFrom > 0) {
        candidates.push_back(Position(rowFrom, colFrom - 1));
    }
    if (colFrom < getCols() - 1) {
        candidates.push_back(Position(rowFrom, colFrom + 1));
    }


    vector<Position> trueCandidates;
    for (auto candidate: candidates) {
        auto rowTo = get<0>(candidate);
        auto colTo = get<1>(candidate);
        if (map[rowTo][colTo] == Tile::Wall) {
            continue;
        }
        // This can either be Storage or Corridor. It is not possible to be Player
        // or PlayerOnStorage
        if (map[rowTo][colTo] != Tile::Box and map[rowTo][colTo] != Tile::BoxOnStorage) {
            trueCandidates.push_back(candidate);
            continue;
        }

        // This must be a Box or BoxOnStorage. We cannot push it off the map
        if (rowTo == 0 and rowFrom == 1) {
            continue;
        }

        if (rowTo == getRows() - 1 and rowFrom == rowTo - 1) {
            continue;
        }

        if (colTo == 0 and colFrom == 1) {
            continue;
        }

        if (colTo == getCols() - 1 and colFrom == colTo - 1) {
            continue;
        }

        // We know that we can push the box, but still do not know the destination of that box.
        // If the destination is not Storage or Corridor, than we are blocked
        auto rowPushTo = rowTo;
        auto colPushTo = colTo;
        if (rowFrom > rowTo) {
            rowPushTo = rowTo - 1;
        } else if (rowTo > rowFrom) {
            rowPushTo = rowTo + 1;
        } else if (colFrom > colTo) {
            colPushTo = colTo - 1;
        } else {
            colPushTo = colTo + 1;
        }

        if (map[rowPushTo][colPushTo] == Tile::Storage or map[rowPushTo][colPushTo] == Tile::Corridor) {
            trueCandidates.push_back(candidate);
        }
    }

    return trueCandidates;
}

UndoTiles Board::move(Position from, Position to) {
    UndoTiles undoTiles;
    auto rowFrom = get<0>(from);
    auto colFrom = get<1>(from);
    auto rowTo = get<0>(to);
    auto colTo = get<1>(to);
    undoTiles.push_back(PositionOfTile(from, map[rowFrom][colFrom]));
    undoTiles.push_back(PositionOfTile(to, map[rowTo][colTo]));

    if (map[rowFrom][colFrom] == Tile::PlayerOnStorage) {
        map[rowFrom][colFrom] = Tile::Storage;
    } else {
        map[rowFrom][colFrom] = Tile::Corridor;
    }

    if (map[rowTo][colTo] == Tile::Storage) {
        map[rowTo][colTo] = Tile::PlayerOnStorage;
        return undoTiles;
    } else if (map[rowTo][colTo] == Tile::Corridor) {
        map[rowTo][colTo] = Tile::Player;
        return undoTiles;
    } else if (map[rowTo][colTo] == Tile::Box) {
        map[rowTo][colTo] = Tile::Player;
    } else {
        map[rowTo][colTo] = Tile::PlayerOnStorage;
    }

    auto rowPushTo = rowTo;
    auto colPushTo = colTo;
    if (rowFrom > rowTo) {
        rowPushTo = rowTo - 1;
    } else if (rowTo > rowFrom) {
        rowPushTo = rowTo + 1;
    } else if (colFrom > colTo) {
        colPushTo = colTo - 1;
    } else {
        colPushTo = colTo + 1;
    }

    undoTiles.push_back(PositionOfTile(Position(rowPushTo, colPushTo), map[rowPushTo][colPushTo]));

    if (map[rowPushTo][colPushTo] == Tile::Storage) {
        map[rowPushTo][colPushTo] = Tile::BoxOnStorage;
    } else {
        map[rowPushTo][colPushTo] = Tile::Box;
    }


    return undoTiles;
}

void Board::restore(UndoTiles undoTiles) {
    for (auto positionOfTile: undoTiles) {
        auto pos = get<0>(positionOfTile);
        auto row = get<0>(pos);
        auto col = get<1>(pos);
        auto tile = get<1>(positionOfTile);
        map[row][col] = tile;
    }
}

