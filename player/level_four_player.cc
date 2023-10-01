#include "level_four_player.h"

#include <iostream>
#include <memory>
#include <sstream>

#include "../board/board.h"
#include "../game/game.h"
#include "../piece/piece.h"
#include "../square/square.h"

LevelFourPlayer::LevelFourPlayer(std::shared_ptr<Player> player): PlayerDecorator{player} {}

bool LevelFourPlayer::move(std::istream& in) {
    auto board = wraps->getGame()->getBoard();
    std::stringstream ss{"Q"};
    int maxNetPoint = 0;
    std::pair<char, int> bestMoveToEat;
    std::pair<char, int> BestMoveCurPiece;
    for (auto square: *board) {
        auto piece = square->getPiece();
        if (!piece || piece->isWhite() != wraps->isWhite()) {
            continue;
        }
        int currPoint = 0;
        std::pair<char, int> curPieceSquare = square->getRankFile();
        auto possibleMoves = piece->getMoves(curPieceSquare);
        for (auto move: possibleMoves) {
            auto opponentPiece = board->getSquare(move.first, move.second)->getPiece();
            if (!opponentPiece) {
                continue;
            }
            std::pair<char, int> CurEatSquare = move;
            currPoint = opponentPiece->getPointValue();
            if (!piece->move(square->getRankFile(), move, ss)) {
                continue;
            }
            if (isInCheck()) {
                board->undoLastMove();
                board->popLastMove();
                continue;
            }
            for (auto oppSquare: *board) {
                auto opponentPiece = oppSquare->getPiece();
                if (!opponentPiece || opponentPiece->isWhite() == wraps->isWhite()) {
                    continue;
                }
                if(!opponentPiece->move(oppSquare->getRankFile(), CurEatSquare, ss)) {
                    continue;
                }
                if (board->isInCheck(!wraps->isWhite())) {
                    board->undoLastMove();
                    board->popLastMove();
                    continue;
                }
                //Op can eat our piece
                currPoint -= piece->getPointValue(); // game->getBoard()->getSquare(BestMoveCurPiece.first, BestMoveCurPiece.second)->getPiece()
                if (currPoint > maxNetPoint) {
                    maxNetPoint = currPoint;
                    bestMoveToEat = CurEatSquare;
                    BestMoveCurPiece = curPieceSquare;
                }
                board->undoLastMove();
                board->popLastMove();
                break;
            }
            if (currPoint > maxNetPoint) {
                maxNetPoint = currPoint;
                bestMoveToEat = CurEatSquare;
                BestMoveCurPiece = curPieceSquare;
            }
            board->undoLastMove();
            board->popLastMove();
        }
    }
    
    if (maxNetPoint != 0) {
        return board->getSquare(BestMoveCurPiece.first, BestMoveCurPiece.second)->getPiece()->move(BestMoveCurPiece, bestMoveToEat, ss);
    }
    return wraps->move(in);
    // if (maxNetPoint(wraps->isWhite(), 0) != 0) {
    //     return true;
    // }
    // std::stringstream ss{"Q"};
    // auto board = wraps->getGame()->getBoard();
    // for (auto square: *board) {
    //     auto piece = square->getPiece();
    //     if (!piece || piece->isWhite() != wraps->isWhite()) {
    //         continue;
    //     }
    //     auto possibleMoves = piece->getMoves(square->getRankFile());
    //     for (auto move: possibleMoves) {
    //         bool canBeEaten = false;
    //         auto otherPiece = board->getSquare(move.first, move.second)->getPiece();
    //         if (otherPiece) {
    //             continue;
    //         }
    //         if (!piece->move(square->getRankFile(), move, ss)) {
    //             continue;
    //         }
    //         if (board->isInCheck(wraps->isWhite())) {
    //             board->undoLastMove();
    //             board->popLastMove();
    //             continue;
    //         }
    //         for (auto oppSquare: *board) {
    //             auto opponentPiece = oppSquare->getPiece();
    //             if (!opponentPiece || opponentPiece->isWhite() == wraps->isWhite()) {
    //                 continue;
    //             }
    //             if (!opponentPiece->move(oppSquare->getRankFile(), move, ss)) {
    //                 continue;
    //             }
    //             if (board->isInCheck(!wraps->isWhite())) {
    //                 board->undoLastMove();
    //                 board->popLastMove();
    //                 continue;
    //             }
    //             board->undoLastMove();
    //             board->popLastMove();
    //             canBeEaten = true;
    //             break;
    //         }
    //         if (canBeEaten) {
    //             board->undoLastMove();
    //             board->popLastMove();
    //             continue;
    //         }
    //         return true;
    //     }
    // }
    // return false;
}

int LevelFourPlayer::maxNetPoint(bool isWhite, int space) {
    int maxPoint = 0;
    std::pair<char, int> bestPieceSqaure;
    std::pair<char, int> bestMoveSqaure;
    std::stringstream ss{"Q"};
    for (int i = 0; i < space; ++i) {
        std::cout << "  ";
    }
    std::cout << "Begin maxNetPoint" << std::endl;
    auto board = wraps->getGame()->getBoard();
    for (auto square: *board) {
        auto piece = square->getPiece();
        if (!piece || piece->isWhite() != isWhite) {
            continue;
        }
        for (int i = 0; i < space; ++i) {
            std::cout << "  ";
        }
        std::cout << "check here 1" << " " << space << std::endl;
        auto possibleMoves = piece->getMoves(square->getRankFile());
        for (auto move: possibleMoves) {
            int currPoint, oppMaxPoint;
            auto opponentPiece = board->getSquare(move.first, move.second)->getPiece();
            for (int i = 0; i < space; ++i) {
                std::cout << "  ";
            }
            std::cout << "check here 2" << " " << space << std::endl;
            if (!opponentPiece || opponentPiece->isWhite() == isWhite) {
                continue;
            }
            for (int i = 0; i < space; ++i) {
                std::cout << "  ";
            }
            std::cout << "check here 3" << " " << space << std::endl;
            for (int i = 0; i < space; ++i) {
                std::cout << "  ";
            }
            std::cout << "piece: " << piece->getLetter() << std::endl;
            std::cout << *board << std::endl;
            if (!piece->move(square->getRankFile(), move, ss)) {
                continue;
            }
            for (int i = 0; i < space; ++i) {
                std::cout << "  ";
            }
            std::cout << "check here 4" << " " << space << std::endl;
            if (board->isInCheck(isWhite)) {
                board->undoLastMove();
                board->popLastMove();
                continue;
            }
            if (wraps->getGame()->getCurPlayer()->isWhite() != isWhite) {
                
            }
            for (int i = 0; i < space; ++i) {
                std::cout << "  ";
            }
            std::cout << "check here 5" << " " << space << std::endl;
            currPoint = opponentPiece->getPointValue();
            oppMaxPoint = maxNetPoint(!isWhite, space + 1);
            if (oppMaxPoint != 0) {
                currPoint -= oppMaxPoint;
                board->undoLastMove();
                board->popLastMove();
            }
            if (currPoint > maxPoint) {
                maxPoint = currPoint;
                bestPieceSqaure = square->getRankFile();
                bestMoveSqaure = move;
            }
            for (int i = 0; i < space; ++i) {
                std::cout << "  ";
            }
            std::cout << "check here 6" << " " << space << std::endl;
            board->undoLastMove();
            board->popLastMove();
        }
    }
    for (int i = 0; i < space; ++i) {
        std::cout << "  ";
    }
    std::cout << "End maxNetPoint" << std::endl;
    if (maxPoint != 0) {
        auto pieceMoved = board->getSquare(bestPieceSqaure.first, bestPieceSqaure.second)->getPiece();
        pieceMoved->move(bestPieceSqaure, bestMoveSqaure, ss);
        return maxPoint;
    }
    return 0;
}

