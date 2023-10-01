#ifndef BISHOP_H
#define BISHOP_H

#include <memory>
#include "../board/board.h"
#include "piece.h"

class Bishop : public Piece {
public:
    Bishop(char letter, std::shared_ptr<Board> board);
    std::vector<std::pair<char, int>> getMoves(std::pair<char, int>) override;
    bool canMoveTo(std::pair<char, int>, std::pair<char, int>) override;
    bool move(std::pair<char, int>, std::pair<char, int>, std::istream&) override;
};

#endif // BISHOP_H
