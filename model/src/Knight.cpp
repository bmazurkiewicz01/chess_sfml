#include "Knight.hpp"
#include "KingChecker.hpp"

Knight::Knight(sf::Texture& pieceTexture, int x, int y, PieceColor pieceColor)
    : Piece(pieceTexture, x, y, pieceColor, PieceType::KNIGHT)
{

}

void Knight::calculateValidMoves(BoardType board, bool simulateMoves) const
{
    m_validMoves.clear();

    const std::vector<std::pair<int, int>> knightMoves = {
        {1, 2}, {2, 1}, {2, -1}, {1, -2},
        {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
    };

    for (const auto& move : knightMoves)
    {
        int deltaY = move.first;
        int deltaX = move.second;

        int targetY = m_y + deltaY;
        int targetX = m_x + deltaX;

        if (targetY < 0 || targetY >= BOARD_SIZE || targetX < 0 || targetX >= BOARD_SIZE)
        {
            continue; 
        }

        std::shared_ptr<Piece> targetPiece = board[targetY][targetX].getPiece();
        if (!targetPiece || (targetPiece->getPieceColor() != m_pieceColor))
        {
            if (simulateMoves || !resultsInCheck(targetY, targetX, board))
            {
                m_validMoves.emplace_back(board[targetY][targetX]);
            }
        }
    }
}
