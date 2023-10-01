#ifndef PAWN_H
#define PAWN_H

#include "piece.h" 

class Pawn : public Piece {
    bool canEnPassant(std::pair<char, int>, std::pair<char, int>);
public:
    Pawn(char letter, std::shared_ptr<Board> board);
    std::vector<std::pair<char, int>> getMoves(std::pair<char, int>) override;
    bool canMoveTo(std::pair<char, int>, std::pair<char, int>) override;
    bool move(std::pair<char, int>, std::pair<char, int>, std::istream&) override;
};

#endif // PAWN_H
