#ifndef GAME_H
#define GAME_H

#include <memory>
#include <iostream>

#include "../board/board.h"
#include "../board/board_iterator.h"
#include "../player/player.h"
#include "game_controller.h"
#include "game_view.h"

class Game {
    std::shared_ptr<Board> board;
    std::pair<int, int> score;
    std::pair<std::shared_ptr<Player>, std::shared_ptr<Player>> players;
    std::shared_ptr<Player> curPlayer;
    bool isWhite;
public:
    Game(); // set gameStatus to notstarter, checkstatus to notcheck
    ~Game();
    void reset(); // reset board, pieces, turn
    void resign();
    void setTurnToWhite(bool);
    std::shared_ptr<Board> getBoard();
    std::shared_ptr<Player> getCurPlayer();
    bool move(std::istream&); // check for valid as well
    void undoMove();
    std::pair<int, int> getScore();
    void setScore(std::pair<int, int>);
    void setPlayers(std::shared_ptr<Player>, std::shared_ptr<Player>);
    void getIsWhite(bool);
};

#endif
