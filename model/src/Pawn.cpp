#include "Pawn.hpp"
#include "Logger.hpp"
#include "EnPassantManager.hpp"

Pawn::Pawn(sf::Texture& texture, int x, int y, PieceColor pieceColor, int direction) 
                        : Piece(texture, x, y, pieceColor, PieceType::PAWN), m_firstMove(true), m_exposedOnEnPassant(false), m_direction(direction)
{
    
}

bool Pawn::isMovingForward(int y) const
{
    bool result = false;

    if (m_direction == -1)
    {
        result = y < m_y;
    }
    else
    {
        result = y > m_y;
    }

    return result;
}

bool Pawn::canPromote(int y) const
{
    bool result = false;

    if (m_direction == -1)
    {
        result = y == 0;
    }
    else
    {
        result = y == 7;
    }
    return result;
}

bool Pawn::isPathClear(int y, BoardType board) const
{
    if (m_direction == -1)
    {
        for (int boardY = m_y - 1; boardY > y; boardY--) {
            if (board[boardY][m_x].getPiece() != nullptr) 
            {
                return false;
            }
        }
    }
    else
    {
        for (int boardY = m_y + 1; boardY < y; boardY++) {
            if (board[boardY][m_x].getPiece() != nullptr) 
            {
                return false;
            }
        }
    }
    return true;
}

bool Pawn::isValidMove(const Tile& tile, BoardType board, bool simulateMove) const
{
    auto it = std::find(m_validMoves.begin(), m_validMoves.end(), tile);
    if (it == m_validMoves.end())
    {
        return false;
    }
    else
    {
        if (!simulateMove)
        {
            m_firstMove = false;
            if (std::abs(tile.getY() - m_y) == 2)
            {
                EnPassantManager::getInstance().registerPawn(this);
            }
        }
        return true;
    }
}

void Pawn::calculateValidMoves(BoardType board, bool simulateMoves) const
{
    m_validMoves.clear();

    int targetY = m_y + m_direction;

    if (targetY >= 0 && targetY < BOARD_SIZE)
    {
        for (int deltaX = -1; deltaX <= 1; deltaX += 2)
        {
            int targetX = m_x + deltaX;

            if (targetX >= 0 && targetX < BOARD_SIZE && targetY - m_direction >= 0 && targetY - m_direction < BOARD_SIZE)
            {
                std::shared_ptr<Piece> targetPiece = board[targetY - m_direction][targetX].getPiece();
                if (targetPiece && targetPiece->getPieceType() == PieceType::PAWN &&
                    targetPiece->getPieceColor() != m_pieceColor &&
                    std::static_pointer_cast<Pawn>(targetPiece)->getExposedOnEnPassant())
                {
                    m_validMoves.emplace_back(board[targetY][targetX]);
                }
            }
        }
    }

    if (targetY >= 0 && targetY < BOARD_SIZE && board[targetY][m_x].getPiece() == nullptr)
    {
        if (simulateMoves || !resultsInCheck(targetY, m_x, board))
        {
            m_validMoves.emplace_back(board[targetY][m_x]);
        }
        if (m_firstMove)
        {
            if ((targetY + m_direction) >= 0 && (targetY + m_direction) < BOARD_SIZE && board[targetY + m_direction][m_x].getPiece() == nullptr)
            {
                if (simulateMoves || !resultsInCheck(targetY + m_direction, m_x, board))
                    m_validMoves.emplace_back(board[targetY + m_direction][m_x]);
            }
        }
    }

    for (int deltaX = -1; deltaX <= 1; deltaX += 2)
    {
        int targetX = m_x + deltaX;
        if (targetX >= 0 && targetX < BOARD_SIZE && targetY >= 0 && targetY < BOARD_SIZE)
        {
            std::shared_ptr<Piece> targetPiece = board[targetY][targetX].getPiece();
            if (targetPiece && targetPiece->getPieceColor() != m_pieceColor)
            {
                if (simulateMoves || !resultsInCheck(targetY, targetX, board))
                    m_validMoves.emplace_back(board[targetY][targetX]);
            }
        }
    }
}

bool Pawn::getExposedOnEnPassant() const
{
    return m_exposedOnEnPassant;
}

void Pawn::setExposedOnEnPassant(bool exposed) const
{
    m_exposedOnEnPassant = exposed;
}

int Pawn::getDirection() const
{
    return m_direction;
}
