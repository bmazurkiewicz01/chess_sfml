#ifndef PIECE_HPP
#define PIECE_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "PieceColor.hpp"
#include "Tile.hpp"
#include "BoardUtils.hpp"

class Tile;

class Piece : public sf::Drawable, public sf::Transformable
{
protected:
    sf::Sprite m_pieceSprite;
    int m_x;
    int m_y;
    PieceColor m_pieceColor;
    mutable std::vector<Tile> m_validMoves;

public:
    Piece(sf::Texture& pieceTexture, int x, int y, PieceColor pieceColor);
    virtual ~Piece();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual bool isValidMove(const Tile& tile, std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE> board) const = 0;
    virtual void calculateValidMoves(std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE> board) const = 0;
    void setSize(const sf::Vector2f& size);

    sf::Sprite getPieceSprite() const;
    int getPieceX() const;
    int getPieceY() const;
    void setPieceX(int x);
    void setPieceY(int y);
    PieceColor getPieceColor() const;
    const std::vector<Tile>& getValidMoves() const;
};

#endif
