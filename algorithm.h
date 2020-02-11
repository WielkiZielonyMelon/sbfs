#pragma once
#include <unordered_set>
#include "board.h"
#include "types.h"

class Algorithm {
private:
    Board board;
    std::unordered_set<Board> setOfBoards;
    void _get_solution(Solution& solution, Position position);

public:
    Algorithm(Board& b);
    Solution get_solution();
};

