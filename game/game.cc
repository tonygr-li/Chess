#include "game.h"

#include <memory>
#include <iostream>

#include "../board/board.h"
#include "../player/player.h"
#include "../move/move.h"

Game::Game(): 
    board{std::make_shared<Board>()}, 
    score{std::make_pair(0, 0)},
    isWhite{true} {}

void Game::reset() {
    std::shared_ptr<Move> resetMove = std::make_shared<Move>();
    resetMove->isUndo = true;
    board->emptyBoard(resetMove);
    // add pawns
    for (int i = 0; i < 8; i++) {
        board->addPiece('P', 'a' + i, 2, resetMove);
        board->addPiece('p', 'a' + i, 7, resetMove);
    }
    // add rooks
    board->addPiece('R', 'a', 1, resetMove);
    board->addPiece('R', 'h', 1, resetMove);
    board->addPiece('r', 'a', 8, resetMove);
    board->addPiece('r', 'h', 8, resetMove);
    // add knights
    board->addPiece('N', 'b', 1, resetMove);
    board->addPiece('N', 'g', 1, resetMove);
    board->addPiece('n', 'b', 8, resetMove);
    board->addPiece('n', 'g', 8, resetMove);
    // add bishops
    board->addPiece('B', 'c', 1, resetMove);
    board->addPiece('B', 'f', 1, resetMove);
    board->addPiece('b', 'c', 8, resetMove);
    board->addPiece('b', 'f', 8, resetMove);
    // add queens
    board->addPiece('Q', 'd', 1, resetMove);
    board->addPiece('q', 'd', 8, resetMove);
    // add kings
    board->addPiece('K', 'e', 1, resetMove);
    board->addPiece('k', 'e', 8, resetMove);
    // set current player turn
    while(board->popLastMove());
    board->addLastMove(resetMove);
    setTurnToWhite(true);
}

void Game::setTurnToWhite(bool whiteTurn) {
    isWhite = whiteTurn;
    // if (whiteTurn) {
    //     curPlayer = players.first;
    // }
    // else {
    //     curPlayer = players.second;
    // }
}

void Game::resign() {
    if (curPlayer == players.first) {
        score.second += 1;
    } 
    else {
        score.first += 1;
    }
}

std::shared_ptr<Board> Game::getBoard() {
    return board;
}

bool Game::move(std::istream& in) {
    bool moveValid = curPlayer->move(in);
    if (moveValid) {
        if (curPlayer == players.first) {
            curPlayer = players.second;
        }
        else {
            curPlayer = players.first;
        }
    }
    return moveValid;
}

void Game::undoMove() {
    board->undoLastMove();
    if (curPlayer == players.first) {
        curPlayer = players.second;
    }
    else {
        curPlayer = players.first;
    }
}

std::pair<int, int> Game::getScore() {
    return score;
}

void Game::setScore(std::pair<int, int> newScore) {
    score = newScore;
}

Game::~Game() {}

void Game::setPlayers(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2) {
    players = isWhite ? std::make_pair(p1, p2) : std::make_pair(p2, p1);
    curPlayer = players.first;
}

std::shared_ptr<Player> Game::getCurPlayer() {
    return curPlayer;
}
