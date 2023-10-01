#include "knight.h"

#include <memory>
#include <vector>

#include "../board/board.h"
#include "../move/move.h"

Knight::Knight(char letter, std::shared_ptr<Board> board): Piece{letter, board, false, 3} {}

std::vector<std::pair<char, int>> Knight::getMoves(std::pair<char, int> start) {
    std::vector<std::pair<char, int>> moves;
    for (int i = -2; i <= 2; i++) {
        if (i == 0) {
            continue;
        }
        if (canMoveTo(start, {start.first + i, start.second + 3 - abs(i)})) {
            moves.emplace_back(start.first + i, start.second + 3 - abs(i));
        }
        if (canMoveTo(start, {start.first + i, start.second - 3 + abs(i)})) {
            moves.emplace_back(start.first + i, start.second - 3 + abs(i));
        }
    }
    return moves;
}

bool Knight::canMoveTo(std::pair<char, int> start, std::pair<char, int> end) {
    if (end.first < 'a' || end.first > 'h' || end.second < 1 || end.second > 8) {
        return false;
    }
    auto nextPiece = board->getSquare(end.first, end.second)->getPiece();
    if (nextPiece && nextPiece->isWhite() == isWhite()) {
        return false;
    }
    if (start.first == end.first) {
        return false;
    }
    if (start.second == end.second) {
        return false;
    }
    if (abs(start.first - end.first) == 1 && abs(start.second - end.second) == 2) {
        return true;
    }
    if (abs(start.first - end.first) == 2 && abs(start.second - end.second) == 1) {
        return true;
    }
    return false;
}

bool Knight::move(std::pair<char, int> start, std::pair<char, int> end, std::istream &in) {
    if (canMoveTo(start, end)) {
        std::shared_ptr<Move> mv = std::make_shared<Move>();
        board->movePiece(start, end, mv);
        board->addLastMove(mv);
        return true;
    }
    return false;
}
