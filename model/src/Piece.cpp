#include "Piece.hpp"

Piece::Piece(sf::Texture& pieceTexture, int x, int y, PieceColor pieceColor) : m_pieceSprite(sf::Sprite(pieceTexture)), m_x(x), m_y(y), m_pieceColor(pieceColor)
{

}

Piece::~Piece()
{

}

void Piece::setSize(const sf::Vector2f& size)
{
    m_pieceSprite.setScale(size.x / m_pieceSprite.getLocalBounds().width, size.y / m_pieceSprite.getLocalBounds().height);
}

sf::Sprite Piece::getPieceSprite() const
{
    return m_pieceSprite;
}