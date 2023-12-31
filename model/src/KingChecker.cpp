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

bool KingChecker::isWhiteKingInCheck(const BoardType& board) const
{
    return isKingInCheck(*m_whiteKing, board);
}

bool KingChecker::isBlackKingInCheck(const BoardType& board) const
{
    return isKingInCheck(*m_blackKing, board);
}

bool KingChecker::isKingInCheck(const King& king, const BoardType& board) const
{
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
                if (piece->isValidMove(board[kingY][kingX], board, true)) 
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool KingChecker::isCheckmate(const BoardType& board, PieceColor pieceColor) const
{
    std::shared_ptr<King> king = pieceColor == PieceColor::WHITE ? m_whiteKing : m_blackKing;
    
    if(!isKingInCheck(*king, board))
    {
        return false;
    }

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            std::shared_ptr<Piece> piece = board[y][x].getPiece();
            if (piece != nullptr && piece->getPieceColor() == pieceColor)
            {
                piece->calculateValidMoves(board);
                if(!piece->getValidMoves().empty())
                {
                    return false;
                }
            }
        }
    }
    return true;
}
