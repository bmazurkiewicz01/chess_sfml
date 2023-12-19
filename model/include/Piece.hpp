#ifndef PIECE_HPP
#define PIECE_HPP

#include <SFML/Graphics.hpp>
#include "PieceColor.hpp"

class Tile;

class Piece : public sf::Drawable, public sf::Transformable
{
protected:
    sf::Sprite m_pieceSprite;
    int m_x;
    int m_y;
    PieceColor m_pieceColor;

public:
    Piece(sf::Texture& pieceTexture, int x, int y, PieceColor pieceColor);
    virtual ~Piece();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual void move(Tile& tile, Tile& clickedTile) = 0;
    virtual bool isValidMove(int x, int y) = 0;
    void setSize(const sf::Vector2f& size);

    sf::Sprite getPieceSprite() const;
};

#endif
