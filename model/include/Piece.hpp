#ifndef PIECE_HPP
#define PIECE_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "PieceColor.hpp"
#include "PieceType.hpp"
#include "Tile.hpp"
#include "BoardUtils.hpp"

class Tile;

class Piece : public sf::Drawable, public sf::Transformable
{
protected:
    PieceType m_pieceType;
    sf::Sprite m_pieceSprite;
    int m_x;
    int m_y;
    PieceColor m_pieceColor;
    mutable std::vector<Tile> m_validMoves;

    bool resultsInCheck(int targetY, int targetX, const BoardType& board) const;

public:
    Piece() = default;
    Piece(sf::Texture& pieceTexture, int x, int y, PieceColor pieceColor, PieceType pieceType);
    virtual ~Piece();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual bool isValidMove(const Tile& tile, BoardType board, bool simulateMove = false) const;
    virtual void calculateValidMoves(BoardType board, bool simulateMoves = false) const = 0;
    void setSize(const sf::Vector2f& size);

    sf::Sprite getPieceSprite() const;
    int getPieceX() const;
    int getPieceY() const;
    void setPieceX(int x);
    void setPieceY(int y);
    PieceColor getPieceColor() const;
    PieceType getPieceType() const;
    const std::vector<Tile>& getValidMoves() const;
};

#endif
