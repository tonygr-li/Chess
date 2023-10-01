#include "level_one_player.h"

#include <memory>
#include <sstream>

#include "../board/board.h"
#include "../game/game.h"
#include "../piece/piece.h"
#include "../square/square.h"

LevelOnePlayer::LevelOnePlayer(std::shared_ptr<Player> player): PlayerDecorator{player} {}

bool LevelOnePlayer::move(std::istream& in) {
    auto board = wraps->getGame()->getBoard();
    std::stringstream ss{"Q"};
    for (auto square: *board) {
        auto piece = square->getPiece();
        if (!piece || piece->isWhite() != wraps->isWhite()) {
            continue;
        }
        auto possibleMoves = piece->getMoves(square->getRankFile());
        if (possibleMoves.empty()) {
            continue;
        }
        for (auto move: possibleMoves) {
            piece->move(square->getRankFile(), move, ss);
            if (isInCheck()) {
                board->undoLastMove();
                board->popLastMove();
                continue;
            }
            return true;
        }
    }
    return false;
}
