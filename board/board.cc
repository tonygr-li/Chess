#include "board.h"
#include "board_iterator.h"

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

#include "../piece/piece.h"
#include "../piece/pawn.h"
#include "../piece/rook.h"
#include "../piece/knight.h"
#include "../piece/bishop.h"
#include "../piece/queen.h"
#include "../piece/king.h"
#include "../move/move.h"

Board::Board(): squares{8, std::vector<std::shared_ptr<Square>>(8)} {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; j++) {
            squares[i][j] = std::make_shared<Square>('a' + i, j + 1);
        }
    }
}

bool Board::removePiece(char rank, int file, std::shared_ptr<Move> mv) {
    if (rank < 'a' || rank > 'h' || file < 1 || file > 8) {
        return false;
    }
    std::shared_ptr<Piece> piece = squares[rank - 'a'][file - 1]->getPiece();
    if (piece) {
        squares[rank - 'a'][file - 1]->removePiece();
        if (piece->isWhite()) {
            whitePieces[piece->getLetter()].erase(std::remove(whitePieces[piece->getLetter()].begin(), whitePieces[piece->getLetter()].end(), std::make_pair(rank, file)), whitePieces[piece->getLetter()].end());
        } else {
            blackPieces[piece->getLetter()].erase(std::remove(blackPieces[piece->getLetter()].begin(), blackPieces[piece->getLetter()].end(), std::make_pair(rank, file)), blackPieces[piece->getLetter()].end());
        }
        if (mv) {
            mv->pieceRemoved.push_back({piece->getLetter(), {rank, file}});
        }
    } else {
        return false;
    }
    return true;
}

bool Board::addPiece(char letter, char rank, int file, std::shared_ptr<Move> mv) {
    if (rank < 'a' || rank > 'h' || file < 1 || file > 8) {
        return false;
    }
    std::shared_ptr<Piece> piece;
    switch (letter) {
        case 'p':
        case 'P':
            piece = std::make_shared<Pawn>(letter, shared_from_this());
            break;
        case 'r':
        case 'R':
            piece = std::make_shared<Rook>(letter, shared_from_this());
            break;
        case 'n':
        case 'N':
            piece = std::make_shared<Knight>(letter, shared_from_this());
            break;
        case 'b':
        case 'B':
            piece = std::make_shared<Bishop>(letter, shared_from_this());
            break;
        case 'q':
        case 'Q':
            piece = std::make_shared<Queen>(letter, shared_from_this());
            break;
        case 'k':
        case 'K':
            piece = std::make_shared<King>(letter, shared_from_this());
            break;
        default:
            return false;
    }
    removePiece(rank, file, mv);
    squares[rank - 'a'][file - 1]->setPiece(piece);
    if (piece->isWhite()) {
        whitePieces[letter].push_back(std::make_pair(rank, file));
    } else {
        blackPieces[letter].push_back(std::make_pair(rank, file));
    }
    if (mv) {
        mv->pieceAdded.push_back({letter, {rank, file}});
    }
    return true;
}

bool Board::isValid() {
    // int whiteKing = 0;
    // int blackKing = 0;
    // for (auto square: *this) {
    //     if (square->getPiece()) {
    //         if (square->getPiece()->getLetter() == 'k') {
    //             blackKing++;
    //         } else if (square->getPiece()->getLetter() == 'K') {
    //             whiteKing++;
    //         }
    //     }
    // }
    if (whitePieces['K'].size() != 1 || blackPieces['k'].size() != 1) {
        return false;
    }

    for (auto pair: whitePieces['P']) {
        if (pair.second == 1 || pair.second == 8) {
            return false;
        }
    }
    for (auto pair: blackPieces['p']) {
        if (pair.second == 1 || pair.second == 8) {
            return false;
        }
    }

    // for (int i = 0; i < 8; i++) {
    //     if (squares[0][i]->getPiece()) {
    //         if (
    //             squares[0][i]->getPiece()->getLetter() == 'P' ||
    //             squares[0][i]->getPiece()->getLetter() == 'p'
    //             ) {
    //             return false;
    //         }
    //     }
    //     if (squares[7][i]->getPiece()) {
    //         if (
    //             squares[7][i]->getPiece()->getLetter() == 'P' ||
    //             squares[7][i]->getPiece()->getLetter() == 'p'
    //             ) {
    //             return false;
    //         }
    //     }
    // }

    return !(isInCheck(true) || isInCheck(false));
}

void Board::movePiece(std::pair<char, int> start, std::pair<char, int> end, std::shared_ptr<Move> mv) {
    removePiece(end.first, end.second, mv);
    auto piece = squares[start.first - 'a'][start.second - 1]->getPiece();
    squares[end.first - 'a'][end.second - 1]->setPiece(piece);
    squares[start.first - 'a'][start.second - 1]->setPiece(nullptr);
    if (piece->isWhite()) {
        whitePieces[piece->getLetter()].erase(std::remove(whitePieces[piece->getLetter()].begin(), whitePieces[piece->getLetter()].end(), start), whitePieces[piece->getLetter()].end());
        whitePieces[piece->getLetter()].push_back(end);
    } 
    else {
        blackPieces[piece->getLetter()].erase(std::remove(blackPieces[piece->getLetter()].begin(), blackPieces[piece->getLetter()].end(), start), blackPieces[piece->getLetter()].end());
        blackPieces[piece->getLetter()].push_back(end);
    }
    auto opponentPieces = piece->isWhite() ? blackPieces : whitePieces;
    for (auto pawnPos: opponentPieces[piece->isWhite() ? 'p' : 'P']) {
        auto piece = squares[pawnPos.first - 'a'][pawnPos.second - 1]->getPiece();
        if (piece->getCanSpecialMove() && mv) {
            mv->enPassant = pawnPos;
            piece->setCanSpecialMove(false);
            break;
        }
    }
    if (mv) {
        mv->pieceAdded.push_back({piece->getLetter(), end});
        mv->pieceRemoved.push_back({piece->getLetter(), start});
    }
}

void Board::undoLastMove() {
    if (moves.empty()) {
        return;
    }
    std::shared_ptr<Move> lastMove = moves.top(), mv = std::make_shared<Move>();
    mv->isUndo = true;
    if (lastMove) {
        for (auto piece: lastMove->pieceAdded) {
            removePiece(piece.second.first, piece.second.second, mv);
        }
        for (auto piece: lastMove->pieceRemoved) {
            addPiece(piece.first, piece.second.first, piece.second.second, mv);
        }
    }
    if (lastMove->enPassant.first != ' ' && lastMove->enPassant.second != 0) {
        squares[lastMove->enPassant.first - 'a'][lastMove->enPassant.second - 1]->getPiece()->setCanSpecialMove(true);
    }
    moves.pop();
    moves.push(mv);
}

std::shared_ptr<Move> Board::getLastMove() {
    if (moves.empty()) {
        return nullptr;
    }
    return moves.top();
}

void Board::addLastMove(std::shared_ptr<Move> move) {
    moves.push(move);
}

std::shared_ptr<Move> Board::popLastMove() {
    if (moves.empty()) {
        return nullptr;
    }
    std::shared_ptr<Move> move = moves.top();
    moves.pop();
    return move;
}

bool Board::isInCheck(bool isWhite) {
    // char targetKing;
    // if (isWhite) {
    //     targetKing = 'K';
    // }
    // else {
    //     targetKing = 'k';
    // }

    auto opponentPieces = isWhite ? blackPieces : whitePieces;
    std::pair<char, int> playerKingPos = isWhite ? whitePieces['K'][0] : blackPieces['k'][0];
    // for (auto square: *this) {
    //     if (square->getPiece()) {
    //         if (square->getPiece()->getLetter() == targetKing) {
    //             std::pair<char, int> pos = square->getRankFile();
    //             playerKingVectorPos = std::make_pair(pos.first - 'a', pos.second - 1);
    //             break;
    //         } 
    //     }
    // }

    for (auto pieceType: opponentPieces) {
        for (auto piecePos: pieceType.second) {
            if (squares[piecePos.first - 'a'][piecePos.second - 1]->canMoveTo(playerKingPos)) {
                return true;
            }
        }
    }

    return false;
           

    // // knight
    // std::pair<int, int> knightMoves[8] = {
    //     {2, 1}, 
    //     {2, -1}, 
    //     {-2, 1}, 
    //     {-2, -1}, 
    //     {1, 2}, 
    //     {1, -2}, 
    //     {-1, 2}, 
    //     {-1, -2}};
    // for (int i = 0; i < 8; i++) {
    //     if (
    //         playerKingVectorPos.first + knightMoves[i].first >= 0 && 
    //         playerKingVectorPos.first + knightMoves[i].first < 8 && 
    //         playerKingVectorPos.second + knightMoves[i].second >= 0 && 
    //         playerKingVectorPos.second + knightMoves[i].second < 8
    //         ) {
    //         std::shared_ptr p = squares[playerKingVectorPos.first + knightMoves[i].first][playerKingVectorPos.second + knightMoves[i].second]->getPiece();
    //         if (p) {
    //             if (isWhite) {
    //                 if (p->getLetter() == 'n') {

    //                     return true;
    //                 }
    //             } 
    //             else {
    //                 if (p->getLetter() == 'N') {

    //                     return true;
    //                 }
    //             }
    //         }
    //     }
    // }

    // // rook -> files 
    // for (int i = playerKingVectorPos.first + 1; i < 8; i++) {
    //     std::shared_ptr p = squares[i][playerKingVectorPos.second]->getPiece();
    //     if (p) {
    //         if (isWhite) {
    //             if (p->getLetter() == 'r' || p->getLetter() == 'q') {
    //                 return true;
    //             }
    //             else {
    //                 break;
    //             }
    //         }
    //         else {
    //             if (p->getLetter() == 'R' || p->getLetter() == 'Q') {
    //                 return true;
    //             }
    //             else {
    //                 break;
    //             }
    //         }
    //     }
    // }
    // for (int i = playerKingVectorPos.first - 1; i >= 0; i--) {
    //     std::shared_ptr p = squares[i][playerKingVectorPos.second]->getPiece();
    //     if (p) {
    //         if (isWhite) {
    //             if (p->getLetter() == 'r' || p->getLetter() == 'q') {
    //                 return true;
    //             }
    //             else {
    //                 break;
    //             }
    //         }
    //         else {
    //             if (p->getLetter() == 'R' || p->getLetter() == 'Q') {
    //                 return true;
    //             }
    //             else {
    //                 break;
    //             }
    //         }
    //     }
    // }
    // // rook -> ranks
    // for (int i = playerKingVectorPos.second + 1; i < 8; i++) {
    //     std::shared_ptr p = squares[playerKingVectorPos.first][i]->getPiece();
    //     if (p) {
    //         if (isWhite) {
    //             if (p->getLetter() == 'r' || p->getLetter() == 'q') {
    //                 return true;
    //             }
    //             else {
    //                 break;
    //             }
    //         }
    //         else {
    //             if (p->getLetter() == 'R' || p->getLetter() == 'Q') {
    //                 return true;
    //             }
    //             else {
    //                 break;
    //             }
    //         }
    //     }
    // }
    // for (int i = playerKingVectorPos.second - 1; i >= 0; i--) {
    //     std::shared_ptr p = squares[playerKingVectorPos.first][i]->getPiece();
    //     if (p) {
    //         if (isWhite) {
    //             if (p->getLetter() == 'r' || p->getLetter() == 'q') {
    //                 return true;
    //             }
    //             else {
    //                 break;
    //             }
    //         }
    //         else {
    //             if (p->getLetter() == 'R' || p->getLetter() == 'Q') {
    //                 return true;
    //             }
    //             else {
    //                 break;
    //             }
    //         }
    //     }
    // }

    // // bishop -> diagonal
    // for (int i = 1; i < 8; i++) {
    //     if (
    //         playerKingVectorPos.first + i < 8 && 
    //         playerKingVectorPos.second + i < 8
    //         ) {
    //         std::shared_ptr p = squares[playerKingVectorPos.first + i][playerKingVectorPos.second + i]->getPiece();
    //         if (p) {
    //             if (isWhite) {
    //                 if (p->getLetter() == 'b' || p->getLetter() == 'q') {

    //                     return true;
    //                 }
    //                 else {
    //                     break;
    //                 }
    //             }
    //             else {
    //                 if (p->getLetter() == 'B' || p->getLetter() == 'Q') {

    //                     return true;
    //                 }
    //                 else {
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    // }
    // for (int i = 1; i < 8; i++) {
    //     if (
    //         playerKingVectorPos.first - i >= 0 && 
    //         playerKingVectorPos.second - i >= 0
    //         ) {
    //         std::shared_ptr p = squares[playerKingVectorPos.first - i][playerKingVectorPos.second - i]->getPiece();
    //         if (p) {
    //             if (isWhite) {
    //                 if (p->getLetter() == 'b' || p->getLetter() == 'q') {

    //                     return true;
    //                 }
    //                 else {
    //                     break;
    //                 }
    //             }
    //             else {
    //                 if (p->getLetter() == 'B' || p->getLetter() == 'Q') {

    //                     return true;
    //                 }
    //                 else {
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    // }
    // for (int i = 1; i < 8; i++) {
    //     if (
    //         playerKingVectorPos.first + i < 8 && 
    //         playerKingVectorPos.second - i >= 0
    //         ) {
    //         std::shared_ptr p = squares[playerKingVectorPos.first + i][playerKingVectorPos.second - i]->getPiece();
    //         if (p) {
    //             if (isWhite) {
    //                 if (p->getLetter() == 'b' || p->getLetter() == 'q') {

    //                     return true;
    //                 }
    //                 else {
    //                     break;
    //                 }
    //             }
    //             else {
    //                 if (p->getLetter() == 'B' || p->getLetter() == 'Q') {

    //                     return true;
    //                 }
    //                 else {
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    // }
    // for (int i = 1; i < 8; i++) {
    //     if (
    //         playerKingVectorPos.first - i >= 0 && 
    //         playerKingVectorPos.second + i < 8
    //         ) {
    //         std::shared_ptr p = squares[playerKingVectorPos.first - i][playerKingVectorPos.second + i]->getPiece();
    //         if (p) {
    //             if (isWhite) {
    //                 if (p->getLetter() == 'b' || p->getLetter() == 'q') {

    //                     return true;
    //                 }
    //                 else {
    //                     break;
    //                 }
    //             }
    //             else {
    //                 if (p->getLetter() == 'B' || p->getLetter() == 'Q') {

    //                     return true;
    //                 }
    //                 else {
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    // }

    // // pawn -> close squares
    // if (isWhite) {
    //     if (
    //         playerKingVectorPos.first - 1 >= 0 && 
    //         playerKingVectorPos.second + 1 <8
    //         ) {
    //         std::shared_ptr p = squares[playerKingVectorPos.first - 1][playerKingVectorPos.second + 1]->getPiece();
    //         if (p) {
    //             if (p->getLetter() == 'p') {
    //                 return true;
    //             }
    //         }
    //     }
    //     if (
    //         playerKingVectorPos.first + 1 < 8 && 
    //         playerKingVectorPos.second + 1 < 8
    //         ) {
    //         std::shared_ptr p = squares[playerKingVectorPos.first + 1][playerKingVectorPos.second + 1]->getPiece();
    //         if (p) {
    //             if (p->getLetter() == 'p') {
    //                 return true;
    //             }
    //         }
    //     }
    // }
    // else {
    //     if (
    //         playerKingVectorPos.first + 1 < 8 && 
    //         playerKingVectorPos.second - 1 >= 0
    //         ) {
    //         std::shared_ptr p = squares[playerKingVectorPos.first + 1][playerKingVectorPos.second - 1]->getPiece();
    //         if (p) {
    //             if (p->getLetter() == 'P') {
    //                 return true;
    //             }
    //         }
    //     }
    //     if (
    //         playerKingVectorPos.first - 1 >= 0  && 
    //         playerKingVectorPos.second - 1 >= 0
    //         ) {
    //         std::shared_ptr p = squares[playerKingVectorPos.first - 1][playerKingVectorPos.second - 1]->getPiece();
    //         if (p) {
    //             if (p->getLetter() == 'P') {
    //                 return true;
    //             }
    //         }
    //     }
    // }

    // return false;
}

void Board::emptyBoard(std::shared_ptr<Move> mv) {
    for (auto square: *this) {
        auto rankFile = square->getRankFile();
        removePiece(rankFile.first, rankFile.second, mv);
    }
}

bool Board::isPieceBetween(std::pair<char, int> start, std::pair<char, int> end) {
    if (start.first == end.first && start.second == end.second) {
        return false;
    }
    if (start.first == end.first) {
        for (int i = std::min(start.second, end.second) + 1; i < std::max(start.second, end.second); i++) {
            if (squares[start.first - 'a'][i - 1]->getPiece()) {
                return true;
            }
        }
    }
    else if (start.second == end.second) {
        for (int i = std::min(start.first, end.first) + 1; i < std::max(start.first, end.first); i++) {
            if (squares[i - 'a'][start.second - 1]->getPiece()) {
                return true;
            }
        }
    }
    else if (abs(start.first - end.first) == abs(start.second - end.second)) {
        int x = start.first - 'a';
        int y = start.second - 1;
        int xDir = end.first > start.first ? 1 : -1;
        int yDir = end.second > start.second ? 1 : -1;
        while (x != end.first - 'a' - xDir && y != end.second - 1 - yDir) {
            x += xDir;
            y += yDir;
            if (squares[x][y]->getPiece()) {
                return true;
            }
        }
    }
    return false;
}

Board::~Board() {}

BoardIterator Board::begin() {
    return BoardIterator{shared_from_this(), 'a', 1};
}

BoardIterator Board::end() {
    return BoardIterator{shared_from_this(), 'i', 1};
}

std::ostream &operator<<(std::ostream &out, const Board &b) {
    for (int i = 0; i < 8; i++) {
        out << 8 - i << " ";
        for (int j = 0; j < 8; j++) {
            if (b.squares[j][7 - i]->getPiece()) {
                out << b.squares[j][7 - i]->getPiece()->getLetter();
            } else {
                if ((i + j - 1) % 2 == 0) {
                    out << "_";
                } else {
                    out << " ";
                }
            }
        }
        out << std::endl;
    }
    out << std::endl;
    out << "  ";
    for (int i = 0; i < 8; i++) {
        out << (char)('a' + i);
    }
    return out;
}

std::shared_ptr<Square> Board::getSquare(char rank, int file) {
    return squares[rank - 'a'][file - 1];
}
