#include "game_view.h"
#include "game.h"

GameView::GameView(std::shared_ptr<Game> game): game{game} {}

GameView::~GameView() {}

void GameView::showMessage(std::string message) {
    notify(message);
}

void GameView::showBoard() {
    notify(game->getBoard());
}
