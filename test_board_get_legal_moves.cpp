#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <algorithm>
#include <vector>
#include "board.h"
#include "types.h"

using std::sort;
using std::vector;
TEST_CASE("Test legal moves on empty 1x1 board") {
    Board board(1, 1);
    Position startPos = Position(0, 0);
    auto legalMoves = board.getLegalMoves(startPos);
    REQUIRE(legalMoves.empty());
}

TEST_CASE("Test legal moves on empty 2x1 board, start 0 0") {
    Board board(2, 1);

    auto startPos = Position(0, 0);
    auto legalMoves = board.getLegalMoves(startPos);
    REQUIRE(legalMoves[0] == Position(1, 0));
}

TEST_CASE("Test legal moves on empty 2x1 board, start 1 0") {
    Board board(2, 1);
    auto startPos = Position(1, 0);
    auto legalMoves = board.getLegalMoves(startPos);

    REQUIRE(legalMoves[0] == Position(0, 0));
}

TEST_CASE("Test legal moves on empty 1x2 board, start 0 0") {
    Board board(1, 2);

    auto startPos = Position(0, 0);
    auto legalMoves = board.getLegalMoves(startPos);
    REQUIRE(legalMoves[0] == Position(0, 1));
}

TEST_CASE("Test legal moves on empty 1x2 board, start 0 1") {
    Board board(1, 2);
    auto startPos = Position(0, 1);
    auto legalMoves = board.getLegalMoves(startPos);

    REQUIRE(legalMoves[0] == Position(0, 0));
}

TEST_CASE("Test legal moves on empty 2x2 board, start 0 0") {
    Board board(2, 2);

    auto startPos = Position(0, 0);
    auto legalMoves = board.getLegalMoves(startPos);
    auto expectedMoves = vector<Position>{Position(1, 0), Position(0, 1)};
    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 2x2 board, start 1 0") {
    Board board(2, 2);

    auto startPos = Position(1, 0);
    auto legalMoves = board.getLegalMoves(startPos);
    auto expectedMoves = vector<Position>{Position(0, 0), Position(1, 1)};
    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 2x2 board, start 0 1") {
    Board board(2, 2);
    
    auto startPos = Position(0, 1);
    auto legalMoves = board.getLegalMoves(startPos);
    auto expectedMoves = vector<Position>{Position(0, 0), Position(1, 1)};
    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 2x2 board, start 1 1") {
    Board board(2, 2);

    auto startPos = Position(1, 1);
    auto legalMoves = board.getLegalMoves(startPos);
    auto expectedMoves = vector<Position>{Position(1, 0), Position(0, 1)};
    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 3x3 board, start 0 0") {
    Board board(3, 3);

    auto startPos = Position(0, 0);
    auto legalMoves = board.getLegalMoves(startPos);
    auto expectedMoves = vector<Position>{Position(1, 0), Position(0, 1)};
    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 3x3 board, start 1 0") {
    Board board(3, 3);

    auto startPos = Position(1, 0);
    auto legalMoves = board.getLegalMoves(startPos);
    auto expectedMoves = vector<Position>{Position(0, 0), Position(1, 1),
                                          Position(2, 0)};
    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 3x3 board, start 2 0") {
    Board board(3, 3);

    auto startPos = Position(2, 0);
    auto legalMoves = board.getLegalMoves(startPos);
    auto expectedMoves = vector<Position>{Position(1, 0),
                                          Position(2, 1)};
    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 3x3 board, start 2 1") {
    Board board(3, 3);

    auto startPos = Position(2, 1);
    auto legalMoves = board.getLegalMoves(startPos);
    auto expectedMoves = vector<Position>{Position(2, 2), Position(1, 1),
                                          Position(2, 0)};
    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 3x3 board, start 0 1") {
    Board board(3, 3);

    auto startPos = Position(0, 1);
    auto legalMoves = board.getLegalMoves(startPos);
    auto expectedMoves = vector<Position>{Position(0, 0), Position(1, 1),
                                          Position(0, 2)};
    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 3x3 board, start 0 2") {
    Board board(3, 3);

    auto startPos = Position(0, 2);
    auto legalMoves = board.getLegalMoves(startPos);
    auto expectedMoves = vector<Position>{Position(0, 1),
                                          Position(1, 2)};
    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 3x3 board, start 1 2") {
    Board board(3, 3);

    auto startPos = Position(1, 2);
    auto legalMoves = board.getLegalMoves(startPos);
    auto expectedMoves = vector<Position>{Position(0, 2), Position(1, 1),
                                          Position(2, 2)};
    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 3x3 board, start 1 1") {
    Board board(3, 3);

    auto startPos = Position(1, 1);
    auto legalMoves = board.getLegalMoves(startPos);
    auto expectedMoves = vector<Position>{Position(1, 0), Position(0, 1),
                                          Position(2, 1), Position(1, 2)};
    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());
    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 3x3 board, start 2 2") {
    Board board(3, 3);

    auto startPos = Position(2, 2);
    auto legalMoves = board.getLegalMoves(startPos);
    auto expectedMoves = vector<Position>{Position(2, 1), Position(1, 2)};
    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());
    REQUIRE(legalMoves == expectedMoves);
}
