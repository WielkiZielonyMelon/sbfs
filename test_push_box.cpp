#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <algorithm>
#include <tuple>
#include <vector>
#include "board.h"
#include "types.h"

using std::get;
using std::sort;
using std::vector;

struct TestData {
    Position startPos;
    Position boxFrom;
    Position boxTo;
};

struct TileBeforeAfter {
    Tile before;
    Tile after;
};

TEST_CASE("Test move on empty 3x3 board") {
    Board board(3, 3);

    auto playerTile =  GENERATE(TileBeforeAfter{Tile::Player,
                                                Tile::Corridor},
                                TileBeforeAfter{Tile::PlayerOnStorage,
                                                Tile::Storage});
    auto boxTile = GENERATE(TileBeforeAfter{Tile::Box,
                                            Tile::Player},
                            TileBeforeAfter{Tile::BoxOnStorage,
                                            Tile::PlayerOnStorage});
    auto destinationTile = GENERATE(TileBeforeAfter{Tile::Corridor,
                                                    Tile::Box},
                                    TileBeforeAfter{Tile::Storage,
                                                    Tile::BoxOnStorage});
    auto testData = GENERATE(TestData{Position(0, 0),
                                      Position(0, 1), Position(0, 2)},
                             TestData{Position(0, 0),
                                      Position(1, 0), Position(2, 0)},

                             TestData{Position(0, 2),
                                      Position(0, 1), Position(0, 0)},
                             TestData{Position(0, 2),
                                      Position(1, 2), Position(2, 2)},

                             TestData{Position(2, 2),
                                      Position(2, 1), Position(2, 0)},
                             TestData{Position(2, 2),
                                      Position(1, 2), Position(0, 2)});

    auto startPos = testData.startPos;
    auto boxFrom = testData.boxFrom;
    auto boxTo = testData.boxTo;
    board[get<0>(startPos)][get<1>(startPos)] = playerTile.before;
    board[get<0>(boxFrom)][get<1>(boxFrom)] = boxTile.before;
    board[get<0>(boxTo)][get<1>(boxTo)] = destinationTile.before;

    board.move(startPos, boxFrom);

    REQUIRE(board[get<0>(startPos)][get<1>(startPos)] == playerTile.after);
    REQUIRE(board[get<0>(boxFrom)][get<1>(boxFrom)] == boxTile.after);
    REQUIRE(board[get<0>(boxTo)][get<1>(boxTo)] == destinationTile.after);
}

