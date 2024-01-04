#include "Rook.hpp"
#include "KingChecker.hpp"

Rook::Rook(sf::Texture& pieceTexture, int x, int y, PieceColor pieceColor)
    : Piece(pieceTexture, x, y, pieceColor, PieceType::ROOK)
{

}

void Rook::calculateValidMoves(BoardType board, bool simulateMoves) const
{
    m_validMoves.clear();

    const std::vector<std::pair<int, int>> directions = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1}
    };

    for (const auto& direction : directions)
    {
        int deltaY = direction.first;
        int deltaX = direction.second;

        for (int step = 1; step < BOARD_SIZE; ++step)
        {
            int targetY = m_y + step * deltaY;
            int targetX = m_x + step * deltaX;

            if (targetY < 0 || targetY >= BOARD_SIZE || targetX < 0 || targetX >= BOARD_SIZE)
            {
                break; 
            }

            std::shared_ptr<Piece> targetPiece = board[targetY][targetX].getPiece();
            if (!targetPiece)
            {
                if (simulateMoves || !resultsInCheck(targetY, targetX, board))
                {
                    m_validMoves.emplace_back(board[targetY][targetX]);
                }
            }
            else
            {
                if (targetPiece->getPieceColor() == m_pieceColor)
                {
                    break;
                }

                if (simulateMoves || !resultsInCheck(targetY, targetX, board))
                {
                    m_validMoves.emplace_back(board[targetY][targetX]);
                }

                break; 
            }
        }
    }
}
