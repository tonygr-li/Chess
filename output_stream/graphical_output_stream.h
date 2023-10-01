#ifndef GRAPHICAL_OUTPUT_STREAM_H
#define GRAPHICAL_OUTPUT_STREAM_H

#include "../observer/observer.h"
#include "../graphics/window.h"

class GameView;

class GraphicalOutputStream: public Observer, public std::enable_shared_from_this<GraphicalOutputStream> {
    void drawMessage(const std::string&);
    void drawBoard(const std::shared_ptr<Board>&);
    std::shared_ptr<Xwindow> boardWin;
    std::shared_ptr<Xwindow> messageWin;
    std::shared_ptr<GameView> gameView;
public:
    GraphicalOutputStream(std::shared_ptr<GameView>);
    ~GraphicalOutputStream();
    void onNotify(const EventVariant&) override;
};

#endif // GRAPHICAL_OUTPUT_STREAM_H
