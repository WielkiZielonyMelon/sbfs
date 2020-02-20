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
    Position endPos;
};

struct TileBeforeAfter {
    Tile before;
    Tile after;
};

TEST_CASE("Test move on empty 3x3 board") {
    Board board(3, 3);

    auto startTileType =  GENERATE(TileBeforeAfter{Tile::Player,
                                                   Tile::Corridor},
                                   TileBeforeAfter{Tile::PlayerOnStorage,
                                                   Tile::Storage});
    auto endTileType = GENERATE(TileBeforeAfter{Tile::Corridor,
                                                Tile::Player},
                                TileBeforeAfter{Tile::Storage,
                                                Tile::PlayerOnStorage});
    auto testData = GENERATE(TestData{Position(0, 0), Position(0, 1)},
                             TestData{Position(0, 1), Position(0, 0)},
                             TestData{Position(0, 0), Position(1, 0)},
                             TestData{Position(1, 0), Position(0, 0)},

                             TestData{Position(1, 1), Position(0, 1)},
                             TestData{Position(0, 1), Position(1, 1)},
                             TestData{Position(1, 1), Position(1, 0)},
                             TestData{Position(1, 0), Position(1, 1)},
                             TestData{Position(1, 1), Position(2, 1)},
                             TestData{Position(2, 1), Position(1, 1)},
                             TestData{Position(1, 1), Position(1, 2)},
                             TestData{Position(1, 2), Position(1, 1)},

                             TestData{Position(0, 2), Position(0, 1)},
                             TestData{Position(0, 1), Position(0, 2)},
                             TestData{Position(0, 2), Position(1, 2)},
                             TestData{Position(1, 2), Position(1, 1)},

                             TestData{Position(2, 2), Position(2, 1)},
                             TestData{Position(2, 1), Position(2, 2)},
                             TestData{Position(2, 2), Position(1, 2)},
                             TestData{Position(1, 2), Position(2, 2)});
    auto startPos = testData.startPos;
    auto endPos = testData.endPos;
    board[get<0>(startPos)][get<1>(startPos)] = startTileType.before;
    board[get<0>(endPos)][get<1>(endPos)] = endTileType.before;

    board.move(startPos, endPos);

    REQUIRE(board[get<0>(startPos)][get<1>(startPos)] == startTileType.after);
    REQUIRE(board[get<0>(endPos)][get<1>(endPos)] == endTileType.after);
}

