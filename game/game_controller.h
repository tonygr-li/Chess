#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "game.h"
#include "game_view.h"
#include <memory>
#include <iostream>

class GameController {
    std::shared_ptr<Game> model;
    std::shared_ptr<GameView> view;
    std::istream& in;
    void commandsReader();
    void viewSetup();
    void setup();
public:
    GameController(std::shared_ptr<Game>, std::shared_ptr<GameView>, std::istream&);
    ~GameController();
    void run();
};

#endif
