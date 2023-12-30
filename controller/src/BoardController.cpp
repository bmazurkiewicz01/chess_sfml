#include "BoardController.hpp"
#include "EventManager.hpp"
#include "Piece.hpp"
#include "Logger.hpp"

BoardController::BoardController(BoardView& view) : m_view(view), m_clickedTile(nullptr), m_highlightValidMoves(false) 
{
    EventManager::getInstance().subscribe<Tile>(EventType::ON_TILE_PRESSED, [this](const std::shared_ptr<Tile>& tile) {
        this->handleOnTilePressed(tile);
    });
}

void BoardController::run() 
{
    while (m_view.getWindow().isOpen()) 
    {
        m_view.handleEvents();
        m_view.drawBoard();

        if (m_highlightValidMoves && m_clickedTile && m_clickedTile->getPiece())
        {
            m_view.drawMoveHint(m_clickedTile->getPiece()->getValidMoves());
        }

        m_view.getWindow().display();
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
            if (piece->isValidMove(*tile, m_view.getBoard()))
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
        sf::Color oldTileColor = m_clickedTile->getColor() == WHITE_TILE_HIGHLIGHT_COLOR ? WHITE_TILE_COLOR : BLACK_TILE_COLOR;
        m_clickedTile->setColor(oldTileColor);
        m_clickedTile = nullptr;
        m_highlightValidMoves = false;
    }
    else
    {
        if(tile->getPiece() != nullptr)
        {
            sf::Color highlightTileColor = tile->getColor() 
                                            == WHITE_TILE_COLOR ? WHITE_TILE_HIGHLIGHT_COLOR : BLACK_TILE_HIGHLIGHT_COLOR;
            tile->setColor(highlightTileColor);
            m_clickedTile = tile;
            
            tile->getPiece()->calculateValidMoves(m_view.getBoard());
            m_highlightValidMoves = true;
        }
    }
}
