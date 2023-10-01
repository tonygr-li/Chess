#include "bishop.h"

#include <memory>
#include <vector>

#include "../board/board.h"
#include "../move/move.h"

Bishop::Bishop(char letter, std::shared_ptr<Board> board): Piece{letter, board, false, 3} {}

std::vector<std::pair<char, int>> Bishop::getMoves(std::pair<char, int> start) {
    std::vector<std::pair<char, int>> moves;
    for (int i = 1; i <= 8; i++) {
        if (canMoveTo(start, {start.first + i, start.second + i})) {
            moves.emplace_back(start.first + i, start.second + i);
        }
        if (canMoveTo(start, {start.first + i, start.second - i})) {
            moves.emplace_back(start.first + i, start.second - i);
        }
        if (canMoveTo(start, {start.first - i, start.second + i})) {
            moves.emplace_back(start.first - i, start.second + i);
        }
        if (canMoveTo(start, {start.first - i, start.second - i})) {
            moves.emplace_back(start.first - i, start.second - i);
        }
    }
    return moves;
}

bool Bishop::canMoveTo(std::pair<char, int> start, std::pair<char, int> end) {
    if (end.first < 'a' || end.first > 'h' || end.second < 1 || end.second > 8) {
        return false;
    }
    auto nextPiece = board->getSquare(end.first, end.second)->getPiece();
    if (nextPiece && nextPiece->isWhite() == isWhite()) {
        return false;
    }
    if (board->isPieceBetween(start, end)) {
        return false;
    }
    if (abs(start.first - end.first) == abs(start.second - end.second)) {
        return true;
    }
    return false;
}

bool Bishop::move(std::pair<char, int> start, std::pair<char, int> end, std::istream &in) {
    if (canMoveTo(start, end)) {
        std::shared_ptr<Move> mv = std::make_shared<Move>();
        board->movePiece(start, end, mv);
        board->addLastMove(mv);
        return true;
    }
    return false;
}
