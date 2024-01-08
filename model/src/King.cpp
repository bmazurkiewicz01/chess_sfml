#include "King.hpp"
#include "KingChecker.hpp"
#include "Rook.hpp"

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

    if (m_firstMove && !simulateMoves)
    {
        if (canCastleKingside(board))
        {
            Tile kingsideRookTile = board[m_y][BOARD_SIZE - 1];
            BoardType kingsideCastlingBoard = board;
            kingsideCastlingBoard[m_y][m_x + 1].setPiece(std::make_shared<King>(*this));
            kingsideCastlingBoard[m_y][m_x + 1].setPiece(nullptr);

            KingChecker& kingChecker = KingChecker::getInstance();
            if (!kingChecker.isKingInCheck(*this, kingsideCastlingBoard) &&
                !kingChecker.isKingInCheck(*this, board))
            {
                m_validMoves.emplace_back(board[m_y][m_x + 2]);
            }
        }

        if (canCastleQueenside(board))
        {
            Tile queensideRookTile = board[m_y][0];
            BoardType queensideCastlingBoard = board;
            queensideCastlingBoard[m_y][m_x - 1].setPiece(std::make_shared<King>(*this));
            queensideCastlingBoard[m_y][m_x - 1].setPiece(nullptr);

            KingChecker& kingChecker = KingChecker::getInstance();
            if (!kingChecker.isKingInCheck(*this, queensideCastlingBoard) &&
                !kingChecker.isKingInCheck(*this, board))
            {
                m_validMoves.emplace_back(board[m_y][m_x - 2]);
            }
            
        }
    }
}

bool King::canCastleKingside(BoardType board) const
{
    if (!m_firstMove || KingChecker::getInstance().isKingInCheck(*this, board))
        return false;

    Tile kingsideRookTile = board[m_y][BOARD_SIZE - 1];

    if (kingsideRookTile.getPiece() == nullptr || kingsideRookTile.getPiece()->getPieceType() != PieceType::ROOK)
    {
        return false;
    }

    std::shared_ptr<Rook> rook = std::dynamic_pointer_cast<Rook>(kingsideRookTile.getPiece());
    if (rook != nullptr && !rook->isFirstMove())
    {
        return false;
    }

    for (int i = m_x + 1; i < BOARD_SIZE - 1; ++i)
    {
        if (board[m_y][i].getPiece() != nullptr || KingChecker::getInstance().isSquareUnderAttack(m_y, i, board, m_pieceColor))
            return false;
    }

    BoardType simulatedBoard = board;
    simulatedBoard[m_y][m_x + 1].setPiece(std::make_shared<King>(*this));
    simulatedBoard[m_y][m_x].setPiece(nullptr);

    if (KingChecker::getInstance().isKingInCheck(*this, simulatedBoard))
        return false;

    return true;
}

bool King::canCastleQueenside(BoardType board) const
{
    if (!m_firstMove || KingChecker::getInstance().isKingInCheck(*this, board))
        return false;

    Tile queensideRookTile = board[m_y][0];
    if (queensideRookTile.getPiece() == nullptr || queensideRookTile.getPiece()->getPieceType() != PieceType::ROOK)
    {
        return false;
    }

    std::shared_ptr<Rook> rook = std::dynamic_pointer_cast<Rook>(queensideRookTile.getPiece());
    if (rook != nullptr && !rook->isFirstMove())
    {
        return false;
    }

    for (int i = m_x - 1; i > 0; --i)
    {
        if (board[m_y][i].getPiece() != nullptr || KingChecker::getInstance().isSquareUnderAttack(m_y, i, board, m_pieceColor))
            return false;
    }

    BoardType simulatedBoard = board;
    simulatedBoard[m_y][m_x - 1].setPiece(std::make_shared<King>(*this));
    simulatedBoard[m_y][m_x].setPiece(nullptr);

    if (KingChecker::getInstance().isKingInCheck(*this, simulatedBoard))
        return false;

    return true;
}
