#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <memory>
#include <stack>

#include "../game/game.h"

class Command {
protected:
    std::shared_ptr<Game> game;
    std::istream& in;
public:
    Command(std::shared_ptr<Game>, std::istream&);
    virtual ~Command();
    virtual std::string execute() = 0;
    virtual void undo();
};

#endif // COMMAND_H
