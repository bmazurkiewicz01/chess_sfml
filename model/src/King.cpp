#include "King.hpp"
#include "KingChecker.hpp"

King::King(sf::Texture& texture, int x, int y, PieceColor pieceColor) 
                        : Piece(texture, x, y, pieceColor, PieceType::KING), m_firstMove(true)
{
    
}

bool King::isValidMove(const Tile& tile, BoardType board, bool simulateMove) const
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

void King::calculateValidMoves(BoardType board, bool simulateMoves) const
{
    m_validMoves.clear();

    for (int deltaY = -1; deltaY <= 1; ++deltaY) 
    {
        for (int deltaX = -1; deltaX <= 1; ++deltaX) 
        {
            int targetX = m_x + deltaX;
            int targetY = m_y + deltaY;

            if (targetX >= 0 && targetX < BOARD_SIZE && targetY >= 0 && targetY < BOARD_SIZE) 
            {
                std::shared_ptr<Piece> targetPiece = board[targetY][targetX].getPiece();

                if (!targetPiece || (targetPiece && targetPiece->getPieceColor() != m_pieceColor && targetPiece->getPieceType() != PieceType::KING)) 
                {
                    BoardType simulatedBoard = board;
                    simulatedBoard[m_y][m_x].setPiece(nullptr); 

                    King simulatedKing = *this;
                    simulatedKing.setPieceX(targetX);
                    simulatedKing.setPieceY(targetY);
                    simulatedBoard[targetY][targetX].setPiece(std::make_shared<King>(simulatedKing)); 

                    if (!KingChecker::getInstance().isKingInCheck(simulatedKing, simulatedBoard))
                    {
                        m_validMoves.emplace_back(board[targetY][targetX]);
                    }
                }
            }
        }
    }
}

