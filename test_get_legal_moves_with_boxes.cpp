#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <algorithm>
#include <tuple>
#include <vector>
#include "board.h"
#include "types.h"

using std::get;
using std::sort;
using std::tuple;
using std::vector;

TEST_CASE("Test legal moves on empty 2x1 board") {
    Board board(2, 1);
    board[0][0] = Tile::Box;

    auto startPos = Position(1, 0);
    auto expectedMoves = vector<Position>();
    auto legalMoves = board.getLegalMoves(startPos);       
    REQUIRE(legalMoves == expectedMoves);

    board[0][0] = Tile::Corridor;
    board[1][0] = Tile::Box;
    startPos = Position(0, 0);
    expectedMoves = vector<Position>();
    legalMoves = board.getLegalMoves(startPos);       
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 1x2 board") {
    Board board(1, 2);
    board[0][0] = Tile::Box;

    auto startPos = Position(0, 1);
    auto expectedMoves = vector<Position>();
    auto legalMoves = board.getLegalMoves(startPos);       
    REQUIRE(legalMoves == expectedMoves);

    board[0][0] = Tile::Corridor;
    board[0][1] = Tile::Box;
    startPos = Position(0, 0);
    legalMoves = board.getLegalMoves(startPos);       
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 2x2 board") {
    Board board(2, 2);

    using tuple_type = tuple<Position, vector<Position>, vector<Position>>;
    auto dump = GENERATE(table<Position, vector<Position>, vector<Position>>( {
                tuple_type{ Position(0, 0),
                            vector<Position> { Position(1, 0) },
                            vector<Position> { Position(0, 1) }},
                tuple_type{ Position(0, 0),
                            vector<Position> { Position(1, 0) },
                            vector<Position> { Position(0, 1) }},
                tuple_type{ Position(0, 0),
                            vector<Position> { Position(0, 1), Position(1, 0) },
                            vector<Position> { }},
                tuple_type{ Position(0, 1),
                            vector<Position> { Position(0, 0) },
                            vector<Position> { Position(1, 1) }},
                tuple_type{ Position(0, 1),
                            vector<Position> { Position(1, 1) },
                            vector<Position> { Position(0, 0) }},
                tuple_type{ Position(0, 1),
                            vector<Position> { Position(0, 0), Position(1, 1) },
                            vector<Position> { }},
                tuple_type{ Position(1, 0),
                            vector<Position> { Position(0, 0) },
                            vector<Position> { Position(1, 1) }},
                tuple_type{ Position(1, 0),
                            vector<Position> { Position(1, 1) },
                            vector<Position> { Position(0, 0) }},
                tuple_type{ Position(1, 0),
                            vector<Position> { Position(1, 1), Position(0, 0) },
                            vector<Position> { }},
                tuple_type{ Position(1, 1),
                            vector<Position> { Position(0, 1) },
                            vector<Position> { Position(1, 0) }},
                tuple_type{ Position(1, 1),
                            vector<Position> { Position(1, 0) },
                            vector<Position> { Position(0, 1) }},
                tuple_type{ Position(1, 1),
                            vector<Position> { Position(1, 0), Position(0, 1) },
                            vector<Position> { }}
                }));
    auto startPos = get<0>(dump);
    auto boxPos = get<1>(dump);
    auto expectedMoves = get<2>(dump);
    for (auto box: boxPos) {
        board[get<0>(box)][get<1>(box)] = Tile::Box;
    }

    auto legalMoves = board.getLegalMoves(startPos);

    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());

    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 3x3 board") {
    Board board(3, 3);

    using tuple_type = tuple<Position, vector<Position>, vector<Position>>;
    auto dump = GENERATE(table<Position, vector<Position>, vector<Position>>( {
                tuple_type{ Position(0, 0),
                            vector<Position> { Position(1, 0) },
                            vector<Position> { Position(0, 1), Position(1, 0) }},
                tuple_type{ Position(0, 0),
                            vector<Position> { Position(1, 0) },
                            vector<Position> { Position(0, 1), Position(1, 0) }},
                tuple_type{ Position(0, 0),
                            vector<Position> { Position(0, 1), Position(1, 0) },
                            vector<Position> { Position(0, 1), Position(1, 0) }},
                tuple_type{ Position(0, 1),
                            vector<Position> { Position(0, 0) },
                            vector<Position> { Position(1, 1), Position(0, 2) }},
                tuple_type{ Position(0, 1),
                            vector<Position> { Position(1, 1) },
                            vector<Position> { Position(0, 0), Position(1, 1), Position(0, 2) }},
                tuple_type{ Position(0, 1),
                            vector<Position> { Position(0, 2) },
                            vector<Position> { Position(0, 0), Position(1, 1) }},
                tuple_type{ Position(0, 1),
                            vector<Position> { Position(0, 0), Position(1, 1) },
                            vector<Position> { Position(0, 2), Position(1, 1) }},
                tuple_type{ Position(1, 0),
                            vector<Position> { Position(0, 0) },
                            vector<Position> { Position(1, 1), Position(2, 0) }},
                tuple_type{ Position(1, 0),
                            vector<Position> { Position(1, 1) },
                            vector<Position> { Position(0, 0), Position(1, 1), Position(2, 0) }},
                tuple_type{ Position(1, 0),
                            vector<Position> { Position(2, 0) },
                            vector<Position> { Position(0, 0), Position(1, 1) }},
                tuple_type{ Position(1, 0),
                            vector<Position> { Position(0, 0), Position(1, 1) },
                            vector<Position> { Position(2, 0), Position(1, 1) }},
                tuple_type{ Position(1, 1),
                            vector<Position> { Position(0, 1), Position(2, 1) },
                            vector<Position> { Position(1, 0), Position(1, 2) }},
                tuple_type{ Position(1, 1),
                            vector<Position> { Position(1, 0), Position(1, 2) },
                            vector<Position> { Position(0, 1), Position(2, 1) }},
                tuple_type{ Position(1, 1),
                            vector<Position> { Position(2, 1), Position(1, 2) },
                            vector<Position> { Position(0, 1), Position(1, 0) }},
                tuple_type{ Position(1, 1),
                            vector<Position> { Position(0, 1), Position(1, 0) },
                            vector<Position> { Position(2, 1), Position(1, 2) }},
                }));
    auto startPos = get<0>(dump);
    auto boxPos = get<1>(dump);
    auto expectedMoves = get<2>(dump);
    for (auto box: boxPos) {
        board[get<0>(box)][get<1>(box)] = Tile::Box;
    }

    auto legalMoves = board.getLegalMoves(startPos);

    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());

    REQUIRE(legalMoves == expectedMoves);
}

