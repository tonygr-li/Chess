#ifndef LEVEL_FOUR_PLAYER_H
#define LEVEL_FOUR_PLAYER_H

#include "player.h"
#include "../player/player_decorator.h"

#include <memory>

class LevelFourPlayer: public PlayerDecorator {
    std::shared_ptr<Player> player;
    int maxNetPoint(bool, int);
public:
    LevelFourPlayer(std::shared_ptr<Player>);
    bool move(std::istream&) override;
};

#endif // LEVEL_FOUR_PLAYER_H
