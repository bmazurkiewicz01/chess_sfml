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

bool Pawn::isPathClear(int y, std::array<std::array<Tile, 8>, 8> board) const
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

bool Pawn::move(Tile& tile, Tile& clickedTile, std::array<std::array<Tile, 8>, 8> board) 
{
    bool validMove = isValidMove(tile, board);
    return validMove;
}

bool Pawn::isValidMove(const Tile& tile, std::array<std::array<Tile, 8>, 8> board) const
{
    bool result = false;

    int diffX = std::abs(m_x - tile.getX());
    int diffY = std::abs(m_y - tile.getY());

    if(isMovingForward(tile.getY()) && isPathClear(tile.getY(), board))
    {
        if (tile.getPiece())
        {
            result = (diffY == 1 && diffX == 1);
        }
        else
        {
            if (m_firstMove)
            {
                if (diffY > 0 && diffY <= 2 && diffX == 0)
                {
                    result = true;
                }
            }
            else
            {
                result = (diffY == 1 && diffX == 0);
            }
        }   
    }

    if(result == true)
    {
        m_firstMove = false;
    }

    return result;
} 

