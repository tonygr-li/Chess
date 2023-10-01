#include "queen.h"

#include <memory>
#include <vector>

#include "../board/board.h"
#include "../move/move.h"

Queen::Queen(char letter, std::shared_ptr<Board> board): Piece{letter, board, false, 9} {}

std::vector<std::pair<char, int>> Queen::getMoves(std::pair<char, int> start) {
    std::vector<std::pair<char, int>> moves;
    for (char rank = 'a'; rank <= 'h'; rank++) {
        for (int file = 1; file <= 8; file++) {
            if (canMoveTo(start, {rank, file})) {
                moves.push_back({rank, file});
            }
        }
    }
    return moves;
}

bool Queen::canMoveTo(std::pair<char, int> start, std::pair<char, int> end) {
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
    if (start.first == end.first) {
        return true;
    }
    if (start.second == end.second) {
        return true;
    }
    if (abs(start.first - end.first) == abs(start.second - end.second)) {
        return true;
    }
    return false;
}

bool Queen::move(std::pair<char, int> start, std::pair<char, int> end, std::istream &in) {
    if (canMoveTo(start, end)) {
        std::shared_ptr<Move> mv = std::make_shared<Move>();
        board->movePiece(start, end, mv);
        board->addLastMove(mv);
        return true;
    }
    return false;
}
