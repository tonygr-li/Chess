#ifndef PLAYER_DECORATOR_H
#define PLAYER_DECORATOR_H

#include <memory>

#include "../player/player.h"

class Board;

class PlayerDecorator: public Player {
protected:
    std::shared_ptr<Player> wraps;
public:
    PlayerDecorator(std::shared_ptr<Player>);
    virtual bool move(std::istream&) = 0;
    bool isWhite() const override;
    bool isInCheck() const override;
    bool canMove() const override;
    std::shared_ptr<Game> getGame() const override;
};

#endif // PLAYER_DECORATOR_H
