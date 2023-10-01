#include "square.h"

Square::Square(char rank, int file): rankFile{std::make_pair(rank, file)} {}

std::pair<char, int> Square::getRankFile() {
    return rankFile;
}

std::shared_ptr<Piece> Square::getPiece() {
    return piece;
}

void Square::setPiece(std::shared_ptr<Piece> piece) {
    this->piece = piece;
}

void Square::removePiece() {
    piece = nullptr;
}

bool Square::canMoveTo(std::pair<char, int> toMove) {
    if (piece) {
        return piece->canMoveTo(rankFile, toMove);
    }
    return false;
}

Square::~Square() {}
