#include "textual_output_stream.h"

#include <iostream>

#include "../board/board.h"
#include "../game/game_view.h"

void TextualOutputStream::onNotify(const EventVariant& event) {
    if (std::holds_alternative<std::string>(event)) {
        outputMessage(std::get<std::string>(event));
    } else if (std::holds_alternative<std::shared_ptr<Board>>(event)) {
        outputBoard(std::get<std::shared_ptr<Board>>(event));
    }
}

void TextualOutputStream::outputMessage(const std::string& message) {
    std::cout << message << std::endl;
}

void TextualOutputStream::outputBoard(const std::shared_ptr<Board>& board) {
    std::cout << *board << std::endl;
}

TextualOutputStream::~TextualOutputStream() {
    gameView->detach(shared_from_this());
}

TextualOutputStream::TextualOutputStream(const std::shared_ptr<GameView>& gameView) : gameView(gameView) {}

