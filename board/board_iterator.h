#ifndef BOARD_ITERATOR_H
#define BOARD_ITERATOR_H

#include <memory>

#include "../square/square.h"

class Board;

class BoardIterator {
    std::shared_ptr<Board> board;
    char rank;
    int file;
    BoardIterator(std::shared_ptr<Board>, char, int);
public:
    BoardIterator& operator++();
    bool operator!=(const BoardIterator&) const;
    std::shared_ptr<Square> operator*() const;
    friend Board;
};

#endif // BOARD_ITERATOR_H
