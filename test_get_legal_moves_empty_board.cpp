#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <algorithm>
#include <vector>
#include "board.h"
#include "types.h"

using std::sort;
using std::vector;

struct TestData {
    Position startPos;
    vector<Position> expectedMoves;
};

TEST_CASE("Test legal moves on empty 1x1 board") {
    Board board(1, 1);
    Position startPos = Position(0, 0);
    auto legalMoves = board.getLegalMoves(startPos);
    REQUIRE(legalMoves.empty());
}

TEST_CASE("Test legal moves on empty 2x1 board") {
    Board board(2, 1);

    auto tileType = GENERATE(Tile::Corridor, Tile::Storage);
    auto testData = GENERATE(TestData{Position(0, 0),
                                 vector<Position>{Position(1, 0)}},
                             TestData{Position(1, 0),
                                 vector<Position>{Position(0, 0)}});
    board[0][0] = tileType;
    board[1][0] = tileType;
    auto startPos = testData.startPos;
    auto expectedMoves = testData.expectedMoves;
    auto legalMoves = board.getLegalMoves(startPos);       
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 1x2 board") {
    Board board(1, 2);

    auto tileType = GENERATE(Tile::Corridor, Tile::Storage);
    auto testData = GENERATE(TestData{Position(0, 0),
                                 vector<Position>{Position(0, 1)}},    
                             TestData{Position(0, 1),
                                 vector<Position>{Position(0, 0)}}); 
    board[0][0] = tileType;
    board[0][1] = tileType;
    auto startPos = testData.startPos;
    auto expectedMoves = testData.expectedMoves;
    auto legalMoves = board.getLegalMoves(startPos);       
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 2x2 board") {
    Board board(2, 2);

    auto tileType = GENERATE(Tile::Corridor, Tile::Storage);
    auto testData = GENERATE(TestData{Position(0, 0), vector<Position> {
                                 Position(0, 1), Position(1, 0)}},
                             TestData{Position(0, 1), vector<Position> {
                                 Position(0, 0), Position(1, 1) }},
                             TestData{Position(1, 1), vector<Position> {
                                 Position(1, 0), Position(0, 1) }},
                             TestData{Position(1, 0), vector<Position> {
                                 Position(0, 0), Position(1, 1) }});
    for (unsigned int row = 0; row < 2; ++row)
        for (unsigned int col = 0; col < 2; ++col)
            board[row][col] = tileType;

    auto startPos = testData.startPos;
    auto expectedMoves = testData.expectedMoves;
    auto legalMoves = board.getLegalMoves(startPos);

    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());

    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 3x3 board") {
    Board board(3, 3);

    auto tileType = GENERATE(Tile::Corridor, Tile::Storage);
    auto testData = GENERATE(TestData{Position(0, 0), vector<Position> {
                                 Position(0, 1), Position(1, 0)}},
                             TestData{Position(0, 1), vector<Position> {
                                 Position(0, 0), Position(1, 1),
                                 Position(0, 2) }},
                             TestData{Position(1, 1), vector<Position> {
                                 Position(1, 0), Position(0, 1),
                                 Position(2, 1), Position(1, 2)}},
                             TestData{Position(1, 0), vector<Position> {
                                 Position(0, 0), Position(1, 1),
                                 Position(2, 0) }},
                             TestData{Position(2, 0), vector<Position> {
                                 Position(1, 0), Position(2, 1) }},
                             TestData{Position(2, 1), vector<Position> {
                                 Position(2, 0), Position(2, 2),
                                 Position(1, 1) }},
                             TestData{Position(0, 2), vector<Position> {
                                 Position(0, 1), Position(1, 2) }},
                             TestData{Position(1, 2), vector<Position> {
                                 Position(0, 2), Position(1, 1),
                                 Position(2, 2) }},
                             TestData{Position(2, 2), vector<Position> {
                                 Position(1, 2), Position(2, 1) }});
    for (unsigned int row = 0; row < 3; ++row)
        for (unsigned int col = 0; col < 3; ++col)
            board[row][col] = tileType;

    auto startPos = testData.startPos;
    auto expectedMoves = testData.expectedMoves;
    auto legalMoves = board.getLegalMoves(startPos);

    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());

    REQUIRE(legalMoves == expectedMoves);
}

