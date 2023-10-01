#ifndef SQUARE_H
#define SQUARE_H

#include <memory>

#include "../piece/piece.h"

class Square {
    std::shared_ptr<Piece> piece;
    const std::pair<char, int> rankFile;
public:
    Square(char, int);
    ~Square();
    std::shared_ptr<Piece> getPiece();
    void setPiece(std::shared_ptr<Piece>);
    void removePiece();
    bool canMoveTo(std::pair<char, int>);
    std::pair<char, int> getRankFile();
};

#endif // SQUARE_H
