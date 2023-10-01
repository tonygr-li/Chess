#include "game/game_controller.h"

#include <iostream>
#include <memory>

using namespace std;

int main() {
    shared_ptr<Game> game = make_shared<Game>();
    make_unique<GameController>(game, make_shared<GameView>(game), cin)->run();
}
