#include "BoardController.hpp"
#include "EventManager.hpp"
#include "Piece.hpp"

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
    std::cout << "Got address: " << tile.get() << std::endl;
    if (m_clickedTile)
    {
        std::shared_ptr<Piece> piece = m_clickedTile->getPiece();
        if(piece)
        {
            m_clickedTile->setPiece(nullptr);
            tile->setPiece(piece);
        }
        m_clickedTile = nullptr;
    }
    else
    {
        m_clickedTile = tile;
    }
}
