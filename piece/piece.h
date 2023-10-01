#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <memory>
#include <vector>

class Board;

class Piece {
protected:
    char letter; // lowercase is black, uppercase is white
    std::shared_ptr<Board> board;
    bool canSpecialMove;
    int pointValue;
public:
    Piece(char, std::shared_ptr<Board>, bool, int);
    ~Piece();
    char getLetter();
    bool isWhite();
    bool getCanSpecialMove();
    void setCanSpecialMove(bool);
    virtual std::vector<std::pair<char, int>> getMoves(std::pair<char, int>) = 0;
    virtual bool move(std::pair<char, int>, std::pair<char, int>, std::istream&) = 0;
    virtual bool canMoveTo(std::pair<char, int>, std::pair<char, int>) = 0;
    int getPointValue();
};

#endif
