#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "../board/board.h"
#include "../observer/subject.h"

#include <memory>
#include <string>

class Game;

class GameView: public Subject {
    std::shared_ptr<Game> game;
public:
    GameView(std::shared_ptr<Game>);
    ~GameView();
    void showMessage(std::string);
    void showBoard();
};

#endif
