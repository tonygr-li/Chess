#include "invoker.h"

Invoker::Invoker() {}

Invoker::~Invoker() {}

void Invoker::setCommand(std::shared_ptr<Command> command) {
    this->command = command;
}

std::string Invoker::execute() {
    return command->execute();
}
