#include "Pawn.hpp"
#include "Logger.hpp"

Pawn::Pawn(sf::Texture& texture, int x, int y, PieceColor pieceColor) 
                        : Piece(texture, x, y, pieceColor), m_firstMove(true)
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

    Logger::getInstance().log(LogLevel::DEBUG, "isMovingForward ", result);

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

bool Pawn::isPathClear(int y, std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE> board) const
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

void Pawn::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    states.transform *= getTransform();
    target.draw(m_pieceSprite, states);
}

bool Pawn::isValidMove(const Tile& tile, std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE> board) const
{
    auto it = std::find(m_validMoves.begin(), m_validMoves.end(), tile);
    if (it == m_validMoves.end())
    {
        return false;
    }
    else
    {
        m_firstMove = false;
        return true;
    }

    // bool result = false;

    // int diffX = std::abs(m_x - tile.getX());
    // int diffY = std::abs(m_y - tile.getY());

    // if(isMovingForward(tile.getY()) && isPathClear(tile.getY(), board))
    // {
    //     if (tile.getPiece())
    //     {
    //         result = (diffY == 1 && diffX == 1);
    //     }
    //     else
    //     {
    //         if (m_firstMove)
    //         {
    //             if (diffY > 0 && diffY <= 2 && diffX == 0)
    //             {
    //                 result = true;
    //             }
    //         }
    //         else
    //         {
    //             result = (diffY == 1 && diffX == 0);
    //         }
    //     }   
    // }

    // if(result == true)
    // {
    //     m_firstMove = false;
    // }

    // return result;
}

void Pawn::calculateValidMoves(std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE> board) const
{
    m_validMoves.clear();

    int direction = (m_pieceColor == PieceColor::WHITE) ? -1 : 1;

    int targetY = m_y + direction;
    if (targetY >= 0 && targetY < BOARD_SIZE && board[targetY][m_x].getPiece() == nullptr)
    {
        m_validMoves.emplace_back(board[targetY][m_x]);
        
        if (m_firstMove)
        {
            if (targetY + direction >= 0 && targetY + direction < BOARD_SIZE && board[targetY + direction][m_x].getPiece() == nullptr)
            {
                m_validMoves.emplace_back(board[targetY + direction][m_x]);
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
                m_validMoves.emplace_back(board[targetY][targetX]);
            }
        }
    }

    Logger::getInstance().log(LogLevel::DEBUG, "Valid moves:");
    for(auto t : m_validMoves)
    {
        Logger::getInstance().log(LogLevel::INFO, "Move: ", t);
    }
}

