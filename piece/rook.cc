#include "rook.h"

#include <memory>

#include "../board/board.h"
#include "../move/move.h"

Rook::Rook(char letter, std::shared_ptr<Board> board): Piece{letter, board, true, 5} {}

std::vector<std::pair<char, int>> Rook::getMoves(std::pair<char, int> start) {
    std::vector<std::pair<char, int>> moves;
    for (char rank = 'a'; rank <= 'h'; rank++) {
        if (rank != start.first && canMoveTo(start, {rank, start.second})) {
            moves.emplace_back(rank, start.second);
        }
    }
    for (int file = 1; file <= 8; file++) {
        if (file != start.second && canMoveTo(start, {start.first, file})) {
            moves.emplace_back(start.first, file);
        }
    }
    return moves;
}

bool Rook::canMoveTo(std::pair<char, int> start, std::pair<char, int> end) {
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
    return false;
}

bool Rook::move(std::pair<char, int> start, std::pair<char, int> end, std::istream &in) {
    if (canMoveTo(start, end)) {
        std::shared_ptr<Move> mv = std::make_shared<Move>();
        canSpecialMove = false;
        board->movePiece(start, end, mv);
        board->addLastMove(mv);
        return true;
    }
    return false;
}
