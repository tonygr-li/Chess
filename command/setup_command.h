#ifndef SETUP_COMMAND_H
#define SETUP_COMMAND_H

#include <iostream>
#include <memory>

#include "../game/game.h"
#include "command.h"
#include "command_history.h"
#include "alter_board_command.h"
#include "../game/game_view.h"

class SetupCommand: public Command {
    std::shared_ptr<CommandHistory<AlterBoardCommand>> history;
    std::shared_ptr<GameView> view;
public:
    SetupCommand(std::shared_ptr<Game>, std::istream&, std::shared_ptr<GameView>);
    std::string execute();
    void undo();
};

#endif // SETUP_COMMAND_H
