#include "BoardController.hpp"
#include "EventManager.hpp"
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Logger.hpp"
#include "KingChecker.hpp"
#include "EnPassantManager.hpp"

BoardController::BoardController(BoardView& view) : m_view(view), m_clickedTile(nullptr), m_highlightValidMoves(false), m_currentTurn(PieceColor::WHITE)
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
    if (m_clickedTile)
    {
        std::shared_ptr<Piece> piece = m_clickedTile->getPiece();
        if (piece)
        {
            if (piece->isValidMove(*tile, m_view.getBoard()))
            {
                if (piece->getPieceType() == PieceType::KING)
                {
                    checkKingCastling(tile, piece);
                }
                else if (piece->getPieceType() == PieceType::PAWN)
                {
                    checkEnPassant(tile, piece);
                }
                else
                {
                    EnPassantManager::getInstance().popPawn();
                }

                m_clickedTile->setPiece(nullptr);
                piece->setPieceX(tile->getX());
                piece->setPieceY(tile->getY());
                tile->setPiece(piece);

                m_currentTurn = (m_currentTurn == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;

                GameReturnType gameResult = KingChecker::getInstance().isCheckmate(m_view.getBoard(), m_currentTurn);
                if (gameResult == GameReturnType::GAME_CHECKMATE)
                {
                    Logger::getInstance().log(LogLevel::INFO, "Checkmate! ", m_currentTurn == PieceColor::WHITE ? "BLACK" : "WHITE", " won.");
                }
                else if (gameResult == GameReturnType::GAME_STALEMATE)
                {
                    Logger::getInstance().log(LogLevel::INFO, "Stalemate! Draw.");
                }
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
            if(tile->getPiece()->getPieceColor() == m_currentTurn)
            {
                sf::Color highlightTileColor = tile->getColor() 
                                            == WHITE_TILE_COLOR ? WHITE_TILE_HIGHLIGHT_COLOR : BLACK_TILE_HIGHLIGHT_COLOR;
                tile->setColor(highlightTileColor);
                m_clickedTile = tile;
                
                tile->getPiece()->calculateValidMoves(m_view.getBoard());
                m_highlightValidMoves = true;
            }
            else
            {
                Logger::getInstance().log(LogLevel::DEBUG, "Not your turn, current turn is: ", m_currentTurn == PieceColor::WHITE ? "white" : "black");
            }
        }
        else
        {
            Logger::getInstance().log(LogLevel::DEBUG, "There is no piece on this tile");
        }
    }
}

void BoardController::checkKingCastling(const std::shared_ptr<Tile>& tile, std::shared_ptr<Piece>& piece)
{
    if(tile == nullptr || piece == nullptr)
    {
        return;
    }

    if (std::abs(tile->getX() - piece->getPieceX()) == 2)
    {
        if (tile->getX() < piece->getPieceX())
        {
            std::shared_ptr<Piece> rook = m_view.getBoard()[piece->getPieceY()][0].getPiece();
            if (rook->getPieceType() == PieceType::ROOK)
            {
                Tile& oldRookTile = m_view.getBoard()[piece->getPieceY()][0];
                oldRookTile.setPiece(nullptr);
                rook->setPieceX(tile->getX() + 1);

                Tile& newRookTile = m_view.getBoard()[piece->getPieceY()][tile->getX() + 1];
                newRookTile.setPiece(rook);
            }
        }
        else
        {
            std::shared_ptr<Piece> rook = m_view.getBoard()[piece->getPieceY()][7].getPiece();
            if (rook->getPieceType() == PieceType::ROOK)
            {
                Tile& oldRookTile = m_view.getBoard()[piece->getPieceY()][7];
                rook->setPieceX(tile->getX() - 1);

                Tile& newRookTile = m_view.getBoard()[piece->getPieceY()][tile->getX() - 1];
        
                newRookTile.setPiece(rook);
                oldRookTile.setPiece(nullptr);
            }
        }
    }
}

void BoardController::checkEnPassant(const std::shared_ptr<Tile>& tile, std::shared_ptr<Piece>& piece)
{
    if(tile == nullptr || piece == nullptr)
    {
        return;
    }

    if (std::abs(piece->getPieceY() - tile->getY()) == 1 && std::abs(piece->getPieceX() - tile->getX()) == 1)
    {
        int direction = (piece->getPieceColor() == PieceColor::WHITE) ? -1 : 1;
        int targetY = tile->getY() - direction;

        if (targetY >= 0 && targetY < BOARD_SIZE && tile->getX() >= 0 && tile->getX() < BOARD_SIZE)
        {
            Tile& pieceTile = m_view.getBoard()[targetY][tile->getX()];
            std::shared_ptr<Piece> targetPiece = pieceTile.getPiece();

            if (targetPiece && targetPiece->getPieceType() == PieceType::PAWN &&
                targetPiece->getPieceColor() != piece->getPieceColor() &&
                std::static_pointer_cast<Pawn>(targetPiece)->getExposedOnEnPassant())
            {
                pieceTile.setPiece(nullptr);
            }
        }
        EnPassantManager::getInstance().popPawn(); 
    }
}
