#ifndef MOVE_H
#define MOVE_H

#include <memory>
#include <stack>
#include <vector>

struct Move {
    std::vector<std::pair<char, std::pair<char, int>>> pieceRemoved;
    std::vector<std::pair<char, std::pair<char, int>>> pieceAdded;
    std::pair<char, int> enPassant = {' ', 0};
    bool isUndo = false;
    Move(): pieceRemoved(), pieceAdded() {}
    ~Move() {}
};

#endif // MOVE_H
