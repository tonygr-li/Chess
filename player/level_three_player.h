#ifndef LEVEL_THREE_PLAYER_H
#define LEVEL_THREE_PLAYER_H

#include <memory>

#include "../player/player_decorator.h"

class LevelThreePlayer: public PlayerDecorator {
public:
    LevelThreePlayer(std::shared_ptr<Player>);
    bool move(std::istream&) override;
};

#endif // LEVEL_THREE_PLAYER_H
