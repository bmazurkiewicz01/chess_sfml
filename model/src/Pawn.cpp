#include "Pawn.hpp"
#include "Logger.hpp"

Pawn::Pawn(sf::Texture& texture, int x, int y, PieceColor pieceColor) 
                        : Piece(texture, x, y, pieceColor, PieceType::PAWN), m_firstMove(true)
{
    
}

bool Pawn::isMovingForward(int y) const
{
    bool result = false;

    if (m_pieceColor == PieceColor::WHITE)
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

    if (m_pieceColor == PieceColor::WHITE)
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
    if (m_pieceColor == PieceColor::WHITE)
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
            m_firstMove = false;
        return true;
    }
}

void Pawn::calculateValidMoves(BoardType board, bool simulateMoves) const
{
    m_validMoves.clear();

    int direction = (m_pieceColor == PieceColor::WHITE) ? -1 : 1;

    int targetY = m_y + direction;
    if (targetY >= 0 && targetY < BOARD_SIZE && board[targetY][m_x].getPiece() == nullptr)
    {
        if (simulateMoves || !resultsInCheck(targetY, m_x, board))
        {
            m_validMoves.emplace_back(board[targetY][m_x]);
        
            if (m_firstMove)
            {
                if ((targetY + direction) >= 0 && (targetY + direction) < BOARD_SIZE && board[targetY + direction][m_x].getPiece() == nullptr)
                {
                    if (simulateMoves || !resultsInCheck(targetY + direction, m_x, board))
                        m_validMoves.emplace_back(board[targetY + direction][m_x]);
                }
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
