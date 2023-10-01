#ifndef LEVEL_TWO_PLAYER_H
#define LEVEL_TWO_PLAYER_H

#include <memory>

#include "../player/player_decorator.h"

class LevelTwoPlayer: public PlayerDecorator {
public:
    LevelTwoPlayer(std::shared_ptr<Player>);
    bool move(std::istream&) override;
};

#endif // LEVEL_TWO_PLAYER_H
