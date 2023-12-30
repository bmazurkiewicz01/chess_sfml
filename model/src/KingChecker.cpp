#include "KingChecker.hpp"

KingChecker::KingChecker() {}

KingChecker& KingChecker::getInstance()
{
    static KingChecker instance;
    return instance;
}

void KingChecker::setWhiteKing(std::shared_ptr<King> king)
{
    m_whiteKing = king;
}

void KingChecker::setBlackKing(std::shared_ptr<King> king)
{
    m_blackKing = king;
}

bool KingChecker::isWhiteKingInCheck(const std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE>& board) const
{
    return isKingInCheck(*m_whiteKing, board);
}

bool KingChecker::isBlackKingInCheck(const std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE>& board) const
{
    return isKingInCheck(*m_blackKing, board);
}

bool KingChecker::isKingInCheck(const King& king, const std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE>& board) const
{
    std::cout << "King: " << &king << std::endl;
    PieceColor kingColor = king.getPieceColor();
    int kingX = king.getPieceX();
    int kingY = king.getPieceY();
    for (int y = 0; y < BOARD_SIZE; ++y) 
    {
        for (int x = 0; x < BOARD_SIZE; ++x) 
        {
            std::shared_ptr<Piece> piece = board[y][x].getPiece();
            if (piece && piece->getPieceColor() != kingColor) 
            {
                if (piece->getPieceType() != PieceType::KING)
                {
                    piece->calculateValidMoves(board, true);
                }
                else
                {
                    int deltaX = std::abs(x - kingX);
                    int deltaY = std::abs(y - kingY);

                    if (deltaX <= 1 && deltaY <= 1) 
                    {
                        return true;
                    }
                }
                if (piece->isValidMove(board[kingY][kingX], board)) 
                {
                    return true;
                }
            }
        }
    }

    return false;
}
