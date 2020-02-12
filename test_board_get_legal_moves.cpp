#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "board.h"
#include "types.h"

TEST_CASE("Test legal moves on empty 1x1 board") {
    Board board(1, 1);
    Position startPos = Position(0, 0);
    auto legalMoves = board.getLegalMoves(startPos);
    REQUIRE(legalMoves.empty());
}

TEST_CASE("Test legal moves on empty 2x1 board") {
    Board board(2, 1);

    Position startPos = Position(0, 0);
    auto legalMoves = board.getLegalMoves(startPos);
    REQUIRE(legalMoves[0] == Position(1, 0));

    startPos = Position(1, 0);
    legalMoves = board.getLegalMoves(startPos);

    REQUIRE(legalMoves[0] == Position(0, 0));
}

TEST_CASE("Test legal moves on empty 1x2 board") {
    Board board(1, 2);

    Position startPos = Position(0, 0);
    auto legalMoves = board.getLegalMoves(startPos);
    REQUIRE(legalMoves[0] == Position(0, 1));

    startPos = Position(0, 1);
    legalMoves = board.getLegalMoves(startPos);

    REQUIRE(legalMoves[0] == Position(0, 0));
}
