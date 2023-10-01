#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H

#include <iostream>
#include <memory>

#include "../game/game.h"
#include "command.h"

class GameCommand: public Command {
public:
    GameCommand(std::shared_ptr<Game>, std::istream&);
    std::string execute();
};

#endif // GAME_COMMAND_H
