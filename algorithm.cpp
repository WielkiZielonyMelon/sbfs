#include <iostream>
#include <tuple>
#include <vector>
#include "algorithm.h"
#include "board.h"
#include "types.h"

using std::cout;
using std::endl;
using std::get;
using std::vector;

Algorithm::Algorithm(Board& b) : board(b) {}

Solution Algorithm::get_solution() {
    Solution solution;
    _get_solution(solution, board.findPlayerPosition());
    return solution;
}

void Algorithm::_get_solution(Solution& solution, Position position) {
    auto search = setOfBoards.find(board);
    if (search != setOfBoards.end()) {
        cout << "Terminate this branch" << endl;
        return;
    }
    setOfBoards.insert(board);

    if (board.isSolved()) {
        cout << "Solution is:" << endl;
        for (auto pos: solution) {
            cout << get<0>(pos) << " " << get<1>(pos) << endl;
        }
        throw;
    }

    vector<Position> newPositions = board.getLegalMoves(position);
    for (auto positionTo: newPositions) {
        cout << "Moving to " << get<0>(positionTo) << " " << get<1>(positionTo) << endl;
        auto undo_tiles = board.move(position, positionTo);
        board.print();
        solution.push_back(positionTo);
        _get_solution(solution, positionTo);
        board.restore(undo_tiles);
        solution.pop_back();
    }
}
