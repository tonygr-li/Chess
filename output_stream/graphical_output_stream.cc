#include "graphical_output_stream.h"

#include <iostream>
#include <stack>

#include "../board/board.h"
#include "../move/move.h"
#include "../graphics/window.h"
#include "../game/game_view.h"

GraphicalOutputStream::GraphicalOutputStream(std::shared_ptr<GameView> gameView): gameView{gameView} {}

GraphicalOutputStream::~GraphicalOutputStream() {
    gameView->detach(shared_from_this());
}

void GraphicalOutputStream::onNotify(const EventVariant& event) {
    if (std::holds_alternative<std::string>(event)) {
        drawMessage(std::get<std::string>(event));
    } else if (std::holds_alternative<std::shared_ptr<Board>>(event)) {
        drawBoard(std::get<std::shared_ptr<Board>>(event));
    }
}

void GraphicalOutputStream::drawMessage(const std::string& message) {
    if (!messageWin) {
        messageWin = std::make_shared<Xwindow>(400, 200);
    }
    messageWin->fillRectangle(0, 0, 400, 200, Xwindow::White);
    messageWin->drawString(40, 100, message);
}

void GraphicalOutputStream::drawBoard(const std::shared_ptr<Board>& board) {
    if (!boardWin) {
        boardWin = std::make_shared<Xwindow>(500, 500);
        boardWin->fillRectangle(0, 0, 500, 500, Xwindow::White);
        boardWin->fillRectangle(45, 45, 410, 410, Xwindow::Black);
        boardWin->fillRectangle(50, 50, 400, 400, Xwindow::White);
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8 ; ++j) {
                if ((i + j) % 2 == 0) {
                    boardWin->fillRectangle(50 + 50 * i, 50 + 50 * (7 - j), 50, 50, Xwindow::Green);
                }
                if (board->getSquare(i + 'a', j + 1)->getPiece()) {
                    boardWin->drawString(72 + 50 * i, 77 + 50 * (7 - j), std::string{board->getSquare(i + 'a', j + 1)->getPiece()->getLetter()});
                }
            }
        }
        for (int i = 0; i < 8; ++i) {
            boardWin->drawString(70 + 50 * i, 475, std::string{char('a' + i)});
            boardWin->drawString(20, 75 + 50 * i, std::string{char('8' - i)});
        }
    }
    else {
        auto move = board->getLastMove();
        if (!move) {
            return;
        } else if (move->isUndo) {
            board->popLastMove();
        }
        for (auto rmp: move->pieceRemoved) {
            int i = rmp.second.first - 'a', j = rmp.second.second - 1;
            if ((i + j) % 2 == 0) {
                boardWin->fillRectangle(50 + 50 * i, 50 + 50 * (7 - j), 50, 50, Xwindow::Green);
            } else {
                boardWin->fillRectangle(50 + 50 * i, 50 + 50 * (7 - j), 50, 50, Xwindow::White);
            }
        }
        for (auto adp: move->pieceAdded) {
            int i = adp.second.first - 'a', j = adp.second.second - 1;
            if ((i + j) % 2 == 0) {
                boardWin->fillRectangle(50 + 50 * i, 50 + 50 * (7 - j), 50, 50, Xwindow::Green);
            } else {
                boardWin->fillRectangle(50 + 50 * i, 50 + 50 * (7 - j), 50, 50, Xwindow::White);
            }
            boardWin->drawString(72 + 50 * i, 77 + 50 * (7 - j), std::string{adp.first});
        }
    }
}
