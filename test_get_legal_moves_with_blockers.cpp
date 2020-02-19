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
    vector<Position> blockerPos;
    vector<Position> expectedMoves;
};


TEST_CASE("Test legal moves on empty 3x3 board") {
    Board board(3, 3);

    auto blockerType0 = GENERATE(Tile::Box, Tile::BoxOnStorage, Tile::Wall);
    auto blockerType1 = GENERATE(Tile::Box, Tile::BoxOnStorage, Tile::Wall);

    auto testData = GENERATE(TestData{Position(0, 0),
                                 vector<Position>{Position(1, 0),
                                                  Position(2, 0)},
                                 vector<Position>{Position(0, 1)}},
                             TestData{Position(0, 0),
                                 vector<Position>{Position(0, 1),
                                                  Position(0, 2)},
                                 vector<Position>{Position(1, 0)}},
                             TestData{Position(0, 1),
                                 vector<Position>{Position(1, 1),
                                                  Position(2, 1)},
                                 vector<Position>{Position(0, 0),
                                                  Position(0, 2)}},
                             TestData{Position(1, 0),
                                 vector<Position>{Position(1, 1),
                                                  Position(1, 2)},
                                 vector<Position>{Position(0, 0),
                                                  Position(2, 0)}},
                             TestData{Position(2, 2),
                                 vector<Position>{Position(2, 1),
                                                  Position(2, 0)},
                                 vector<Position>{Position(1, 2)}},
                             TestData{Position(2, 2),
                                 vector<Position>{Position(1, 2),
                                                  Position(0, 2)},
                                 vector<Position>{Position(2, 1)}});

    auto startPos = testData.startPos;
    auto blockerPos = testData.blockerPos;
    auto expectedMoves = testData.expectedMoves;
    board[get<0>(blockerPos[0])][get<1>(blockerPos[0])] = blockerType0;
    board[get<0>(blockerPos[1])][get<1>(blockerPos[1])] = blockerType1;

    auto legalMoves = board.getLegalMoves(startPos);

    sort(legalMoves.begin(), legalMoves.end());
    sort(expectedMoves.begin(), expectedMoves.end());

    REQUIRE(legalMoves == expectedMoves);
}

