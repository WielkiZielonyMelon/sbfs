#pragma once
#include <vector>
#include "types.h"

class Board {
private:
    unsigned int rows;
    unsigned int cols;
    std::vector<std::vector<Tile>> map;
public:
    Board(unsigned int _rows, unsigned int _cols);
    void print(void);
    unsigned int getRows() const noexcept;
    unsigned int getCols() const noexcept;
    const std::vector<Tile>& operator[](unsigned int row) const;
    std::vector<Tile>& operator[](unsigned int row);
    bool operator==(const Board& o) const;
    bool isSolved() const;
    Position findPlayerPosition() const;
    std::vector<Position> getLegalMoves(Position position) const;
    UndoTiles move(Position from, Position to);
    void restore(UndoTiles undoTiles);
};

namespace std {
    template <> struct hash<Board> {
        auto operator()(const Board& b) const noexcept {
            size_t h = 0;
            for (unsigned int row = 0; row < b.getRows(); ++row) {
                for (unsigned int col = 0; col < b.getCols(); ++col) {
                    h ^= hash<Tile>{}(b[row][col]);
                }
            }

            return h;
        }
    };
}

