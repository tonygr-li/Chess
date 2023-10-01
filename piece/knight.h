#ifndef KNIHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {
    
public:
    Knight(char letter, std::shared_ptr<Board> board);
    std::vector<std::pair<char, int>> getMoves(std::pair<char, int>) override;
    bool canMoveTo(std::pair<char, int>, std::pair<char, int>) override;
    bool move(std::pair<char, int>, std::pair<char, int>, std::istream&) override;
};

#endif // KNIGHT_H
