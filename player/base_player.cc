#include "base_player.h"

#include <iostream>
#include <memory>
#include <sstream>

#include "../board/board.h"
#include "../game/game.h"

BasePlayer::BasePlayer(bool is_white, std::shared_ptr<Game> game): is_white{is_white}, game{game} {}

bool BasePlayer::move(std::istream& in) {
    std::string from, to;
    in >> from >> to;
    if ('a' > from[0] || from[0] > 'h' || '1' > from[1] || from[1] > '8' ||
        'a' > to[0] || to[0] > 'h' || '1' > to[1] || to[1] > '8') {
        return false;
    }
    auto startPos = std::make_pair(from[0], from[1] - '0');
    auto endPos = std::make_pair(to[0], to[1] - '0');
    auto piece = game->getBoard()->getSquare(startPos.first, startPos.second)->getPiece();
    if (!piece || piece->isWhite() != isWhite() || !piece->move(startPos, endPos, in)) {
        return false;
    }
    if (isInCheck()) {
        game->getBoard()->undoLastMove();
        return false;
    }
    return true;
}

bool BasePlayer::isWhite() const {
    return is_white;
}

bool BasePlayer::isInCheck() const {
    return game->getBoard()->isInCheck(is_white);
}

bool BasePlayer::canMove() const {
    auto board = game->getBoard();
    std::stringstream ss{"Q"};
    for (auto square: *board) {
        auto piece = square->getPiece();
        if (!piece || piece->isWhite() != is_white) {
            continue;
        }
        auto moves = piece->getMoves(square->getRankFile());
        for (auto move: moves) {
            if (piece->move(square->getRankFile(), move, ss)) {
                if (isInCheck()) {
                    board->undoLastMove();
                    board->popLastMove();
                    continue;
                }
                board->undoLastMove();
                board->popLastMove();
                return true;
            }
        }
    }
    return false;
}

std::shared_ptr<Game> BasePlayer::getGame() const {
    return game;
}
