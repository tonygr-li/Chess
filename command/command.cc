#include "command.h"

Command::Command(std::shared_ptr<Game> game, std::istream& in): game{game}, in{in} {}

void Command::undo() {}

Command::~Command() {}
