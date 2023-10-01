#include "board_iterator.h"
#include "board.h"

BoardIterator::BoardIterator(std::shared_ptr<Board> board, char rank, int file) : board{board}, rank{rank}, file{file} {}

BoardIterator& BoardIterator::operator++() {
    if (file == 8) {
        file = 1;
        rank++;
    } else {
        file++;
    }
    return *this;
}

bool BoardIterator::operator!=(const BoardIterator& other) const {
    return rank != other.rank || file != other.file;
}

std::shared_ptr<Square> BoardIterator::operator*() const {
    return board->getSquare(rank, file);
}
