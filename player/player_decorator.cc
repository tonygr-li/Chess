#include "player_decorator.h"

PlayerDecorator::PlayerDecorator(std::shared_ptr<Player> wraps): wraps{wraps} {}

bool PlayerDecorator::isWhite() const {
    return wraps->isWhite();
}

bool PlayerDecorator::isInCheck() const {
    return wraps->isInCheck();
}

bool PlayerDecorator::canMove() const {
    return wraps->canMove();
}

std::shared_ptr<Game> PlayerDecorator::getGame() const {
    return wraps->getGame();
}
