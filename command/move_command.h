#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include <iostream>
#include <memory>
#include <sstream>

#include "../game/game.h"
#include "command.h"

class MoveCommand: public Command {
public:
    MoveCommand(std::shared_ptr<Game>, std::istream&);
    std::string execute();
    void undo();
};

#endif // MOVE_COMMAND_H
