#ifndef RESIGN_COMMAND_H
#define RESIGN_COMMAND_H

#include <iostream>
#include <memory>
#include <sstream>

#include "../game/game.h"
#include "command.h"

class ResignCommand: public Command {
public:
    ResignCommand(std::shared_ptr<Game>, std::istream&);
    std::string execute();
};

#endif // RESIGN_COMMAND_H
