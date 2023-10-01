#include "alter_board_command.h"

#include <iostream>
#include <memory>
#include <sstream>

#include "../game/game.h"
#include "../move/move.h"

AlterBoardCommand::AlterBoardCommand(std::shared_ptr<Game> game, std::istream& in): Command{game, in} {}

std::string AlterBoardCommand::execute() {
    std::string cmd;
    std::string error = "Invalid setup: ";
    in >> cmd;
    if (cmd == "+") {
        char piece, rank;
        int file;
        in >> piece >> rank >> file;
        revert << "- " << rank << file << std::endl;
        auto prevPiece = game->getBoard()->getSquare(rank,file)->getPiece();
        if (prevPiece) {
            revert << "+ " << prevPiece->getLetter() << " " << rank << file << std::endl;
        }
        error += "+ " + std::string(1, piece) + " " + rank + std::to_string(file);
        auto mv = std::make_shared<Move>();
        bool pieceAdded = game->getBoard()->addPiece(piece, rank, file, mv);
        game->getBoard()->addLastMove(mv);
        return pieceAdded ? std::string() : error;
    } else if (cmd == "-") {
        char rank;
        int file;
        in >> rank >> file;
        revert << "+ " << game->getBoard()->getSquare(rank, file)->getPiece()->getLetter() << " " << rank << file << std::endl;
        error += "- " + rank + std::to_string(file);
        auto mv = std::make_shared<Move>();
        bool pieceRemoved = game->getBoard()->removePiece(rank, file, mv);
        game->getBoard()->addLastMove(mv);
        return pieceRemoved ? std::string() : error;
    } else if (cmd == "=") {
        std::string colour;
        in >> colour;
        error += "= " + colour;
        if (colour != "white" && colour != "black") {
            return error;
        }
        // revert << "= " << (colour == "black" ? "white" : "black") << std::endl;
        game->setTurnToWhite(colour == "white");
        return revert.str();
    } else if (cmd == "done") {
        return game->getBoard()->isValid() ? "done" : error + "invalid board";
    } else if (cmd == "undo") {
        return "undo";
    } else {
        return error + cmd;
    }
}

void AlterBoardCommand::undo() {
    while (revert.tellp() > 0) {
        std::make_shared<AlterBoardCommand>(game, revert)->execute();
    }
}