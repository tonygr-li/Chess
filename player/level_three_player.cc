#include "level_three_player.h"

#include <iostream>
#include <memory>
#include <sstream>

#include "../board/board.h"
#include "../game/game.h"
#include "../piece/piece.h"
#include "../square/square.h"

LevelThreePlayer::LevelThreePlayer(std::shared_ptr<Player> player): PlayerDecorator{player} {}

bool LevelThreePlayer::move(std::istream& in) {
    auto board = wraps->getGame()->getBoard();
    std::stringstream ss{"Q"};
    for (auto square: *board) {
        auto opponentPiece = square->getPiece();
        if (!opponentPiece || opponentPiece->isWhite() == wraps->isWhite()) {
            continue;
        }
        auto possibleOpponentMoves = opponentPiece->getMoves(square->getRankFile());
        for (auto opmove: possibleOpponentMoves) {
            auto attackedPiece = board->getSquare(opmove.first, opmove.second)->getPiece();
            if (!attackedPiece || attackedPiece->isWhite() != wraps->isWhite()) {
                continue;
            }
            auto possibleMoves = attackedPiece->getMoves(opmove);
            for (auto move: possibleMoves) {
                if (!attackedPiece->move(opmove, move, ss)) {
                    continue;
                }
                if (isInCheck()) {
                    board->undoLastMove();
                    board->popLastMove();
                    continue;
                }
                return true;
            }
        }
    }
    return wraps->move(in);
}