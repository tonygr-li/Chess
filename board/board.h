#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>
#include <iostream>
#include <map>
#include <stack>

#include "../square/square.h"
#include "../player/player.h"

class Move;

class BoardIterator;

class Board: public std::enable_shared_from_this<Board> {
    std::vector<std::vector<std::shared_ptr<Square>>> squares;
    std::map<char, std::vector<std::pair<char, int>>> whitePieces;
    std::map<char, std::vector<std::pair<char, int>>> blackPieces;
    std::stack<std::shared_ptr<Move>> moves;
public:
    Board();
    ~Board();
    bool isValid();
    bool isInCheck(bool);
    void emptyBoard(std::shared_ptr<Move>);
    bool isPieceBetween(std::pair<char, int>, std::pair<char, int>);
    bool addPiece(char, char, int, std::shared_ptr<Move> = nullptr);
    bool removePiece(char, int, std::shared_ptr<Move> = nullptr);
    void movePiece(std::pair<char, int>, std::pair<char, int>, std::shared_ptr<Move> = nullptr);
    std::shared_ptr<Square> getSquare(char, int);
    void undoLastMove();
    std::shared_ptr<Move> getLastMove();
    std::shared_ptr<Move> popLastMove();
    void addLastMove(std::shared_ptr<Move>);
    BoardIterator begin();
    BoardIterator end();
    friend std::ostream& operator<<(std::ostream&, const Board&);
};

#endif // BOARD_H
