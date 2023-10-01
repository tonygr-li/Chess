#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h" 

class Queen : public Piece {
public:
    Queen(char letter, std::shared_ptr<Board> board);
    std::vector<std::pair<char, int>> getMoves(std::pair<char, int>) override;
    bool canMoveTo(std::pair<char, int>, std::pair<char, int>) override;
    bool move(std::pair<char, int>, std::pair<char, int>, std::istream&) override;
};

#endif // QUEEN_H
