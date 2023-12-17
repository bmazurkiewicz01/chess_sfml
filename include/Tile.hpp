#include <SFML/Graphics.hpp>
#include <iostream>

class Tile : public sf::Drawable, public sf::Transformable
{
private:
    sf::Vector2f m_size;
    float m_x;
    float m_y;
    sf::Color m_tileColor;

    friend std::ostream& operator<<(std::ostream& stream, const Tile& tile);

public:
    Tile() = default;
    Tile(float size, float x, float y, sf::Color tileColor) : m_size(sf::Vector2f(size, size)), m_x(x), m_y(y), m_tileColor(tileColor)
    {
        setPosition(sf::Vector2f(x * size, y * size));
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        sf::RectangleShape shape(m_size);
        shape.setFillColor(m_tileColor);
        shape.setPosition(getPosition());
        target.draw(shape);
    }

    bool containsPoint(sf::Vector2f point) const 
    {
        sf::FloatRect bounds(getPosition(), m_size);
        return bounds.contains(point);
    }

    sf::Vector2f getSize() const
    {
        return m_size;
    }

    float getX() const 
    {
        return m_x;
    }

    float getY() const 
    {
        return m_y;
    }

    sf::Color getColor() const 
    {
        return m_tileColor;
    }
};

std::ostream& operator<<(std::ostream& stream, const Tile& tile)
{
    std::string color = tile.m_tileColor == sf::Color::White ? "White" : "Black";
    stream << "Tile {" << std::endl
           << "\tm_size: " << tile.m_size.x << ", " << tile.m_size.y
           << "\n\tm_x: " << tile.m_x
           << "\n\tm_y: " << tile.m_y
           << "\n\tposition: " << tile.getPosition().x << ", " << tile.getPosition().y
           << "\n\tm_tileColor: " << color << std::endl
           << "}";
    return stream;
}