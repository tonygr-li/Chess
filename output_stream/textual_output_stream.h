#ifndef TEXTUAL_OUTPUT_STREAM_H
#define TEXTUAL_OUTPUT_STREAM_H

#include "../observer/observer.h"

#include <memory>
#include <string>


class GameView;

class TextualOutputStream: public Observer, public std::enable_shared_from_this<TextualOutputStream> {
    void outputMessage(const std::string&);
    void outputBoard(const std::shared_ptr<Board>&);
    std::shared_ptr<GameView> gameView;
public:
    void onNotify(const EventVariant&) override;
    ~TextualOutputStream();
    TextualOutputStream(const std::shared_ptr<GameView>&);
};

#endif // TEXTUAL_OUTPUT_STREAM_H
