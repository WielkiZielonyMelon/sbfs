#include <iostream>
#include <functional>
#include <vector>
#include "algorithm.h"
#include "board.h"

int main() {
    Board b = Board(3, 3);
    b[0][0] = Tile::Player;
    b[0][1] = Tile::Box;
    b[0][2] = Tile::Storage;

    b.print();
    Algorithm a = Algorithm(b);
    a.get_solution();
    return 0;
}
