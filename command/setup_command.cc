#include "setup_command.h"

#include <iostream>
#include <memory>

#include "../game/game.h"
#include "alter_board_command.h"

SetupCommand::SetupCommand(std::shared_ptr<Game> game, std::istream& in, std::shared_ptr<GameView> view): Command{game, in}, history{std::make_shared<CommandHistory<AlterBoardCommand>>()}, view{view} {}

std::string SetupCommand::execute() {
    while (true) {
        auto cmd = std::make_shared<AlterBoardCommand>(game, in);
        std::string msg = cmd->execute();
        if (msg.empty()) {
            history->push(cmd);
            view->showBoard();
        } else if (msg == "done") {
            return std::string();
        }else if (msg == "undo") {
            if (history->empty()) {
                view->showMessage("No previous command to undo");
                continue;
            }
            history->top()->undo();
            history->pop();
            view->showBoard();
        } else {
            view->showMessage(msg);
        }
    }
    return std::string();
}

void SetupCommand::undo() {
    while (!history->empty()) {
        history->top()->undo();
        history->pop();
        view->showBoard();
    }
}
