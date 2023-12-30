#include "Piece.hpp"

Piece::Piece(sf::Texture& pieceTexture, int x, int y, PieceColor pieceColor, PieceType pieceType) : m_pieceSprite(sf::Sprite(pieceTexture)), m_x(x), m_y(y), m_pieceColor(pieceColor), m_pieceType(pieceType)
{

}

Piece::~Piece()
{

}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    states.transform *= getTransform();
    target.draw(m_pieceSprite, states);
}

void Piece::setSize(const sf::Vector2f& size)
{
    m_pieceSprite.setScale(size.x / m_pieceSprite.getLocalBounds().width, size.y / m_pieceSprite.getLocalBounds().height);
}

sf::Sprite Piece::getPieceSprite() const
{
    return m_pieceSprite;
}

int Piece::getPieceX() const
{
    return m_x;
}

int Piece::getPieceY() const
{
    return m_y;
}

void Piece::setPieceX(int x)
{
    m_x = x;
}

void Piece::setPieceY(int y)
{
    m_y = y;
}

PieceColor Piece::getPieceColor() const
{
    return m_pieceColor;
}

PieceType Piece::getPieceType() const
{
    return m_pieceType;
}

bool Piece::isValidMove(const Tile& tile, std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE> board, bool simulateMove) const
{
    auto it = std::find(m_validMoves.begin(), m_validMoves.end(), tile);
    if (it == m_validMoves.end())
    {
        return false;
    }
    else
    {
        return true;
    }   
}

const std::vector<Tile>& Piece::getValidMoves() const
{
    return m_validMoves;
}
