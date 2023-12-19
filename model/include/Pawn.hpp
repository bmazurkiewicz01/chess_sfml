#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece
{
public:
    Pawn(sf::Texture& texture, int x, int y, PieceColor pieceColor) : Piece(texture, x, y, pieceColor) {}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();
        target.draw(m_pieceSprite, states);
    }

    void move(Tile& tile, Tile& clickedTile) override
    {
        std::cout << "Got address in pawn: " << &tile << std::endl;
        std::cout << "Move!" << std::endl;
    }

    bool isValidMove(int x, int y) override
    {
        return true;
    } 
};

#endif
