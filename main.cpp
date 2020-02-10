#include <iostream>
#include <array>
#include <functional>
#include <tuple>
#include <unordered_set>
#include <vector>

using std::cout;
using std::endl;
using std::array;
using std::get;
using std::hash;
using std::tuple;
using std::unordered_set;
using std::vector;


enum Tile { Corridor, Wall, Player, Box, Storage,
    PlayerOnStorage, BoxOnStorage };

typedef tuple<unsigned int, unsigned int> Position;
typedef tuple<Position, Tile> PositionOfTile;
typedef vector<Position> Solution;
typedef vector<PositionOfTile> UndoTiles;

class Board {
private:
    unsigned int rows;
    unsigned int cols;
    vector<vector<Tile>> map;
public:
    Board(unsigned int _rows, unsigned int _cols) :
        rows(_rows), cols(_cols), map(rows, vector<Tile>(cols))  {}

    void print(void) {
        for (auto row: map) {
            for (auto tile: row) {
                cout << static_cast<int>(tile);
            }
            cout << endl;
        }
    }

    auto getRows() const noexcept {
        return rows;
    }

    auto getCols() const noexcept {
        return cols;
    }

    const vector<Tile>& operator[](unsigned int row) const {
        return map[row];
    }

    vector<Tile>& operator[](unsigned int row) {
        return map[row];
    }

    bool operator==(const Board& o) const {
        for (unsigned int row = 0; row < rows; ++row) {
            for (unsigned int col = 0; col < cols; ++col) {
                if (map[row][col] != o[row][col]) {
                    return false;
                }
            }
        }

        return true;
    }

    bool isSolved() const {
        for (unsigned int row = 0; row < rows; ++row) {
            for (unsigned int col = 0; col < cols; ++col) {
                if (map[row][col] == Box) {
                    return false;
                }
            }
        }

        return true;
    }

    Position findPlayerPosition() const {
        for (unsigned int row = 0; row < rows; ++row) {
            for (unsigned int col = 0; col < cols; ++col) {
                if (map[row][col] == Tile::Player) {
                    return Position(row, col);
                }
            }
        }

        throw;
    }

    vector<Position> getLegalMoves(Position position) const {
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

    UndoTiles move(Position from, Position to) {
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

    void restore(UndoTiles undoTiles) {
        for (auto positionOfTile: undoTiles) {
            auto pos = get<0>(positionOfTile);
            auto row = get<0>(pos);
            auto col = get<1>(pos);
            auto tile = get<1>(positionOfTile);
            map[row][col] = tile;
        }
    }
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

class Algorithm {
private:
    Board board;
    unordered_set<Board> setOfBoards;
public:
    Algorithm(Board& b) : board(b) {}
    Solution get_solution() {
        Solution solution;
        _get_solution(solution, board.findPlayerPosition());
        return solution;
    }

    void _get_solution(Solution& solution, Position position) {
	auto search = setOfBoards.find(board);
	if (search != setOfBoards.end()) {
            cout << "Terminate this branch" << endl;
            return;
	}
	setOfBoards.insert(board);

        if (board.isSolved()) {
            cout << "Solution is:" << endl;
            for (auto pos: solution) {
                cout << get<0>(pos) << " " << get<1>(pos) << endl;
            }
            throw;
        }

        vector<Position> newPositions = board.getLegalMoves(position);
        for (auto positionTo: newPositions) {
            cout << "Moving to " << get<0>(positionTo) << " " << get<1>(positionTo) << endl;
            auto undo_tiles = board.move(position, positionTo);
            board.print();
            solution.push_back(positionTo);
            _get_solution(solution, positionTo);
            board.restore(undo_tiles);
            solution.pop_back();
        }
    }
};

int main() {
    Board b = Board(3, 3);
    b[0][0] = Tile::Player;
    b[0][1] = Tile::Box;
    b[0][2] = Tile::Storage;

    b.print();
    Algorithm a = Algorithm(b);
    a.get_solution();
    return 0;
}
