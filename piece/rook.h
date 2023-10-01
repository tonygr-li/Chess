#ifndef ROOK_H
#define ROOK_H

#include "piece.h" 

class Rook : public Piece {
    bool canSpecialMove;
public:
    Rook(char letter, std::shared_ptr<Board> board);
    std::vector<std::pair<char, int>> getMoves(std::pair<char, int>) override;
    bool canMoveTo(std::pair<char, int>, std::pair<char, int>) override;
    bool move(std::pair<char, int>, std::pair<char, int>, std::istream&) override;
};

#endif // ROOK_H
