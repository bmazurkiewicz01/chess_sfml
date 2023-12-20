#ifndef PIECE_HPP
#define PIECE_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "PieceColor.hpp"
#include "Tile.hpp"

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
    virtual bool move(Tile& tile, Tile& clickedTile, std::array<std::array<Tile, 8>, 8> board) = 0;
    virtual bool isValidMove(const Tile& tile, std::array<std::array<Tile, 8>, 8> board) const = 0;
    void setSize(const sf::Vector2f& size);

    sf::Sprite getPieceSprite() const;
    int getPieceX() const;
    int getPieceY() const;
    void setPieceX(int x);
    void setPieceY(int y);
};

#endif
