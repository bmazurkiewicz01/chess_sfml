#include "BoardController.hpp"
#include "EventManager.hpp"
#include "Piece.hpp"
#include "Logger.hpp"

BoardController::BoardController(BoardView& view) : m_view(view), m_clickedTile(nullptr) 
{
    EventManager::getInstance().subscribe<Tile>(EventType::ON_TILE_PRESSED, [this](const std::shared_ptr<Tile>& tile) {
        this->handleOnTilePressed(tile);
    });
}

void BoardController::run() {
    while (m_view.getWindow().isOpen()) 
    {
        m_view.handleEvents();
        m_view.drawBoard();
    }
}

void BoardController::handleOnTilePressed(const std::shared_ptr<Tile>& tile)
{
    // Logger::getInstance().log(LogLevel::DEBUG, "Tile address in BoardController: ", tile.get());
    if (m_clickedTile)
    {
        std::shared_ptr<Piece> piece = m_clickedTile->getPiece();
        if(piece)
        {
            if (piece->move(*tile, *m_clickedTile, m_view.getBoard()))
            {
                m_clickedTile->setPiece(nullptr);
                piece->setPieceX(tile->getX());
                piece->setPieceY(tile->getY());
                tile->setPiece(piece);
            }
            else
            {
                Logger::getInstance().log(LogLevel::ERROR, "Invalid move");
            }
        }
        m_clickedTile = nullptr;
    }
    else
    {
        m_clickedTile = tile;
    }
}
