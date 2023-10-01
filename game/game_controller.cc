#include "game_controller.h"

#include <memory>
#include <iostream>

#include "game.h"
#include "../output_stream/textual_output_stream.h"
#include "../output_stream/graphical_output_stream.h"
#include "../player/base_player.h"
#include "../player/level_one_player.h"
#include "../player/level_two_player.h"
#include "../player/level_three_player.h"
#include "../player/level_four_player.h"
#include "../player/player.h"
#include "../command/invoker.h"
#include "../command/game_command.h"
#include "../command/resign_command.h"
#include "../command/move_command.h"
#include "../command/setup_command.h"
#include "../command/command_history.h"

using namespace std;

GameController::GameController(
    shared_ptr<Game> model, 
    shared_ptr<GameView> view, 
    istream& in): model{model}, view{view}, in{in} {}

void GameController::run() {
    viewSetup();
    commandsReader();
}

void GameController::commandsReader() {
    string command, cmdMsg;
    auto history = make_shared<CommandHistory<Command>>();
    auto invoker = make_shared<Invoker>();
    bool gameStarted = false, undoEnabled = false, isSetup = false;
    while (in >> command) {
        shared_ptr<Command> cmd;
        if (command == "game") {
            if (gameStarted) {
                view->showMessage("Game has already started");
                continue;
            }
            cmd = make_shared<GameCommand>(model, in);
        } else if (command == "move") {
            if (!gameStarted) {
                view->showMessage("Game has not started yet");
                continue;
            }
            cmd = make_shared<MoveCommand>(model, in);
        } else if (command == "resign") {
            if (!gameStarted) {
                view->showMessage("Game has not started yet");
                continue;
            }
            cmd = make_shared<ResignCommand>(model, in);
            isSetup = false;
        } else if (command == "setup") {
            if (gameStarted) {
                view->showMessage("Cannot setup game after it has started");
                continue;
            }
            model->reset();
            view->showBoard();
            cmd = make_shared<SetupCommand>(model, in, view);
            isSetup = true;
        } else if (command == "undo") {
            if (!undoEnabled) {
                view->showMessage("Invalid command");
                continue;
            }
            if (history->empty()) {
                view->showMessage("No previous command to undo");
                continue;
            }
            history->top()->undo();
            history->pop();
            view->showBoard();
            continue;
        } else if (command == "+") {
            in >> command;
            if (command == "undo") {
                undoEnabled = true;
                view->showMessage("Undo enabled");
                continue;
            } else {
                view->showMessage("Invalid command");
                continue;
            }
        } else if (command == "-") {
            in >> command;
            if (command == "undo") {
                undoEnabled = false;
                view->showMessage("Undo disabled");
                continue;
            } else {
                view->showMessage("Invalid command");
                continue;
            }
        } else {
            view->showMessage("Invalid command");
            continue;
        }
        invoker->setCommand(cmd);
        history->push(cmd);
        if (cmdMsg = invoker->execute(); !cmdMsg.empty()) {
            if (cmdMsg.length() >= 9 && cmdMsg.substr(0, 9) == "Checkmate") {
                gameStarted = false;
                isSetup = false;
                history->clear();
                view->showBoard();
            } else if (cmdMsg.length() >= 18 && cmdMsg.substr(5, 18) == " is in check.") {
                view->showBoard();
            } else if (cmdMsg.length() >= 9 && cmdMsg == "Stalemate") {
                gameStarted = false;
                isSetup = false;
                history->clear();
                view->showBoard();
            } else if (cmdMsg.length() >= 11 && cmdMsg.substr(5, 11) == " wins!") {
                gameStarted = false;
                isSetup = false;
                history->clear();
            }
            view->showMessage(cmdMsg);
        } else {
            if (command == "game") {
                if (!isSetup) {  
                    model->reset();
                }
                gameStarted = true;
            }
            view->showBoard();
        }
    }
    auto score = model->getScore();
    view->showMessage(
        "Final Score:\nWhite: " + 
        std::to_string(score.first) + "\nBlack: " + 
        std::to_string(score.second) + "\n"
    );
}

void GameController::viewSetup() {
    view->attach(make_shared<TextualOutputStream>(view));
    view->attach(make_shared<GraphicalOutputStream>(view));
}

GameController::~GameController() {}
