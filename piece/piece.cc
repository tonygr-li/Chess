#include "piece.h"

#include <memory>

#include "../board/board.h"

Piece::Piece(char letter, std::shared_ptr<Board> board, bool canSpecialMove, int pointValue): letter{letter}, board{board}, canSpecialMove{canSpecialMove}, pointValue{pointValue} {}

Piece::~Piece() {}

char Piece::getLetter() {
    return letter;
}

bool Piece::isWhite() {
    return isupper(letter);
}

bool Piece::getCanSpecialMove() {
    return canSpecialMove;
}

void Piece::setCanSpecialMove(bool canSpecialMove) {
    this->canSpecialMove = canSpecialMove;
}

int Piece::getPointValue() {
    return pointValue;
}
