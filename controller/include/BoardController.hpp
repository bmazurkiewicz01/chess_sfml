#ifndef BOARD_CONTROLLER_HPP
#define BOARD_CONTROLLER_HPP

#include <memory>
#include "BoardView.hpp"
#include "PieceColor.hpp"

class BoardController {
private:
    BoardView& m_view;
    PieceColor m_currentTurn;
    std::shared_ptr<Tile> m_clickedTile;
    bool m_highlightValidMoves;

public:
    BoardController(BoardView& view);

    void run();
    void handleOnTilePressed(const std::shared_ptr<Tile>& tile);
};

#endif
