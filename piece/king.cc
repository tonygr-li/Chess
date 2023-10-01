#include "king.h"

#include <iostream>
#include <memory>
#include <vector>

#include "../board/board.h"
#include "../move/move.h"

King::King(char letter, std::shared_ptr<Board> board): Piece{letter, board, true, 100} {}

std::vector<std::pair<char, int>> King::getMoves(std::pair<char, int> from) {
    std::vector<std::pair<char, int>> moves;
    for (char rank = from.first - 1; rank <= from.first + 1; rank++) {
        for (int file = from.second - 1; file <= from.second + 1; file++) {
            if (rank == from.first && file == from.second) {
                continue;
            }
            if (canMoveTo(from, {rank, file})) {
                moves.emplace_back(rank, file);
            }
        }
    }
    if (canSpecialMove) {
        if (from.first == 'e' && from.second == 1) {
            moves.emplace_back('g', 1);
            moves.emplace_back('c', 1);
        } else if (from.first == 'e' && from.second == 8) {
            moves.emplace_back('g', 8);
            moves.emplace_back('c', 8);
        }
    }
    return moves;
}

bool King::canMoveTo(std::pair<char, int> from, std::pair<char, int> to) {
    if (to.first < 'a' || to.first > 'h' || to.second < 1 || to.second > 8) {
        return false;
    }
    auto nextPiece = board->getSquare(to.first, to.second)->getPiece();
    if (nextPiece && nextPiece->isWhite() == isWhite()) {
        return false;
    }
    if (board->isPieceBetween(from, to)) {
        return false;
    }
    if (canSpecialMove) {
        if (from.first == 'e' && from.second == 1 && to.first == 'g' && to.second == 1) {
            return true;
        } else if (from.first == 'e' && from.second == 1 && to.first == 'c' && to.second == 1) {
            return true;
        } else if (from.first == 'e' && from.second == 8 && to.first == 'g' && to.second == 8) {
            return true;
        } else if (from.first == 'e' && from.second == 8 && to.first == 'c' && to.second == 8) {
            return true;
        }
    }
    return (abs(from.first - to.first) <= 1 && abs(from.second - to.second) <= 1);
}

bool King::move(std::pair<char, int> from, std::pair<char, int> to, std::istream &in) {
    if (canMoveTo(from, to)) {
        std::shared_ptr<Move> mv = std::make_shared<Move>();
        if (canSpecialMove) {
            if (from.first == 'e' && from.second == 1 && to.first == 'g' && to.second == 1) {
                if (!board->getSquare('h', 1)->getPiece()->getCanSpecialMove()) {
                    return false;
                }
                board->movePiece({'h', 1}, {'f', 1}, mv);
            } else if (from.first == 'e' && from.second == 1 && to.first == 'c' && to.second == 1) {
                if (!board->getSquare('a', 1)->getPiece()->getCanSpecialMove()) {
                    return false;
                }
                board->movePiece({'a', 1}, {'d', 1}, mv);
            } else if (from.first == 'e' && from.second == 8 && to.first == 'g' && to.second == 8) {
                if (!board->getSquare('h', 8)->getPiece()->getCanSpecialMove()) {
                    return false;
                }
                board->movePiece({'h', 8}, {'f', 8}, mv);
            } else if (from.first == 'e' && from.second == 8 && to.first == 'c' && to.second == 8) {
                if (!board->getSquare('a', 8)->getPiece()->getCanSpecialMove()) {
                    return false;
                }
                board->movePiece({'a', 8}, {'d', 8}, mv);
            }
        }
        board->movePiece(from, to, mv);
        board->addLastMove(mv);
        canSpecialMove = false;
        return true;
    }
    return false;
}