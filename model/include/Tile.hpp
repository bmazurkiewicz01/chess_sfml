#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class Piece;

class Tile : public sf::Drawable, public sf::Transformable
{
private:
    sf::Vector2f m_size;
    float m_x;
    float m_y;
    sf::Color m_tileColor;
    std::shared_ptr<Piece> m_piece;

    friend std::ostream& operator<<(std::ostream& stream, const Tile& tile);

public:
    Tile();
    Tile(float size, float x, float y, sf::Color tileColor);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool containsPoint(sf::Vector2f point) const;

    sf::Vector2f getSize() const;
    float getX() const;
    float getY() const;
    sf::Color getColor() const;
    std::shared_ptr<Piece> getPiece() const;
    void setPiece(const std::shared_ptr<Piece>& piece);
};

#endif
