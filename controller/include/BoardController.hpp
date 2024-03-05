#ifndef BOARD_CONTROLLER_HPP
#define BOARD_CONTROLLER_HPP

#include <memory>
#include "BoardView.hpp"
#include "PieceColor.hpp"
#include "Pawn.hpp"
#include "PromotionModalView.hpp"
#include "PromotionModalData.hpp"
#include "PromotionChoice.hpp"

class BoardController {
private:
    BoardView& m_view;
    PieceColor m_currentTurn;
    std::shared_ptr<Tile> m_clickedTile;
    bool m_highlightValidMoves;
    bool m_isPawnPromotionDialogActive;
    std::unique_ptr<PromotionModalData> m_promotionModalData;
    std::unique_ptr<PromotionModalView> m_promotionModalView;

    void checkKingCastling(const std::shared_ptr<Tile>& tile, std::shared_ptr<Piece>& piece);
    void checkEnPassant(const std::shared_ptr<Tile>& tile, std::shared_ptr<Pawn>& piece);
    bool promotePawn(PromotionChoice choice);
    void handleTurnState();
    void handleTileState();

public:
    BoardController(BoardView& view);

    void run();
    void handleOnTilePressed(const std::shared_ptr<Tile>& tile);
};

#endif
