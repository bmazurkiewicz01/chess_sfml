#include "Tile.hpp"

Tile::Tile() : m_size(sf::Vector2f()), m_x(0), m_y(0), m_tileColor(sf::Color()) 
{

}

Tile::Tile(float size, float x, float y, sf::Color tileColor) : m_size(sf::Vector2f(size, size)), m_x(x), m_y(y), m_tileColor(tileColor)
{
    setPosition(sf::Vector2f(x * size, y * size));
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // states.transform *= getTransform();

    sf::RectangleShape shape(m_size);
    shape.setFillColor(m_tileColor);
    shape.setPosition(getPosition());
    target.draw(shape);

    if (m_piece)
    {
        // sf::Transform combinedTransform = states.transform * m_piece->getTransform();
        // m_piece->setPosition(combinedTransform.transformPoint(sf::Vector2f(0, 0)));
        m_piece->setSize(m_size);
        m_piece->setPosition(getPosition());
        m_piece->draw(target, states);
    }
}

bool Tile::containsPoint(sf::Vector2f point) const 
{
    sf::FloatRect bounds(getPosition(), m_size);
    return bounds.contains(point);
}

sf::Vector2f Tile::getSize() const
{
    return m_size;
}

float Tile::getX() const 
{
    return m_x;
}

float Tile::getY() const 
{
    return m_y;
}

sf::Color Tile::getColor() const 
{
    return m_tileColor;
}

std::shared_ptr<const Piece> Tile::getPiece() const
{
    return m_piece;
}

void Tile::setPiece(const std::shared_ptr<Piece>& piece)
{
    m_piece = piece;
}

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
