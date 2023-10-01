#include "resign_command.h"

#include <iostream>
#include <memory>
#include <sstream>

#include "../game/game.h"

ResignCommand::ResignCommand(std::shared_ptr<Game> game, std::istream& in): Command{game, in} {}

std::string ResignCommand::execute() {
    game->resign();
    if (game->getCurPlayer()->isWhite()) {
        return "Black wins!";
    } else {
        return "White wins!";
    }
}
