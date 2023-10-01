#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <memory>

class Game;

class Player {
public:
    virtual bool move(std::istream&) = 0;
    virtual bool isWhite() const = 0;
    virtual bool isInCheck() const = 0;
    virtual bool canMove() const = 0;
    virtual std::shared_ptr<Game> getGame() const = 0;
    virtual ~Player() = default;
};

#endif // PLAYER_H
