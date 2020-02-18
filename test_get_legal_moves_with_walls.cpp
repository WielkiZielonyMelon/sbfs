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

struct TestData {
    Position startPos;
    vector<Position> wallPos;
    vector<Position> expectedMoves;
};

TEST_CASE("Test legal moves on empty 2x1 board") {
    Board board(2, 1);
    board[0][0] = Tile::Wall;

    auto startPos = Position(1, 0);
    auto expectedMoves = vector<Position>();
    auto legalMoves = board.getLegalMoves(startPos);       
    REQUIRE(legalMoves == expectedMoves);

    board[0][0] = Tile::Corridor;
    board[1][0] = Tile::Wall;
    startPos = Position(0, 0);
    legalMoves = board.getLegalMoves(startPos);       
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 1x2 board") {
    Board board(1, 2);
    board[0][0] = Tile::Wall;

    auto startPos = Position(0, 1);
    auto expectedMoves = vector<Position>();
    auto legalMoves = board.getLegalMoves(startPos);       
    REQUIRE(legalMoves == expectedMoves);

    board[0][0] = Tile::Corridor;
    board[0][1] = Tile::Wall;
    startPos = Position(0, 0);
    legalMoves = board.getLegalMoves(startPos);       
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 2x2 board") {
    Board board(2, 2);

    auto testData = GENERATE(TestData{Position(0, 0),
                                 vector<Position> {Position(1, 0)},
                                 vector<Position> {Position(0, 1)}},
                             TestData{Position(0, 0),
                                 vector<Position> {Position(1, 0)},
                                 vector<Position> {Position(0, 1)}},
                             TestData{Position(0, 0),
                                 vector<Position> {Position(0, 1),
                                                   Position(1, 0)},
                                 vector<Position> { }},
                             TestData{Position(0, 1),
                                 vector<Position> {Position(0, 0)},
                                 vector<Position> {Position(1, 1)}},
                             TestData{Position(0, 1),
                                 vector<Position> {Position(1, 1)},
                                 vector<Position> {Position(0, 0)}},
                             TestData{Position(0, 1),
                                 vector<Position> {Position(0, 0),
                                                   Position(1, 1)},
                                 vector<Position> { }},
                             TestData{Position(1, 0),
                                 vector<Position> {Position(0, 0)},
                                 vector<Position> {Position(1, 1)}},
                             TestData{Position(1, 0),
                                 vector<Position> {Position(1, 1)},
                                 vector<Position> {Position(0, 0)}},
                             TestData{ Position(1, 0),
                                 vector<Position> {Position(1, 1),
                                                    Position(0, 0)},
                                 vector<Position> { }},
                             TestData{ Position(1, 1),
                                 vector<Position> {Position(0, 1)},
                                 vector<Position> {Position(1, 0)}},
                             TestData{ Position(1, 1),
                                 vector<Position> {Position(1, 0)},
                                 vector<Position> {Position(0, 1)}},
                             TestData{ Position(1, 1),
                                 vector<Position> {Position(1, 0),
                                                   Position(0, 1)},
                                 vector<Position> { }});
    auto startPos = testData.startPos;
    auto wallPos = testData.wallPos;
    auto expectedMoves = testData.expectedMoves;
    for (auto wall: wallPos) {
        board[get<0>(wall)][get<1>(wall)] = Tile::Wall;
    }

    auto legalMoves = board.getLegalMoves(startPos);

    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());

    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 3x3 board") {
    Board board(3, 3);

    auto testData = GENERATE(TestData{Position(0, 0),
                                 vector<Position> {Position(1, 0)},
                                 vector<Position> {Position(0, 1)}},
                             TestData{ Position(0, 0),
                                 vector<Position> {Position(1, 0)},
                                 vector<Position> {Position(0, 1)}},
                             TestData{ Position(0, 0),
                                 vector<Position> {Position(0, 1),
                                                   Position(1, 0) },
                                 vector<Position> { }},
                             TestData{ Position(0, 1),
                                 vector<Position> {Position(0, 0) },
                                 vector<Position> {Position(1, 1),
                                                   Position(0, 2) }},
                             TestData{ Position(0, 1),
                                 vector<Position> {Position(1, 1)},
                                 vector<Position> {Position(0, 0),
                                                   Position(0, 2) }},
                             TestData{ Position(0, 1),
                                 vector<Position> {Position(0, 2) },
                                 vector<Position> {Position(0, 0),
                                                   Position(1, 1) }},
                             TestData{ Position(0, 1),
                                 vector<Position> {Position(0, 0),
                                                   Position(1, 1) },
                                 vector<Position> {Position(0, 2)}},
                             TestData{ Position(1, 0),
                                 vector<Position> {Position(0, 0)},
                                 vector<Position> {Position(1, 1),
                                                   Position(2, 0) }},
                             TestData{ Position(1, 0),
                                 vector<Position> {Position(1, 1)},
                                 vector<Position> {Position(0, 0),
                                                   Position(2, 0) }},
                             TestData{ Position(1, 0),
                                 vector<Position> {Position(2, 0)},
                                 vector<Position> {Position(0, 0),
                                                   Position(1, 1) }},
                             TestData{ Position(1, 0),
                                 vector<Position> {Position(0, 0),
                                                   Position(1, 1) },
                                 vector<Position> {Position(2, 0)}},
                             TestData{ Position(1, 1),
                                 vector<Position> {Position(0, 1),
                                                   Position(2, 1) },
                                 vector<Position> {Position(1, 0),
                                                   Position(1, 2) }},
                             TestData{ Position(1, 1),
                                 vector<Position> {Position(1, 0),
                                                   Position(1, 2) },
                                 vector<Position> {Position(0, 1),
                                                   Position(2, 1) }},
                             TestData{ Position(1, 1),
                                 vector<Position> {Position(2, 1),
                                                   Position(1, 2) },
                                 vector<Position> {Position(0, 1),
                                                   Position(1, 0) }},
                             TestData{ Position(1, 1),
                                 vector<Position> {Position(0, 1),
                                                   Position(1, 0) },
                                 vector<Position> {Position(2, 1),
                                                   Position(1, 2) }});
    auto startPos = testData.startPos;
    auto wallPos = testData.wallPos;
    auto expectedMoves = testData.expectedMoves;
    for (auto wall: wallPos) {
        board[get<0>(wall)][get<1>(wall)] = Tile::Wall;
    }

    auto legalMoves = board.getLegalMoves(startPos);

    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());

    REQUIRE(legalMoves == expectedMoves);
}

