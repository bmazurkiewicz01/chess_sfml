#ifndef PIECE_HPP
#define PIECE_HPP

#include <SFML/Graphics.hpp>

class Piece : public sf::Drawable, public sf::Transformable
{
protected:
    sf::Sprite m_pieceSprite;

public:
    Piece(sf::Texture& pieceTexture);
    virtual ~Piece();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    void setSize(const sf::Vector2f& size);

    sf::Sprite getPieceSprite() const;
};

#endif
