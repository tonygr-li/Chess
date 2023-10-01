#ifndef LEVEL_ONE_PLAYER_H
#define LEVEL_ONE_PLAYER_H

#include <memory>

#include "../player/player_decorator.h"

class LevelOnePlayer: public PlayerDecorator {
public:
    LevelOnePlayer(std::shared_ptr<Player>);
    bool move(std::istream&) override;
};

#endif // LEVEL_ONE_PLAYER_H
