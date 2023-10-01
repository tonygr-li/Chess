#ifndef INVOKER_H
#define INVOKER_H

#include <memory>

#include "../command/command.h"

class Invoker {
    std::shared_ptr<Command> command;
public:
    Invoker();
    ~Invoker();
    void setCommand(std::shared_ptr<Command>);
    std::string execute();
};

#endif // INVOKER_H
