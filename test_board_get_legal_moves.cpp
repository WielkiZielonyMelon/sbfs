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

TEST_CASE("Test legal moves on empty 1x1 board") {
    Board board(1, 1);
    Position startPos = Position(0, 0);
    auto legalMoves = board.getLegalMoves(startPos);
    REQUIRE(legalMoves.empty());
}

TEST_CASE("Test legal moves on empty 2x1 board") {
    Board board(2, 1);

    auto dump = GENERATE(vector<Position>{ Position(0, 0), Position(1, 0) },    
                         vector<Position>{ Position(1, 0), Position(0, 0) }); 
    auto startPos = dump[0];
    auto expectedMoves = dump[1];       
    auto legalMoves = board.getLegalMoves(startPos);       
    REQUIRE(legalMoves[0] == expectedMoves);
}

TEST_CASE("Test legal moves on empty 1x2 board") {
    Board board(1, 2);

    auto dump = GENERATE(vector<Position>{ Position(0, 0), Position(0, 1) },    
                         vector<Position>{ Position(0, 1), Position(0, 0) }); 
    auto startPos = dump[0];
    auto expectedMoves = dump[1];       
    auto legalMoves = board.getLegalMoves(startPos);       
    REQUIRE(legalMoves[0] == expectedMoves);
}

TEST_CASE("Test legal moves on empty 2x2 board") {
    Board board(2, 2);

    using tuple_type = tuple<Position, vector<Position>>;
    auto dump = GENERATE(table<Position, vector<Position>>( {
                tuple_type{ Position(0, 0), vector<Position> {
                            Position(0, 1), Position(1, 0) }},
                tuple_type{ Position(0, 1), vector<Position> {
                            Position(0, 0), Position(1, 1) }},
                tuple_type{ Position(1, 1), vector<Position> {
                            Position(1, 0), Position(0, 1) }},
                tuple_type{ Position(1, 0), vector<Position> {
                            Position(0, 0), Position(1, 1) }}
                }));
    auto startPos = get<0>(dump);
    auto expectedMoves = get<1>(dump);
    auto legalMoves = board.getLegalMoves(startPos);

    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());

    REQUIRE(legalMoves == expectedMoves);
}

TEST_CASE("Test legal moves on empty 3x3 board") {
    Board board(3, 3);

    using tuple_type = tuple<Position, vector<Position>>;
    auto dump = GENERATE(table<Position, vector<Position>>( {
                tuple_type{ Position(0, 0), vector<Position> {
                            Position(0, 1), Position(1, 0) }},
                tuple_type{ Position(0, 1), vector<Position> {
                            Position(0, 0), Position(1, 1), Position(0, 2) }},
                tuple_type{ Position(1, 1), vector<Position> {
                            Position(1, 0), Position(0, 1), Position(2, 1),
                            Position(1, 2)}},
                tuple_type{ Position(1, 0), vector<Position> {
                            Position(0, 0), Position(1, 1), Position(2, 0) }},
                tuple_type{ Position(2, 0), vector<Position> {
                            Position(1, 0), Position(2, 1) }},
                tuple_type{ Position(2, 1), vector<Position> {
                            Position(2, 0), Position(2, 2), Position(1, 1) }},
                tuple_type{ Position(0, 2), vector<Position> {
                            Position(0, 1), Position(1, 2) }},
                tuple_type{ Position(1, 2), vector<Position> {
                            Position(0, 2), Position(1, 1), Position(2, 2) }},
                tuple_type{ Position(2, 2), vector<Position> {
                            Position(1, 2), Position(2, 1) }}
                }));
    auto startPos = get<0>(dump);
    auto expectedMoves = get<1>(dump);
    auto legalMoves = board.getLegalMoves(startPos);

    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());

    REQUIRE(legalMoves == expectedMoves);
}

