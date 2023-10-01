#include "game_command.h"

#include <memory>

#include "../game/game.h"
#include "../player/player.h"
#include "../player/base_player.h"
#include "../player/level_one_player.h"
#include "../player/level_two_player.h"
#include "../player/level_three_player.h"
#include "../player/level_four_player.h"

GameCommand::GameCommand(std::shared_ptr<Game> game, std::istream& in): Command{game, in} {}

std::string GameCommand::execute() {
    std::pair<std::shared_ptr<Player>, std::shared_ptr<Player>> players;
    for (int i = 0; i < 2; ++i) {
        std::string player;
        in >> player;
        if (player != "human") {
            if (
                player.substr(0, 8) != "computer" || 
                player[player.size() - 1] < '1' || 
                player[player.size() - 1] > '4' ||
                player.size() > 9
            ) {
                return "Invalid Player";
            }
        }
        std::shared_ptr<Player> p = std::make_shared<BasePlayer>(i == 0, game);
        if (player != "human") {
            if (player[player.size() - 1] >= '1') {
                p = std::make_shared<LevelOnePlayer>(p);
            }
            if (player[player.size() - 1] >= '2') {
                p = std::make_shared<LevelTwoPlayer>(p);
            }
            if (player[player.size() - 1] >= '3') {
                p = std::make_shared<LevelThreePlayer>(p);
            }
            if (player[player.size() - 1] == '4') {
                p = std::make_shared<LevelFourPlayer>(p);
            }
        }
        if (i == 0) {
            players.first = p;
        }
        else {
            players.second = p;
        }
    }
    game->setPlayers(players.first, players.second);
    return std::string();
}
