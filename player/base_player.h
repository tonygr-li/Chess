#ifndef BASE_PLAYER_H
#define BASE_PLAYER_H

#include <memory>

#include "../player/player.h"

class Game;

class BasePlayer: public Player {
    bool is_white;
    std::shared_ptr<Game> game;
public:
    BasePlayer(bool, std::shared_ptr<Game>);
    bool move(std::istream&) override;
    bool isWhite() const override;
    bool isInCheck() const override;
    bool canMove() const override;
    std::shared_ptr<Game> getGame() const override;
};

#endif // BASE_PLAYER_H
