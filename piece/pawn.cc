#include "pawn.h"

#include <memory>
#include <iostream>
#include <vector>

#include "../board/board.h"
#include "../move/move.h"

Pawn::Pawn(char letter, std::shared_ptr<Board> board): Piece{letter, board, false, 1} {}

std::vector<std::pair<char, int>> Pawn::getMoves(std::pair<char, int> start) {
    std::vector<std::pair<char, int>> moves;
    if (isWhite()) {
        if (canMoveTo(start, {start.first, start.second + 1})) {
            moves.emplace_back(start.first, start.second + 1);
        }
        if (canMoveTo(start, {start.first + 1, start.second + 1})) {
            moves.emplace_back(start.first + 1, start.second + 1);
        }
        if (canMoveTo(start, {start.first - 1, start.second + 1})) {
            moves.emplace_back(start.first - 1, start.second + 1);
        }
        if (canMoveTo(start, {start.first, start.second + 2})) {
            moves.emplace_back(start.first, start.second + 2);
        }
    } else {
        if (canMoveTo(start, {start.first, start.second - 1})) {
            moves.emplace_back(start.first, start.second - 1);
        }
        if (canMoveTo(start, {start.first + 1, start.second - 1})) {
            moves.emplace_back(start.first + 1, start.second - 1);
        }
        if (canMoveTo(start, {start.first - 1, start.second - 1})) {
            moves.emplace_back(start.first - 1, start.second - 1);
        }
        if (canMoveTo(start, {start.first, start.second - 2})) {
            moves.emplace_back(start.first, start.second - 2);
        }
    }
    return moves;
}

bool Pawn::canMoveTo(std::pair<char, int> start, std::pair<char, int> end) {
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
    if (start.first == 8 || start.first == 1) {
        return false;
    }
    if (isWhite()) {
        if (start.second == 2) {
            if (nextPiece != nullptr && start.first == end.first) {
                return false;
            }
            if (start.first == end.first && end.second == 4) {
                canSpecialMove = true;
                return true;
            }
        }
        if (std::abs(end.first - start.first) > 1 || end.second - start.second > 1) {
            return false;
        }
        if (start.first == end.first && end.second == start.second + 1) {
            if (nextPiece != nullptr) {
                return false;
            }
            return true;
        }
        if (std::abs(end.first - start.first) == 1 && end.second - start.second == 1) {
            if (nextPiece != nullptr) {
                return true;
            }
            if (canEnPassant(start, end)) {
                return true;
            }
            return false;
        }
    } else {
        if (start.second == 7) {
            if (nextPiece != nullptr && start.first == end.first) {
                return false;
            }
            if (start.first == end.first && end.second == 5) {
                canSpecialMove = true;
                return true;
            }
        }
        if (std::abs(end.first - start.first) > 1 || start.second - end.second > 1) {
            return false;
        }
        if (start.first == end.first && end.second == start.second - 1) {
            if (nextPiece != nullptr) {
                return false;
            }
            return true;
        }
        if (std::abs(start.first - end.first) == 1 && start.second - end.second == 1) {
            if (nextPiece != nullptr) {
                return true;
            }
            if (canEnPassant(start, end)) {
                return true;
            }
            return false;
        }
    }
    return canEnPassant(start, end);
}

bool Pawn::canEnPassant(std::pair<char, int> start, std::pair<char, int> end) {
    auto nextPiece = board->getSquare(end.first, start.second)->getPiece();
    if (nextPiece == nullptr) {
        return false;
    }
    if ((nextPiece->isWhite() && isWhite()) || (!nextPiece->isWhite() && !isWhite())) {
        return false;
    }
    if (nextPiece->getLetter() != 'P' && nextPiece->getLetter() != 'p') {
        return false;
    }
    if (nextPiece->getCanSpecialMove()) {
        return true;
    }
    return false;
}

bool Pawn::move(std::pair<char, int> start, std::pair<char, int> end, std::istream &in) {
    if (canMoveTo(start, end)) {
        std::shared_ptr<Move> mv = std::make_shared<Move>();
        if (canEnPassant(start, end)) {
            board->movePiece(start, end, mv);
            board->removePiece(end.first, start.second, mv);
            board->addLastMove(mv);
            return true;
        }
        if (end.second == 8 || end.second == 1) {
            char promotion;
            in >> promotion;
            if (isWhite() && !(promotion == 'Q' || promotion == 'R' || promotion == 'B' || promotion == 'N')) {
                return false;
            }
            if (!isWhite() && !(promotion == 'q' || promotion == 'r' || promotion == 'b' || promotion == 'n')) {
                return false;
            }
            board->removePiece(start.first, start.second, mv);
            board->removePiece(end.first, end.second,mv);
            board->addPiece(promotion, end.first, end.second,mv);
        }
        else {
            board->movePiece(start, end, mv);
        }
        board->addLastMove(mv);
        return true;
    }
    return false;
}
