#ifndef KING_H
#define KING_H

#include <memory>

#include "piece.h"

class King : public Piece {
    bool canCastle(std::pair<char, int>, std::pair<char, int>);
public:
    King(char letter, std::shared_ptr<Board> board);
    std::vector<std::pair<char, int>> getMoves(std::pair<char, int>) override;
    bool canMoveTo(std::pair<char, int>, std::pair<char, int>) override;
    bool move(std::pair<char, int>, std::pair<char, int>, std::istream&) override;
};

#endif // KING_H
