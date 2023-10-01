#include "level_two_player.h"

#include <iostream>
#include <memory>
#include <sstream>

#include "../board/board.h"
#include "../game/game.h"
#include "../piece/piece.h"
#include "../square/square.h"

LevelTwoPlayer::LevelTwoPlayer(std::shared_ptr<Player> player): PlayerDecorator{player} {}

bool LevelTwoPlayer::move(std::istream& in) {
    auto board = wraps->getGame()->getBoard();
    std::stringstream ss{"Q"};
    for (auto square: *board) {
        auto piece = square->getPiece();
        if (!piece || piece->isWhite() != wraps->isWhite()) {
            continue;
        }
        auto possibleMoves = piece->getMoves(square->getRankFile());
        for (auto move: possibleMoves) {
            if (board->getSquare(move.first, move.second)->getPiece()) {
                if (!piece->move(square->getRankFile(), move, ss)) {
                    continue;
                }
            } else {
                if (!piece->move(square->getRankFile(), move, ss)) {
                    continue;
                }
                if (!board->isInCheck(!wraps->isWhite())) {
                    board->undoLastMove();
                    board->popLastMove();
                    continue;
                }
            }
            if (isInCheck()) {
                board->undoLastMove();
                board->popLastMove();
                continue;
            }
            return true;
        }
    }
    return wraps->move(in);
}