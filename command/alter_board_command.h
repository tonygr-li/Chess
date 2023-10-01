#ifndef ALTER_BOARD_COMMAND_H
#define ALTER_BOARD_COMMAND_H

#include <iostream>
#include <memory>
#include <sstream>

#include "../game/game.h"
#include "command.h"

class AlterBoardCommand: public Command {
    std::stringstream revert;
public:
    AlterBoardCommand(std::shared_ptr<Game>, std::istream&);
    std::string execute();
    void undo();
};

#endif // ALTER_BOARD_COMMAND_H
