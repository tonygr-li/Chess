#include "move_command.h"

#include <iostream>
#include <memory>

#include "../game/game.h"

MoveCommand::MoveCommand(std::shared_ptr<Game> game, std::istream& in): Command{game, in} {}

std::string MoveCommand::execute() {
    if (!game->move(in)) {
        return "Invalid move";
    }
    if (game->getCurPlayer()->isInCheck()) {
        if (game->getCurPlayer()->canMove()) {
            if (game->getCurPlayer()->isWhite()) {
                return "White is in check.";
            } else {
                return "Black is in check.";
            }
        } else {
            auto score = game->getScore();
            if (game->getCurPlayer()->isWhite()) {
                game->setScore({score.first, score.second + 1});
                return "Checkmate! Black wins!";
            }
            game->setScore({score.first + 1, score.second});
            return "Checkmate! White wins!";
        }
    }
    if (!game->getCurPlayer()->canMove()) {
        return "Stalemate";
    }
    return std::string();
}

void MoveCommand::undo() {
    game->undoMove();
}
